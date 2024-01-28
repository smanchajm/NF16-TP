#ifndef TP2_H_INCLUDED
#define TP2_H_INCLUDED

int TP2_fact1(int n);
int TP2_fact2(int n);
int TP2_fibo1(int n);
int **creerTableau(int lig, int col);
void afficherTableau(int **tab, int lig, int col);
int **genererSousMatrice(int **tab, int lig, int col);
void copiesauflc(int **source, int **dest, int dim, int ligavirer);


#endif // TP2_H_INCLUDED
