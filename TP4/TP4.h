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
    T_Noeud *racine;
    int nbMotsDistincts;
    int nbMotsTotal;
};
typedef struct Index T_Index;

// Création et initialisation des structures
T_Position *creerPosition(int numeroLigne, int ordre, int numeroPhrase);
T_Noeud *creerNoeud(char *mot, int nbOccurences);
T_Index *creerIndex();

int comparaison(int ligne1, int ordre1, int ligne2, int ordre2);
char* majuscule(char* chaine);

// Ajout d'une position dans une liste de position
T_Position *ajouterPosition(T_Position *listeP, int ligne, int ordre, int phrase);

// Ajout d'une occurence dans l'arbre (ajout d'un noeud)
int ajouterOccurence(T_Index *index, char *mot, int ligne, int ordre, int phrase);




#endif //NF16_P23_2_TP4_H
