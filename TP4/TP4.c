#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TP4.h"

/* **********************************
 * Création et initialisation Position
 ********************************** */

T_Position *creerPosition(int numeroLigne, int ordre, int numeroPhrase){
    T_Position *nouvellePosition = NULL;

    nouvellePosition = malloc(sizeof(T_Position));
    if (nouvellePosition != NULL){
        nouvellePosition->numeroLigne = numeroLigne;
        nouvellePosition->ordre = ordre;
        nouvellePosition->numeroPhrase = numeroPhrase;
        nouvellePosition->suivant = NULL;
    }

    return nouvellePosition;
}

/* **********************************
 * Création et initialisation Noeud
 ********************************** */

T_Noeud *creerNoeud(char *mot, int nbOccurences){
    T_Noeud *nouveauNoeud = NULL;

    nouveauNoeud = malloc(sizeof(T_Noeud));
    if(nouveauNoeud != NULL){
        nouveauNoeud->mot = malloc(strlen(mot) + 1);
        strcpy(nouveauNoeud->mot, mot);
        nouveauNoeud->nbOccurences = nbOccurences;
        nouveauNoeud->listePositions = NULL;
        nouveauNoeud->filsGauche = NULL;
        nouveauNoeud->filsDroit = NULL;
    }

    return nouveauNoeud;
}

/* **********************************
 * Création et initialisation Index
 ********************************** */

T_Index *creerIndex(){
    T_Index *nouveauIndex = NULL;

    nouveauIndex = malloc(sizeof(T_Index));
    if(nouveauIndex){
        nouveauIndex->racine = NULL;
        nouveauIndex->nbMotsDistincts = 0;
        nouveauIndex->nbMotsTotal = 0;
    }

    return nouveauIndex;
}

int comparaison(int ligne1, int ordre1, int ligne2, int ordre2){
    if(ligne1 == ligne2){
        if(ordre1 == ordre2){
            return 0;
        } else if(ordre1 < ordre2) {
            return 1;
        }
        return 2;

    } else if(ligne1 < ligne2){
        return 1;
    }
    return 2;
}

/* ********************************
 * Ajout d'une position dans une liste de positions
 ******************************** */

T_Position *ajouterPosition(T_Position *listeP, int ligne, int ordre, int phrase){
    if((ligne <= 0) || (ordre <= 0) || (phrase <= 0)){
        printf("Impossible. Les informations sont erronees. \n");
        return 0;
    }

    // Première comparaison pour la tête
    if((listeP != NULL) && (listeP->numeroLigne == ligne) && (listeP->ordre == ordre) && (listeP->numeroPhrase == phrase)){
        printf("Impossible. La position est deja renseignee.\n");
        return 0;
    }

    // Insertion de la position en tête de liste
    // VOIR si ordre sup égal ou pas
    if((listeP == NULL) || (comparaison(ligne, ordre, listeP->numeroLigne, listeP->ordre) == 1)){
        T_Position *nouvellePosition = creerPosition(ligne, ordre, phrase);
        T_Position *tmp = listeP;
        nouvellePosition->suivant = tmp;
        printf("Insertion du mot en tete de liste.\n");
        return nouvellePosition;
    }

    // Selection des deux premieres positions pour parcourir la liste
    T_Position *posSelec = listeP;
    T_Position *posSelecSuivant = listeP->suivant;

    while ((posSelecSuivant != NULL) && (comparaison(ligne, ordre, posSelecSuivant->numeroLigne, posSelecSuivant->ordre) != 1)){
        posSelec = posSelecSuivant;
        posSelecSuivant = posSelecSuivant->suivant;
    }

    // Si la position existe deja, alors le mot est deja rentre
    if(posSelecSuivant != NULL && (comparaison(ligne, ordre, posSelecSuivant->numeroLigne, posSelecSuivant->ordre) == 0)){
        printf("Impossible l'occurence de ce mot est deja rentre.\n");
        return NULL;
    }

    // Creation d'une position
    T_Position *nouvellePosition = creerPosition(ligne, ordre, phrase);
    nouvellePosition->suivant = posSelecSuivant;
    posSelec->suivant = nouvellePosition;
    printf("Nouvelle position ajoutée avec succes !\n");
    return listeP;
}

/* ********************************
 * Ajout d'une Occurence d'un mot dans l'arbre
 ******************************** */
int ajouterOccurence(T_Index *index, char *mot, int ligne, int ordre, int phrase){

    if(index->racine == NULL){
        // REVOIR LISTEPOS
        index->racine->listePositions = ajouterPosition(NULL, ligne, ordre, phrase);
        return 1;
    }

    T_Noeud *noeudPere = NULL;
    T_Noeud *noeudSelec = index->racine;

    while ((noeudSelec != NULL)){
        if(strcasecmp(noeudSelec->mot, mot) == 0){
            T_Position *listePos = ajouterPosition(noeudSelec->listePositions, ligne, ordre, phrase);
            if(listePos == NULL){
                printf("Impossible l'occurence de ce mot est deja renseignee.\n");
                return 0;
            }
        }
        noeudPere = noeudSelec;

        if(strcasecmp(noeudSelec->mot, mot) < 0){
            noeudSelec = noeudSelec->filsGauche;
        } else{
            noeudSelec = noeudSelec->filsDroit;
        }
    }

    if(strcasecmp(noeudSelec->mot, mot) < 0){
        noeudPere->filsGauche = creerNoeud(mot, 0);
        noeudPere->filsGauche->listePositions = ajouterPosition(noeudPere->filsGauche->listePositions, ligne, ordre, phrase);
    } else{
        noeudPere->filsDroit = creerNoeud(mot, 0);
        noeudPere->filsDroit->listePositions = ajouterPosition(noeudPere->filsDroit->listePositions, ligne, ordre, phrase);
    }

    return 1;
}



/* ********************************
 * Indexation du fichier
 ******************************** */
int indexerFichier(T_Index *index, char *filename){

    FILE *fichier = NULL;
    fichier = fopen(filename, "r");
    char  ligne[LONGLIGNE];


}

T_Noeud* rechercherMot(T_Index* index, char* mot){
    int hauteur_index = 0;

    if (index == NULL){
        return 0;
    }
    if (strcasecmp(index->racine->mot, mot) == 0){
        printf("Mot trouvé à la hauteur %d", hauteur_index);
        return index->racine;
    }

    T_Noeud* current = index->racine;

    while(current != NULL){
        if (strcasecmp(current->mot, mot) == 0){
            printf("Mot trouvé à la hauteur %d", hauteur_index);
            return current;
        }
        else if (strcasecmp(current->mot, mot) < 0) {
            if (current->filsGauche != NULL) {
                current = current->filsGauche;
            }
            else {
                printf("Non trouvé, le mot n'existe pas");
                return 0;
            }
        }
        else {
            if (current->filsDroit != NULL) {
                current = current->filsDroit;
            }
            else {
                printf("Non trouvé, le mot n'existe pas");
                return 0;
            }
        }
        hauteur_index ++;
    }
}