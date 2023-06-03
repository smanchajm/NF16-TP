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


/* **********************************
 * Création et initialisation des structures listes
 ********************************** */


T_Mot *creerMot(char *nom){
    T_Mot *nouveauMot = NULL;
    nouveauMot = malloc(sizeof(T_Mot));

    if (nouveauMot){
        nouveauMot->suivant = NULL;
        nouveauMot->mot = malloc(strlen(nom) + 1);
        strcpy(nouveauMot->mot,nom);
    }

    return nouveauMot;
}

T_Phrase *creerPhrase(){
    T_Phrase *nouvellePhrase = NULL;
    nouvellePhrase = malloc(sizeof(T_Phrase));

    if (nouvellePhrase){
        nouvellePhrase->listeMot = NULL;
        nouvellePhrase->suivant = NULL;
        nouvellePhrase->nbMots = 0;
    }

    return nouvellePhrase;
}

T_listePhrases *creerIndexPhrases(){
    T_listePhrases *nouveauIndexPhrases = NULL;
    nouveauIndexPhrases = malloc((sizeof (T_listePhrases)));
    if (nouveauIndexPhrases){
        nouveauIndexPhrases->nbLignes = 0;
        nouveauIndexPhrases->listePhrase = NULL;
    }

    return nouveauIndexPhrases;
}

// Fonction permettant de comparer deux mots en fonction de leurs positions
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
    if((ligne < 0) || (ordre < 0) || (phrase < 0)){
        printf("Impossible. Les informations sont erronees. \n");
        return NULL;
    }

    // Première comparaison pour la tête
    if((listeP != NULL) && (listeP->numeroLigne == ligne) && (listeP->ordre == ordre) && (listeP->numeroPhrase == phrase)){
        printf("Impossible. La position est deja renseignee.\n");
        return NULL;
    }

    // Insertion de la position en tête de liste
    // VOIR si ordre sup égal ou pas
    if((listeP == NULL) || (comparaison(ligne, ordre, listeP->numeroLigne, listeP->ordre) == 1)){
        T_Position *nouvellePosition = creerPosition(ligne, ordre, phrase);
        T_Position *tmp = listeP;
        nouvellePosition->suivant = tmp;
        printf("Insertion du mot en tete de liste.\n");
        printf("3");
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
        printf("1");
        index->racine = creerNoeud(mot, 0);
        index->racine->listePositions = ajouterPosition(index->racine->listePositions, ligne, ordre, phrase);
        index->racine->nbOccurences ++;
        printf("2");
        return 1;
    }

    T_Noeud *noeudPere = NULL;
    T_Noeud *noeudSelec = index->racine;

    while ((noeudSelec != NULL)){
        printf("5");
        if(strcasecmp(noeudSelec->mot, mot) == 0){
            T_Position *listePos = ajouterPosition(noeudSelec->listePositions, ligne, ordre, phrase);
            if(listePos == NULL){
                printf("Impossible l'occurence de ce mot est deja renseignee.\n");
                return 0;
            }
            noeudSelec->nbOccurences++;
            return 1;
        }
        noeudPere = noeudSelec;

        if(strcasecmp(noeudSelec->mot, mot) < 0){
            noeudSelec = noeudSelec->filsGauche;
            printf("G");
        } else{
            printf("D");
            noeudSelec = noeudSelec->filsDroit;
        }
    }

    if(strcasecmp(noeudPere->mot, mot) < 0){
        noeudPere->filsGauche = creerNoeud(mot, 0);
        noeudPere->filsGauche->listePositions = ajouterPosition(noeudPere->filsGauche->listePositions, ligne, ordre, phrase);
        noeudPere->filsGauche->nbOccurences++;
    } else{
        noeudPere->filsDroit = creerNoeud(mot, 0);
        noeudPere->filsDroit->listePositions = ajouterPosition(noeudPere->filsDroit->listePositions, ligne, ordre, phrase);
        noeudPere->filsDroit->nbOccurences++;
    }

    return 1;
}



/* ********************************
 * Indexation du fichier
 ******************************** */
// attention doit se finir par un point ou un saut de ligne
int indexerFichier(T_Index *index, char *filename){
    // Initialisation des compteurs pour ajouter les occurences aux bonnes positions
    int cmptMot = 0, cmptPhrase = 0, cmptOrdre = 0, cmptLigne = 0;

    FILE *fichier = NULL;
    // Ouverture du fichier
    fichier = fopen(filename, "r");
    char  ligne[LONGLIGNE];

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 0;
    }

    // Parcours de toutes les lignes du fichier
    while (fgets(ligne, LONGLIGNE, fichier) != NULL) {
        // Il faut donc récup le mot sa ligne son ordre et sa phrase
        int j = 0;
        cmptOrdre++;
        char mot[MAX];
        char charSel;

        // Récupération de tous les caractères d'un mot
        for (int i = 0; i < strlen(ligne); ++i) {
            charSel = ligne[i];

            if ((charSel != '\n') && (charSel != '.') && (charSel != ' ')) { // Ce n'est pas la fin du mot
                mot[j] = charSel;
                j++;
            } else{ // C'est la fin d'un mot
                if (strlen(mot) != 0){
                    // On ajoute le mot à l'ABR
                    printf("\n%s\n", mot);
                    ajouterOccurence(index, mot, cmptLigne, cmptOrdre, cmptPhrase);
                    printf("4");
                    cmptMot++;
                }
                cmptOrdre++;
                for (j = 0; j < MAX; j++) {
                    mot[j] = '\0';
                }
                j = 0;
            }
            // Si on lit un point alors on incrémente le nb de phrases
            if (charSel == '.'){
                cmptPhrase++;
            }
        }
        cmptLigne++;
        cmptOrdre = 0;
    }
    // Fermeture du fichier
    fclose(fichier);
    return cmptMot;
}


/* ********************************
 * Recherche d'un mot
 ******************************** */

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

/* ********************************
 * Construction du texte
 ******************************** */
int parcoursABR(T_Noeud *noeud) {
    if (noeud != NULL) {
        printf("Mot: %s, Occurrences: %d\n", noeud->mot, noeud->nbOccurences);
        T_Position *posSelec = noeud->listePositions;
        while (posSelec){
            // Insertion dans une double liste chaînée -> trouver si la phrase existe et soit la créer, soit juste ajouter le mot




            posSelec = posSelec->suivant;
        }

        parcoursABR(noeud->filsDroit);
        parcoursABR(noeud->filsGauche);
    }
}
void indexerListe(T_Index *index){
    // Parcourir tous les éléments de l'ABR et toutes les positions
    // Les ajouter à la liste chainée de phrases en fonction du numéro de la phrase et de l'ordre
    if (index->racine == NULL){
        printf("Attention l'index est nul");
        return;
    }
    parcoursABR(index->racine);



}


void construireTexte(T_Index index, char *filename){
    // 1. Indexer les nouvelles structures
    // 2. Creer un nouveau fichier et l'ouvrir
    // 3. Ecrire chaque mot dans un fichier


}