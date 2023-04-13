#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"


/* **********************************
 * Cr�ation et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite) {
    T_Produit *nouveauProduit = NULL;

    nouveauProduit = malloc(sizeof(T_Produit));
    if (nouveauProduit != NULL) {
        // l'allocation m�moire s'est bien pass�e
        nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace m�moire d�di� pour notre champ de structure
        strcpy(nouveauProduit->designation,designation);
        nouveauProduit->prix = prix;
        nouveauProduit->quantite_en_stock = quantite;
        nouveauProduit->suivant = NULL;
    }

    return nouveauProduit;
}



/* ********************************
 * Cr�ation et initialisation Rayon
 ******************************** */
T_Rayon *creerRayon(char *nom) {
    T_Rayon *nouveauRayon = NULL;

    nouveauRayon = malloc(sizeof(T_Rayon));
    if (nouveauRayon != NULL) {
        // l'allocation m�moire s'est bien pass�e
        nouveauRayon->nom_rayon = malloc(strlen(nom) + 1);
        strcpy(nouveauRayon->nom_rayon,nom);
        nouveauRayon->liste_produits = NULL;
        nouveauRayon->suivant = NULL;
    }

    return nouveauRayon;
}



/* **********************************
 * Cr�ation et initialisation Magasin
 ********************************** */
T_Magasin *creerMagasin(char *nom) {
    T_Magasin *nouveauMagasin = NULL;

    nouveauMagasin = malloc(sizeof(T_Magasin));
    if (nouveauMagasin != NULL) {
        nouveauMagasin->nom = malloc(strlen(nom) + 1);
        strcpy(nouveauMagasin->nom,nom);
        nouveauMagasin->liste_rayons = NULL;
    }

    return nouveauMagasin;
}

// fonction de permettant de comparer deux mots aphab�tiquement
int ordreAlpha(char *nom1, char *nom2){
    // retourne 1 si le premier nom est avant le deuxi�me nom
    if(nom1[1] < nom2[1]){
        return 1;
    } else if (nom1[1] > nom2[1]){
        return 2;
    }
    // si les deux mots sont �gaux on retourne 0
    else if(*nom1 == *nom2){
        return 0;
    }
    // si les deux premiers caract�res sont �gaux, nous comparons les mots en enlevant le premier caract�re
    return ordreAlpha(nom1+1, nom2+1);
}


/* ********************************
 * Ajout d'un rayon dans un magasin
 ******************************** */
int ajouterRayon(T_Magasin *magasin, char *nomRayon) {
    // Cr�ation d'un rayon
    T_Rayon *nouveauRayon = creerRayon(nomRayon);
    T_Rayon *rayonSelec = magasin->liste_rayons;
    T_Rayon *rayonSelecSuivant = magasin->liste_rayons->suivant;
    // Permet de trouver la place du nouveau rayon dans l'ordre alphab�tique -> strcmp
    while ((strcmp(rayonSelec->nom_rayon, nouveauRayon->nom_rayon) < 0) && (strcmp(nouveauRayon->nom_rayon, rayonSelecSuivant->nom_rayon) < 0)){
        rayonSelec = rayonSelecSuivant;
        rayonSelecSuivant = rayonSelecSuivant->suivant;
        // si le rayon existe d�j� alors on retourne 0
        if(strcmp(nouveauRayon->nom_rayon, rayonSelec->nom_rayon) == 0) return 0;
    }
    // si le non du rayon est ajout� en queue de cha�ne
    if(rayonSelecSuivant == NULL){
        nouveauRayon->suivant = NULL;
        rayonSelec->suivant = nouveauRayon;
    } else{
        nouveauRayon->suivant = rayonSelecSuivant;
        rayonSelec->suivant = nouveauRayon;
    }
    return 1;
}



/* ********************************
 * Ajout d'un produit dans un rayon
 ******************************** */
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite) {
    // TODO

    return 1;
}



/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasin(T_Magasin *magasin) {
    // TODO
}



/* *****************************************
 * Affichage de tous les produits d'un rayon
 ***************************************** */
void afficherRayon(T_Rayon *rayon) {
    // TODO
}



/* **************************************
 * Suppression d'un produit dans un rayon
 ************************************** */
int supprimerProduit(T_Rayon *rayon, char* designation_produit) {
    // TODO
    return 1;
}



/* *************************************************************
 * Suppression d'un rayon et de tous les produits qu'il contient
 ************************************************************* */
int supprimerRayon(T_Magasin *magasin, char *nom_rayon) {
    // TODO
    return 1;
}



/* **************************************************************************************
 * Recherche des produits se situant dans une fourchette de prix entr�e par l'utilisateur
 ************************************************************************************** */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max) {
    // TODO
}



/* *********************
 * Fusionner deux rayons
 ********************* */
void fusionnerRayons(T_Magasin *magasin) {
    // TODO
}



/* *********************
 * Fonctions utilitaires
 ********************* */
// Vider le buffer (utile quand on utlise des getchar() )
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
