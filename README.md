# Calculate-a-mathematical-expression
Pislari Vadim -> Facultatea Automatica si Calculatoare -> Universitatea Politehnica Bucuresti

                                                 (Romanian language)
                                               -------DESCRIERE-------
               
O expresie aritmetică este alcătuită din operatori și operanzi (termenii asupra cărora se aplica operatorii). În cazul nostru, setul operatorilor va fi următorul:
</br>● ‘-’  - scădere 
</br> ● ‘+’  - adunare 
</br> ● ‘*’  - înmulțire
 </br>● ‘/’  - împărțire
 </br>● ‘^’  - ridicare la putere 
 </br>● ‘sqrt’  - radical 
 
Se observă că primii 5 operatori sunt binari (au nevoie de 2 valori pentru a fi aplicați) iar cel de-al șaselea este unar (sqrt primește o singură valoare). Pentru a asigura ordinea corectă a operațiilor, operatorii au priorități diferite (de la mic la mare): 
 </br>● ‘-’ și ‘+’ (cea mai mica prioritate) 
 </br>● ‘*’ și ‘/’ 
 </br>● ‘^’ și ‘sqrt’ (cea mai mare prioritate) 
 </br>Această clasificare ajută la trecerea din forma infixată în forma prefixată. 

Pentru evaluarea unei expresii matematice, o abordare comună este cea a arborilor de expresii. Aceasta este o structură de date asemănătoare unui arbore (de cele mai multe ori, binar) în care nodurile sunt asociate operatorilor iar frunzele operanzilor.  
 
Forma prefixată (numită și forma poloneză) este o notație matematică în care operatorii preced operanzii lor. 

Infix  Prefix 2 * (3 + 4) => * 2 + 3 4 2 * 3 + 4 => + * 2 3 4 
</br> ● O expresie este la bază o variabilă sau o valoare numerică 
</br>● O nouă expresie se poate construi prin adunarea a doua expresii, înmulțirea a două expresii, împărțirea lor, etc. 
