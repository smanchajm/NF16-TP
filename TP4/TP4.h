//
// Created by Samuel Manchajm & Quentin Valakou on 18/05/2023.
//

#ifndef NF16_P23_2_TP4_H
#define NF16_P23_2_TP4_H
#define MAX 70 //Maximum de caractères pour un nom
#define LONGLIGNE 300 // Maximum de caractères dans une ligne

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
// Création d'une double liste chainee composée de phrase avec une phrase composée de mots
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

void afficherIndex(T_Index index);



/* ********************************
 * Fonctions principales
 ******************************** */

// Création et initialisation des structures
T_Position *creerPosition(int numeroLigne, int ordre, int numeroPhrase);
T_Noeud *creerNoeud(char *mot, int nbOccurences);
T_Index *creerIndex();

// Ajout d'une position dans une liste de position
T_Position *ajouterPosition(T_Position *listeP, int ligne, int ordre, int phrase);

// Ajout d'une occurence dans l'arbre (ajout d'un noeud)
int ajouterOccurence(T_Index *index, char *mot, int ligne, int ordre, int phrase);

// Indexation de tous les mots du fichier
int indexerFichier(T_Index *index, char *filename);

// Affichage de tous les mots de l'index
void afficherIndex(T_Index index);

// Recherche d'un mot dans l'index
T_Noeud* rechercherMot(T_Index *index, char* character);
T_Noeud *rechercherMotOccurence(T_Index *index, char *mot);

// Affichage de toutes les occurences d'un mot
void afficherOccurencesMot(T_Index *index, char *mot);

// Construction du texte à partir d'un index de type ABR
void construireTexte(T_Index *index, char *filename);


/* ********************************
 * Fonctions utilitaires
 ******************************** */

// Comparaison de deux mots
int comparaison(int ligne1, int ordre1, int ligne2, int ordre2);
void parcours_recherche(T_Noeud* noeud, char lettre, char* tab, int i);

int parcoursABR(T_Noeud *noeud, T_listePhrases * liste);
void parcours_affichage(T_Noeud* noeud, char lettre);

// Fonctions d'indexations de la liste chainee
T_listePhrases *indexerListe(T_Index *index);
int parcoursABRSam(T_Noeud *noeud, T_listePhrases * liste);
int ajouterPhraseMot(T_listePhrases *index, char *mot, int numPhrase, int ordre, int ligne);
int ajouterMot(T_Phrase *phrase, char *mot, int ordre, int ligne);


void menu();

void viderABR(T_Noeud *noeud);
void viderIndex(T_Index *index);

void viderListePhrases(T_listePhrases *listePhrases);

#endif //NF16_P23_2_TP4_H
