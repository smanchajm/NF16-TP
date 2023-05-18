//
// Created by samma on 18/05/2023.
//

#ifndef NF16_P23_2_TP4_H
#define NF16_P23_2_TP4_H
#define MAX 70 //Maximum de caractères pour un nom

// Structures et types
struct Position {
    int numeroLigne;
    int ordre;
    int numeroPhrase;
    struct Position *suivant;
};
typedef struct Position T_Position;

struct Noeud {
    char *mot;
    int nbOccurences;
    T_Position  *listePositions;
    struct Noeud *filsGauche;
    struct Noeud *fildDroit;
};
typedef struct Noeud T_Noeud;

struct Index {
    T_Noeud racine;
    int nbMotsDistincts;
    int nbMotsTotal;
};
typedef struct Index T_Index;


#endif //NF16_P23_2_TP4_H
