int TP2_fact1(int n);
int TP2_fact2(int n);
int TP2_fibo1(int n);
int **creerTableau(int lig, int col);
int **genererSousMatrice(int **tab, int lig, int col);
void afficherTableau(int **tab, int lig, int col);
void copiesauflc(int **source, int **dest, int dim, int ligavirer);

#include <stdlib.h>
#include <stdio.h>


void TP2_buffer(){
    int c;
    while((c = getchar()) != EOF && c != '\n');
}

int TP2_fact1(int n){


    for(int i = n; i>1; --i){
        n = n*(i-1);
    }
    return n;
}

int TP2_fact2(int n){
    if (n == 1) {
        return 1;
    }
    return n*TP2_fact2(n-1);
}


int **creerTableau(int lig, int col){
    int i, j, val = 0;
    int **nouveauTableau;
    nouveauTableau = malloc(lig*sizeof(int));

    for( i = 0; i < lig; i++){
        nouveauTableau[i] = malloc(col*sizeof(int));
    }
    for(i=0; i<lig; i++){
        for(j=0; j<col; j++){
            nouveauTableau[i][j] = val++;
        }
    }
    return nouveauTableau;
}

void afficherTableau(int **tab, int lig, int col){
    for(int i=0; i<lig; i++){
        for(int j=0; j<col; j++){
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

/*int **genererSousMatrice(int **tab, int lig, int col){
    int **nouveauTableau;
    nouveauTableau = creerTableau((lig-1), (col-1));
    for(int i=1; i<lig; i++){
        for(int j=1; j<col; j++){
            nouveauTableau[i-1][j-1] = tab[i][j];
        }
    }
    return nouveauTableau;
}*/

void copiesauflc(int **source, int **dest, int dim, int ligavirer){
    int l,c,ld=0;
    for (l=0;l<dim;l++) if (l!=ligavirer)
    {
        for (c=1;c<dim;c++)
        dest[ld][c-1]=source[l][c];
        ld++;
    }
}


/*int TP2_det(mat[n][m]){
    if mat == vv{
        return mat[1][1];
    }
    return TP2_det(mat[][]);
}

int TP2_fibo1(int n){
    if (n==0 || n==1){
        return n;
    }
    return (TP2_fibo1(n-1)+TP2_fibo1(n-2));
}

int TP2_fibo2(int n){
    if (n==0 || n==1){
        return n;
    }
}*/

typedef  struct oui;
struct oui{
    int non[4];

};
