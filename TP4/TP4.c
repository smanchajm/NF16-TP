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


T_Mot *creerMot(char *nom, int ordre, int ligne){
    T_Mot *nouveauMot = NULL;
    nouveauMot = malloc(sizeof(T_Mot));

    if (nouveauMot){
        nouveauMot->ordre = ordre;
        nouveauMot->ligne = ligne;
        nouveauMot->suivant = NULL;
        nouveauMot->mot = malloc(strlen(nom) + 1);
        nom[0] = tolower(nom[0]);
        strcpy(nouveauMot->mot, nom);
    }

    return nouveauMot;
}

T_Phrase *creerPhrase(int indice){
    T_Phrase *nouvellePhrase = NULL;
    nouvellePhrase = malloc(sizeof(T_Phrase));

    if (nouvellePhrase){
        nouvellePhrase->indice = indice;
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
    return listeP;
}

/* ********************************
 * Ajout d'une Occurence d'un mot dans l'arbre
 ******************************** */
int ajouterOccurence(T_Index *index, char *mot, int ligne, int ordre, int phrase){

    if(index->racine == NULL){
        // REVOIR LISTEPOS
        index->racine = creerNoeud(mot, 0);
        index->racine->listePositions = ajouterPosition(index->racine->listePositions, ligne, ordre, phrase);
        index->racine->nbOccurences ++;
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
            noeudSelec->nbOccurences++;
            return 1;
        }
        noeudPere = noeudSelec;

        if(strcasecmp(noeudSelec->mot, mot) > 0){
            noeudSelec = noeudSelec->filsGauche;
        } else{
            noeudSelec = noeudSelec->filsDroit;
        }
    }

    if(strcasecmp(noeudPere->mot, mot) > 0){
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
    char mot[MAX];
    memset(mot, 0, sizeof(mot));


    // Parcours de toutes les lignes du fichier
    while (fgets(ligne, LONGLIGNE, fichier) != NULL) {
        // Il faut donc récup le mot sa ligne son ordre et sa phrase
        int j = 0;
        char charSel;
        cmptOrdre = 1;


        // Récupération de tous les caractères d'un mot
        for (int i = 0; i < strlen(ligne); ++i) {
            charSel = '\0';
            charSel = ligne[i];

            if ((charSel != '\n') && (charSel != '.') && (charSel != ' ') && (charSel != EOF)) { // Ce n'est pas la fin du mot
                mot[j] = charSel;
                j++;
            } else{ // C'est la fin d'un mot
                if (strlen(mot) != 0){
                    // On ajoute le mot à l'ABR
                    ajouterOccurence(index, mot, cmptLigne, cmptOrdre, cmptPhrase);
                    cmptMot++;
                }
                cmptOrdre++;
                memset(mot, 0, sizeof(mot));
                j = 0;
            }
            // Si on lit un point alors on incrémente le nb de phrases
            if (charSel == '.'){
                cmptPhrase++;
                cmptOrdre--;
            }
        }
        cmptLigne++;
    }
    // Fermeture du fichier
    fclose(fichier);
    return cmptMot;
}

void parcours_recherche(T_Noeud* noeud, char lettre, char* tab, int i){
    T_Noeud* currentpos = noeud;
    if (noeud != NULL){
        if (strncmp(noeud->mot,&lettre,1) == 0){
            if (tab[i] != lettre) {printf("%c \n", lettre);}
            printf("|-- %s \n", noeud->mot);
            T_Position * tempPositions = noeud->listePositions;
            while (tempPositions != NULL){
                printf("|--- (l:%d, o:%d, p:%d) \n", tempPositions->numeroLigne, tempPositions->ordre, tempPositions->numeroPhrase);
                tempPositions = tempPositions->suivant;
            }
            tab[i] = lettre;
        }
        parcours_recherche(noeud->filsGauche, lettre, tab, i);
        parcours_recherche(noeud->filsDroit, lettre, tab, i);
    }
    else {
        return;
    }
}


void afficherIndex(T_Index index){
    T_Noeud* current = index.racine;
    char tab[30];
    int i = 0;
    if (index.racine == NULL){
        printf("L'index est vide\n");
        return;
    }
    char current_char = 97;
    while (current_char < 123) {
        parcours_recherche(current, current_char,tab, i);
        i ++;
        current_char ++;
    }
}

/* ********************************
 * Recherche d'un mot
 ******************************** */

T_Noeud* rechercherMot(T_Index* index, char* mot) {
    int hauteur_index = 0;

    if (index == NULL) {
        return NULL;
    }
    if (strcasecmp(index->racine->mot, mot) == 0) {
        T_Position* tampon = index->racine;
        //printf("Mot trouve a la hauteur %d", hauteur_index);
        while(tampon != NULL) {
            printf("num ligne : %d | ordre : %d | num phrase : %d \n", tampon->numeroLigne, tampon->ordre, tampon->numeroPhrase);
            tampon = tampon->suivant;
        }
        return index->racine;
    }

    T_Noeud *current = index->racine;

    while (current != NULL) {
        printf("%s \n",current->mot);
        printf("%d \n", strcasecmp(current->mot, mot));
        if (strcasecmp(current->mot, mot) == 0) {
            printf("Mot trouve e la hauteur %d \n", hauteur_index);

            T_Position* tempPositions = current->listePositions;
            while(tempPositions != NULL) {
                printf("num ligne : %d | ordre : %d | num phrase : %d \n", tempPositions->numeroLigne, tempPositions->ordre, tempPositions->numeroPhrase);
                tempPositions = tempPositions->suivant;
            }
            return current;

        } else if (strcasecmp(current->mot, mot) > 0) {
            if (current->filsGauche != NULL) {
                current = current->filsGauche;
            } else {
                printf("Non trouvé, le mot n'existe pas");
                return NULL;
            }
        } else {
            if (current->filsDroit != NULL) {
                current = current->filsDroit;
            } else {
                printf("Non trouvé, le mot n'existe pas");
                return NULL;
            }
        }
        hauteur_index++;
    }
}

T_Noeud *rechercherMotOccurence(T_Index *index, char *mot) {

    T_Noeud* ptr = index->racine;
    while (ptr != NULL) {
        if (strcasecmp(ptr->mot, mot) == 0) {
            return ptr;
        } else if (strcasecmp(ptr->mot, mot) < 0) {
            ptr = ptr->filsDroit;
        } else {
            ptr = ptr->filsGauche;
        }
    }
    return NULL;
}


/* ********************************
 * Construction du texte
 ******************************** */

int ajouterMot(T_Phrase *phrase, char *mot, int ordre, int ligne){
    // Insertion du nouveau rayon en tête de liste
    if (( phrase->listeMot != NULL) && (ordre == phrase->listeMot->ordre) && (ligne == phrase->listeMot->ligne)){
        printf("Impossible. Le mot est deja renseignee.\n");
        return 0;
    }
    if( phrase->listeMot == NULL) {
        // Si la liste triée est vide, le nouveau mot devient la tête de la liste
        T_Mot *nouvMot = creerMot(mot,ordre, ligne);
        T_Mot *tmp = phrase->listeMot;
        phrase->listeMot = nouvMot;
        nouvMot->suivant = tmp;
        return 1; }


    if((ligne < phrase->listeMot->ligne || (ligne == phrase->listeMot->ligne && ordre < phrase->listeMot->ordre))){
        T_Mot *nouvMot = creerMot(mot,ordre, ligne);
        T_Mot *tmp = phrase->listeMot;
        phrase->listeMot = nouvMot;
        nouvMot->suivant = tmp;
        //printf("Insertion du mot en tete de liste.\n");
        return 1;
    }

    // Selection des deux premiers mots -> Cela va nous permettre de parcourir la liste chaÃ®nÃ©e
    T_Mot *motSelec = phrase->listeMot;
    T_Mot *motSelecSuivant = phrase->listeMot->suivant;

    // Permet de trouver la place du nouveau rayon dans l'ordre alphabÃ©tique
    while ((motSelecSuivant != NULL && (ligne > motSelecSuivant->ligne || (ligne == motSelecSuivant->ligne && ordre > motSelecSuivant->ordre)))){
        motSelec = motSelecSuivant;
        motSelecSuivant = motSelecSuivant->suivant;
    }

    // Si le mot existe déjà, on retourne 0
    if (motSelecSuivant != NULL && ordre == motSelecSuivant->ordre && ligne == motSelecSuivant->ligne) {
        printf("Impossible le mot existe deja\n");
        return 0;
    }

    // Création d'un mot
    T_Mot *nouvMot = creerMot(mot,ordre, ligne);
    nouvMot->suivant = motSelecSuivant;
    motSelec->suivant = nouvMot;
    return 1;

}


int ajouterPhraseMot(T_listePhrases *index, char *mot, int numPhrase, int ordre, int ligne) {


    // Insertion du nouveau rayon en tête de liste
    if (( index->listePhrase != NULL) && (numPhrase == index->listePhrase->indice)){
        ajouterMot(index->listePhrase, mot, ordre, ligne);
        index->listePhrase->nbMots++;
        return 1;
    }
    if((index->listePhrase == NULL) || ( numPhrase < index->listePhrase->indice )){
        T_Phrase *nouvPhrase = creerPhrase(numPhrase);
        T_Phrase *tmp = index->listePhrase;
        index->listePhrase = nouvPhrase;
        nouvPhrase->suivant = tmp;
        ajouterMot(index->listePhrase, mot, ordre, ligne);
        index->listePhrase->nbMots++;
        return 1;
    }

    // Selection des deux premières -> Cela va nous permettre de parcourir la liste chaÃ®nÃ©e
    T_Phrase *phraseSelec = index->listePhrase;
    T_Phrase *phraseSelecSuivant = index->listePhrase->suivant;

    // Permet de trouver la place du nouveau rayon dans l'ordre alphabÃ©tique -> strcmp
    while (phraseSelecSuivant != NULL && numPhrase > phraseSelecSuivant->indice) {
        phraseSelec = phraseSelecSuivant;
        phraseSelecSuivant = phraseSelecSuivant->suivant;
    }

    if (phraseSelecSuivant != NULL && numPhrase == phraseSelecSuivant->indice) {
        ajouterMot(phraseSelecSuivant, mot, ordre, ligne);
        phraseSelecSuivant->nbMots++;
        return 1;
    }

    T_Phrase *nouvellePhrase = creerPhrase(numPhrase);
    nouvellePhrase->suivant = phraseSelecSuivant;
    phraseSelec->suivant = nouvellePhrase;
    ajouterMot(nouvellePhrase, mot, ordre, ligne);
    nouvellePhrase->nbMots++;
    return 1;
}




int parcoursABRSam(T_Noeud *noeud, T_listePhrases * liste) {
    if (noeud != NULL) {
        T_Position *posSelec = malloc(sizeof(T_Position));
        posSelec = noeud->listePositions;
        while (posSelec){
            // Insertion dans une double liste chaînée -> trouver si la phrase existe et soit la créer, soit juste ajouter le mot
            ajouterPhraseMot(liste, noeud->mot, posSelec->numeroPhrase, posSelec->ordre, posSelec->numeroLigne);
            posSelec = posSelec->suivant;
        }
        parcoursABRSam(noeud->filsDroit, liste);
        parcoursABRSam(noeud->filsGauche, liste);

    }
}

T_listePhrases *indexerListe(T_Index *index){
    // Parcourir tous les éléments de l'ABR et toutes les positions
    // Les ajouter à la liste chainée de phrases en fonction du numéro de la phrase et de l'ordre
    if (index->racine == NULL){
        printf("Attention l'index est nul");
        return NULL;

    }
    T_listePhrases *liste = creerIndexPhrases();
    parcoursABRSam(index->racine, liste);
    return liste;
}



void construireTexte(T_Index *index, char *filename){
    // 1. Indexer les nouvelles structures
    // 2. Creer un nouveau fichier et l'ouvrir
    // 3. Ecrire chaque mot dans un fichier
    T_listePhrases *texte = indexerListe(index);
    T_Phrase *phraseSelec = texte->listePhrase;
    if (texte != NULL){
        FILE *fichier = fopen(filename, "w");  // Ouverture du fichier en mode écriture
        if (fichier == NULL) {
            printf("Impossible d'ouvrir le fichier.\n");
            return;
        }
        while (phraseSelec != NULL){
            int flag = 1;
            T_Mot *motSelec = phraseSelec->listeMot;
            while (motSelec){

                if (flag == 1){
                    char *motMaj = motSelec->mot;
                    motMaj[0] = toupper(motMaj[0]);
                    flag = 0;
                    fputs(motMaj, fichier);
                    fputs(" ", fichier);
                } else if (motSelec->suivant == NULL){
                    fputs(motSelec->mot, fichier);
                    fputs(".", fichier);
                    fputs(" ", fichier);
                }
                else{
                    fputs(motSelec->mot, fichier);
                    fputs(" ", fichier);
                }
                if (motSelec->suivant!= NULL && motSelec->ligne != motSelec->suivant->ligne){
                    fputs("\n", fichier);
                }
                motSelec = motSelec->suivant;
            }
            phraseSelec = phraseSelec->suivant;
        }
        fclose(fichier);  // Fermeture du fichier
    }


}




/* ********************************
 * Affichage des occurences d'un mot
 ******************************** */

void afficherOccurencesMot(T_Index *index, char *mot) {
    T_Noeud* noeud = rechercherMotOccurence(index, mot);
    if (noeud == NULL) {
        printf("\nLe mot %s n'est pas dans l'index.\n", mot);
    }
    else {
        T_Position *pos = noeud->listePositions;
        T_listePhrases *texte = indexerListe(index);
        T_Phrase *phrase = texte->listePhrase;
        printf("\n\nMot = %s\n", noeud->mot);
        printf("Occurences = %d\n", noeud->nbOccurences);
        while (pos!= NULL){
            while (phrase->indice != pos->numeroPhrase){
                phrase = phrase->suivant;
            }
            char phraseReconstitue[LONGLIGNE] = "";
            T_Mot *motSelec = phrase->listeMot;
            int flag = 1;

            while (motSelec != NULL){
                if (flag == 1){
                    char *motMaj = motSelec->mot;
                    motMaj[0] = toupper(motMaj[0]);
                    strcat(phraseReconstitue, motMaj);
                    flag = 0;
                } else {
                    strcat(phraseReconstitue, " ");
                    strcat(phraseReconstitue, motSelec->mot);
                    if (motSelec->suivant == NULL) {
                        strcat(phraseReconstitue, ".");
                    }
                }
                motSelec = motSelec->suivant;
            }
            printf("| Ligne %d, Mot %d : %s\n", pos->numeroLigne, pos->ordre, phraseReconstitue);


            pos = pos->suivant;

        }
    }

}



/* ********************************
 * Utilitaire
 ******************************** */

void viderABR(T_Noeud *noeud) {
    if (noeud != NULL) {
        viderABR(noeud->filsGauche);
        viderABR(noeud->filsDroit);
        free(noeud->mot);
        free(noeud);
    }
}


void viderIndex(T_Index *index) {
    // Vider les listes
    T_Noeud *noeud = index->racine;
    while (noeud != NULL) {
        T_Position *position = noeud->listePositions;
        while (position != NULL) {
            T_Position *suivant = position->suivant;
            free(position);
            position = suivant;
        }
        noeud->listePositions = NULL;
        noeud = noeud->filsDroit;
    }

    // Vider les ABR
    viderABR(index->racine);

    // Réinitialiser l'index
    index->racine = NULL;
    index->nbMotsDistincts = 0;
    index->nbMotsTotal = 0;
}

void viderListePhrases(T_listePhrases *listePhrases) {
    T_Phrase *phrase = listePhrases->listePhrase;
    while (phrase != NULL) {
        T_Mot *mot = phrase->listeMot;
        while (mot != NULL) {
            T_Mot *suivant = mot->suivant;
            free(mot->mot);
            free(mot);
            mot = suivant;
        }
        T_Phrase *suivante = phrase->suivant;
        free(phrase);
        phrase = suivante;
    }
    listePhrases->listePhrase = NULL;
    listePhrases->nbLignes = 0;
}

