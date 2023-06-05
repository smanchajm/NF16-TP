//
// Created by samma on 18/05/2023.
//

#ifndef NF16_P23_2_TP4_H
#define NF16_P23_2_TP4_H
#define MAX 70 //Maximum de caractères pour un nom
#define LONGLIGNE 100

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
    struct Noeud *filsDroit;
};
typedef struct Noeud T_Noeud;

struct Index {
    T_Noeud *racine;
    int nbMotsDistincts;
    int nbMotsTotal;
};
typedef struct Index T_Index;

// Structures particulières pour les questions 6 et 7

struct Mot {
    char *mot;
    struct Mot *suivant;
    int ordre;
    int ligne;
};
typedef struct Mot T_Mot;

struct Phrase {
    struct Mot *listeMot;
    struct Phrase *suivant;
    int indice;
    int nbMots;
};
typedef struct Phrase T_Phrase;

struct listePhrases {
    struct Phrase *listePhrase;
    int nbLignes;

};
typedef struct listePhrases T_listePhrases;



typedef struct LectureTexte {
    char* mot;
    struct LectureTexte* suivant;
}T_LectureTexte;




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

int indexerFichier(T_Index *index, char *filename);

void construireTexte(T_Index index, char *filename);

void afficherIndex(T_Index index);

void parcoursABR(T_Noeud *noeud, char lettre);
int parcoursABRSam(T_Noeud *noeud, T_listePhrases * liste);

T_listePhrases *indexerListe(T_Index *index);

void afficher_arbre(T_Noeud *racine, int prof);

int ajouterPhraseMot(T_listePhrases *index, char *mot, int numPhrase, int ordre, int ligne);
int ajouterMot(T_Phrase *phrase, char *mot, int ordre, int ligne);
void afficherTexte(T_listePhrases *index);
void afficherPos(T_Index *index);



#endif //NF16_P23_2_TP4_H
