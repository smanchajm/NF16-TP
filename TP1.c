#ifndef TP1_C_INCLUDED
#define TP1_C_INCLUDED

#include <stdlib.h>
#include <stdio.h>



void buffer(){
    int c;
    while((c = getchar()) != EOF && c != '\n');
}

void ex1(){
    float nb1 = 0, nb2 = 0, somme  = 0, c = 0;
    printf("Entrer deux reels :\n");
    scanf("%f", &nb1);
    buffer();
    scanf("%f", &nb2);
    buffer();

    // somme
    somme = nb1 + nb2;
    printf("somme :%f\n", somme);

    // PERMUTATION
    nb1 = c;
    nb1 = nb2;
    nb2 = c;

    //modulo
    int x = 0, y = 0, modulo;
    printf("Entrer deux int :\n");
    scanf("%d", &x);
    buffer();
    scanf("%d", &y);
    buffer();


    modulo = x%y;
    printf("%d\n", modulo);

    printf("decimal: %d, octal: %o, hexa: %x", x, x, x);


printf("Entrer un car : ");
char car;

car = getchar();

switch (car)
{
case '1':
    printf("UN");
    break;
case '2':
    printf("DEUX");
    break;
case '3':
    printf("TROIS");
    break;
default :
    printf("autre caractere");
    break;
}


}

void ex2() {

    char c;
    printf("Entrer un char : ");
    c = getchar();

    if ((c>='a') & (c<='z')){
        printf("C'est une lettre minuscule\n");
    }
    else if ((c>='A') & (c<='Z')){
        printf("C'est une lettre majuscule\n");
    }
    else if ((c>='1') & (c<='9')){
        printf("C'est un chiffre\n");
    }

int table;

while(table != 0){
    printf("\nQuelle table ?, tapez 0 pour sortir\n");
    scanf("%d", &table);
    buffer();
    for (int i=1; i < 10; i++){
        printf(" %d,",(table * i));
    }
}


}

void ex3(){
//    int tab[10];
//
//    for (int i=0; i < 10; i++){
//        tab[i] = 0;
//    }
//
//
//    int tab2[5];
//    for (int i=4; i >= 0; i--){
//        tab[i] = i;
//    }

int tab3[3][4];





}



#endif // TP1_C_INCLUDED
