//Pislari Vadim

#define OPER 20
#define Max 10
#include "struct_func.c"

int32_t main(int32_t argc, char const *argv[])
{
	//deschiderea fisierelor
	FILE *in = fopen(argv[1],"r");
	if(!in)
	{
		printf("eroarea 1\n");
		return -1;
	}

	FILE *out = fopen(argv[2],"w");
	if(!out)
	{
		printf("eroarea 2\n");
		return -1;
	}

	int32_t nr_variabile,i,nr_operatii;
	fscanf(in, "%d", &nr_variabile);
	
	// initializarea variabilei var care va reprezenta 
	Variabila *var = NULL, *ant = NULL;

	for (i = 0; i != nr_variabile ; i++)
	{
		Variabila *aux = calloc(sizeof(Variabila),1);
		if(!aux)
		{
			return -1;
		}

		// se denumirea variabilei
		aux->denumire = calloc(sizeof(char),Max);
		if(!aux->denumire)
		{
			free(aux);
			return -1;
		}

		// se aloca valoarea variabilei
		aux->valoare = calloc(sizeof(char) , Max);
		if(!aux->valoare)
		{
			free(aux->denumire);
			free(aux);
			return -1;
		}

		fscanf(in,"%s",aux->denumire);
		//se muta cu 2 pozitii pozitia curenta in fisier
		fseek(in, 2, SEEK_CUR);
		fscanf(in,"%s",aux->valoare);

		//se creaza legaturie listei
		if (var == NULL)
		{
			var = aux;
			ant = var;
		}
		else 
		{
			ant->urm = aux;
			ant = ant->urm;
		}
	}

	fscanf(in, "%d", &nr_operatii);

	//crearea arborelui pentru fiecare linie de operatii
	for (i = 0; i != nr_operatii ; i++)
	{
		char *oper = calloc(sizeof(char) , OPER );
		if(!oper)return -1;
		Tcelula *varf = NULL;

		//fiecare linie
		while( fscanf(in,"%s",oper) != -1 )
		{

			//se aloca o noua celula a arborelui
			Tcelula *aux = malloc(sizeof(Tcelula));
			if(!aux)return -1;

			char *val = calloc(sizeof(char), OPER);
			if(!val)
			{
				free(aux);
				return -1;
			}
			memcpy(val, oper, strlen(oper));

			aux->info = val;
			aux->dr = NULL;
			aux->st = NULL;
			if(varf == NULL)
			{
				varf = aux;
			}
			else
			{
				//inserarea in arbore daca el nu e nul
				Tcelula *antc = NULL;
				int32_t indice = 0,directia = 0;
				cautare_pozitie(varf,&directia,&antc,&indice);

				//determinarea directiei 
				if(directia == 1) antc->dr=aux;
				if(directia == 2) antc->st=aux;
			}

			//se verifica daca sa terminat linia
			char buffer,buff1;
			fscanf(in,"%c",&buffer);

			if(buffer == ' ') 
			{
				fscanf(in,"%c",&buff1);
				fseek(in, -1, SEEK_CUR);
				if(buff1 == '\n') break;
			}
			if(buffer == '\n') break;
		}

		//prelucrarea arborelui
		//variabila daca verifica daca nu sunt variabile nedeclarate
		int32_t reusit = 1;

		//variabila care pastreaza variabila nedeclarata
		Tcelula *aux = NULL;
		parcurgere(&varf,&reusit,var,&aux);

		char *val = NULL;
		if(reusit == 0) 
		{
			val = calloc(sizeof(char), OPER);
			memcpy(val, aux->info, strlen(aux->info));
		}

		//variabila care verifica daca nu sa facut impartirea la 0
		int32_t floating = 0;
		if(calculare(&varf,&floating) == -1) return -1;
		int32_t rasp = *(int32_t *)varf->info;

		free(oper);
		free(varf->info);
		free(varf);

		//printarea in fisierul out
		if(reusit == 0) 
		{
			fprintf(out,"Variable %s undeclared\n",val);
			free(val);
			continue;
		}
		if(reusit == 2 || floating == 1)
		{

			fprintf(out,"Invalid expression\n");
			continue;
		}
		fprintf(out,"%d\n",rasp);
	}
	
	distruge(var);
	fclose(in);
	fclose(out);
	return 0;	
}

