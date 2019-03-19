//Pislari Vadim

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

//lista de variabile simplu inlantuita
typedef struct var
{
	struct var *urm;
	char *denumire, *valoare;
}Variabila;

//arborele binar generic
typedef struct celula{
	void *info;
	struct celula *dr, *st;
}Tcelula;

//functie care verifica daca caracterul e o operatie
int32_t control_dr(Tcelula *varf)
{
	char *a =(char *)varf->info;
	if(strcmp(a, "+") == 0 || strcmp(a, "-") == 0 || strcmp(a, "*") == 0 || 
		strcmp(a,"/") == 0 || strcmp(a, "^") == 0 || strcmp(a, "sqrt") == 0 ) return 1;
	return 0;
}

//functie care verifica daca caracterul e o operatie inafara de sqrt
int32_t control_st(Tcelula *varf)
{
	char *a =(char *)varf->info;
	if(strcmp(a, "+") == 0 || strcmp(a, "-") == 0 || strcmp(a, "*") == 0 || 
		strcmp(a,"/") == 0 || strcmp(a, "^") == 0) return 1;
	return 0;
}

//cautarea pozitiei pentru inserarea celulei
void cautare_pozitie(Tcelula *varf, int32_t *directia ,Tcelula **ant, int32_t *indice)
{
	//SRD
	if(!varf) return;
	if (control_dr(varf) && *indice == 0 && !varf->dr)
	{
		//memorarea directiei
		*indice = 1;
		*directia=1;
		*ant=varf;
	}

	if(varf->dr)cautare_pozitie(varf->dr,directia,ant,indice);
	if (control_st(varf) && *indice == 0 && !varf->st)
	{
		//memorarea directiei
		*indice = 1;
		*directia=2;
		*ant=varf;
	}
	if(varf->st)cautare_pozitie(varf->st,directia,ant,indice);
}

//functie care modifica informatia dintro celula din char in int
int32_t modifica(Tcelula **varf, Variabila *var)
{
	//verificarea daca coincide cu vreo variabila
	for( ;var != NULL; var = var->urm )
	{
		char *a =(char *)var->denumire; 
		char *b =(char *)(*varf)->info;
		if (strcmp(b,a) == 0)
		{
			free((*varf)->info);
			//modicarea variabilei
			char *val = calloc(sizeof(char) , OPER);
			if (!val) return -1;
			memcpy(val, var->valoare, strlen( var->valoare));
			(*varf)->info = val;
			break;
		}
	}
	char *den =(char *)(*varf)->info;
	int32_t i = 0, suma = 0, semn = 0;
	char arr[Max]={'0','1','2','3','4','5','6','7','8','9'};
	if(den[0] == '-') 
	{
		semn = 1;
		i = 1;
	}
	//verificarea daca variabila intreg si modificarea in intreg
	for( ; i != strlen(den); i++)
	{
		int32_t j = 0;
		for( ; j != Max ; j++ )
			if(den[i] == arr[j])
			 {
				int32_t aux = den[i]-'0';
				suma = suma * 10 + aux;
				break;
			}
		if(j == Max) return 0;
	}
	if (semn == 1) suma = suma * -1;
	free((*varf)->info);

	int32_t *val = malloc(sizeof(int));
	if(!val) return -1;
	*val = suma;
	(*varf)->info = val;
	return 1;
}

//functie care modifica variabile cu numere intregi 
//si verifica sa nu fie variabile nedeclarate
void parcurgere(Tcelula **varf, int32_t *reusit,Variabila *var,Tcelula **auxil)
{
	//SRD
	Tcelula *aux = *varf;

	//daca macar o data a continut o variabila nedeclarata 
	//se anuleaza urmatoarea parcurgere
	if(!aux || *reusit == 0 || *reusit == 2) return;

	if(aux)
	{
		if(!control_dr(aux)) *reusit = modifica(&aux,var);
		if(*reusit == 0) *auxil = *varf; 
	}
	if(aux->dr) parcurgere(&aux->dr ,reusit, var, auxil);
	if(aux->st) parcurgere(&aux->st ,reusit, var, auxil);

	if(aux->st)
	{
		char *vr = (char*) aux->info;
		int32_t *dr = (int32_t *) aux->st->info;
		if(*vr == '/' && *dr == 0)*reusit = 2;
	}
}

//funtie care calculeaza operatiile dintrun arbore
int calculare(Tcelula **arb,int32_t *floating)
{
	Tcelula *varf = *arb;
	if(!varf ) return -1;

	//apelarea recursiva SDR a arborelui binar
	if(varf->dr)calculare(&varf->dr, floating);
	if(varf->st)calculare(&varf->st, floating);
	if(varf->dr && varf->st)
	{
		//daca contine ambii copii
		int32_t *dr = (int32_t *) varf->dr->info;
		int32_t *st = (int32_t *) varf->st->info;
		char *a = (char *) varf->info;
		int32_t rez = 1; 

		//determinarea operatiei
		if(strcmp(a,"+") == 0)rez = *dr + *st;
		else if(strcmp(a, "-") == 0) rez = *dr - *st;
		else if(strcmp(a, "*") == 0) rez = *dr * *st;
		else if(strcmp(a, "/") == 0)
		{
			if(*st == 0)
			{
				*floating = 1;
				free(varf->dr->info);
				free(varf->st->info);
				free(varf->dr);
				free(varf->st);
				return 0;
			}
			rez = *dr / *st;
		}
		else if(strcmp(a,"^") == 0)
		{
			int32_t i = 0;
			for( ; i != *st; i++)
			{
				rez = rez * *dr; 
			}
		}

		//eliberarea celulelor de mai jos si calcularea radacinii
		int32_t *val = malloc(sizeof(int));
		if(!val) return -1;
		*val = rez;

		free(varf->info);
		varf->info = val;
		free(varf->dr->info);
		free(varf->st->info);
		free(varf->dr);
		free(varf->st);
		
	}
	if(varf->dr && !varf->st)
	{
		//daca contine un singur copil adica e sqrt
		int32_t *dr = (int32_t *) varf->dr->info;
		if(*dr < 0)
		{
			*floating = 1;
			free(varf->dr->info);
			free(varf->dr);
			return 0;
		}

		int32_t rez = sqrt(*dr); 
		int32_t *val = malloc(sizeof(int32_t));

		if(!val) return -1;
		*val = rez;
		free(varf->info);
		varf->info = val;
		free(varf->dr->info);
		free(varf->dr);
	}
	return 0;
}

//functie care elibereaza memoria din lista eliberata
void distruge(Variabila *var)
{
	Variabila *ant=NULL;
	for (; var!=NULL;ant=var,var = var->urm)
	{
		free(ant);
		free(var->denumire);
		free(var->valoare);
	}
	free(ant);
}
void distrugearb(Tcelula *varf)
{
	//SDR
	if(!varf) return;
	if(varf->st)distrugearb(varf->st);
	if(varf->dr)distrugearb(varf->dr);
	free(varf);
}
