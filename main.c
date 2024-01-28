#include <stdlib.h>
#include <stdio.h>

#include "TP1.h"
#include "TP2.h"


int **crerTableau(int ligne, int colonne){



}


int main(int argc, char *argv[]) {

    //ex1();
    //ex2();
    //ex3();
    int ** tab;
    int ** tab2;
    tab = creerTableau(4,4);
    afficherTableau(tab,4,4);
    printf("\n");
    tab2 = creerTableau(3,3);
    copiesauflc(tab, tab2, 3, 1);
    afficherTableau(tab2, 3, 3);

    return 0;
}
