#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"


/* **********************************
 * Création et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite) {
    T_Produit *nouveauProduit = NULL;

    nouveauProduit = malloc(sizeof(T_Produit));
    if (nouveauProduit != NULL) {
        // l'allocation mémoire s'est bien passée
        nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace mémoire dédié pour notre champ de structure
        strcpy(nouveauProduit->designation,designation);
        nouveauProduit->prix = prix;
        nouveauProduit->quantite_en_stock = quantite;
        nouveauProduit->suivant = NULL;
    }

    return nouveauProduit;
}



/* ********************************
 * Création et initialisation Rayon
 ******************************** */
T_Rayon *creerRayon(char *nom) {
    T_Rayon *nouveauRayon = NULL;

    nouveauRayon = malloc(sizeof(T_Rayon));
    if (nouveauRayon != NULL) {
        // l'allocation mémoire s'est bien passée
        nouveauRayon->nom_rayon = malloc(strlen(nom) + 1);
        strcpy(nouveauRayon->nom_rayon,nom);
        nouveauRayon->liste_produits = NULL;
        nouveauRayon->suivant = NULL;
    }

    return nouveauRayon;
}



/* **********************************
 * Création et initialisation Magasin
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


/* ********************************
 * Ajout d'un rayon dans un magasin
 ******************************** */
int ajouterRayon(T_Magasin *magasin, char *nomRayon) {

    // Sélection des deux premiers rayons -> Cela va nous permettre de parcourir la liste chaînée
    T_Rayon *rayonSelec = magasin->liste_rayons;
    T_Rayon *rayonSelecSuivant = magasin->liste_rayons->suivant;

    // Retourne 0 si le nom est nul
    if(strlen(nomRayon)==0){
        printf("Impossible.\nLes Informations sont erronées .\nVeuillez recommencer.");
        return 0;
    }

    // Insertion du nouveau rayon en tête de liste
    if((magasin->liste_rayons == NULL) || (strcmp(nomRayon, rayonSelec->nom_rayon) < 0)){
        T_Rayon *nouveauRayon = creerRayon(nomRayon);
        magasin ->liste_rayons = nouveauRayon;
        nouveauRayon->suivant = rayonSelec;
        printf("Insertion du rayon en tête de liste.\n");
        return 1;
    }

    // Voir comment gérer le dernier rayon
    // Permet de trouver la place du nouveau rayon dans l'ordre alphabétique -> strcmp
    while ((strcmp(rayonSelec->nom_rayon, nomRayon) < 0) && (strcmp(nomRayon, rayonSelecSuivant->nom_rayon) < 0)) {
        // si le rayon existe déjà alors on retourne 0
        if (strcmp(nomRayon, rayonSelec->nom_rayon) == 0){
            printf("Impossible.\nLe rayon existe déjà.\n");
            return 0;
        }
        rayonSelec = rayonSelecSuivant;
        rayonSelecSuivant = rayonSelecSuivant->suivant;
    }

    // Création d'un rayon
    T_Rayon *nouveauRayon = creerRayon(nomRayon);
    // si le non du rayon est ajouté en queue de chaîne
    if (rayonSelecSuivant == NULL) {
        nouveauRayon->suivant = NULL;
        rayonSelec->suivant = nouveauRayon;
    } else {
        nouveauRayon->suivant = rayonSelecSuivant;
        rayonSelec->suivant = nouveauRayon;
    }
    printf("Le rayon est ajouté avec succès !\n");
    return 1;
}


/* ********************************
 * Ajout d'un produit dans un rayon
 ******************************** */
int ajouterProduit(T_Rayon *rayon, char *designation, float prix, int quantite) {
    T_Produit *produitSelec = rayon->liste_produits;

    // Retourne 0 si les informations sont impossibles
    if((strlen(designation)==0) || (prix <= 0) || (quantite <= 0)){
        printf("Attention les informations renseignées sont incorrectes.\nVeuillez recommencer.\n");
        return 0;
    }
    // Vérifier que le rayon existe !!

    // Insertion du produit en tête de liste
    if((rayon->liste_produits == NULL) || (prix < rayon->liste_produits->prix)){
        printf("Insertion du produit en tête de liste.\n");
        T_Produit *nouveauProduit = creerProduit(designation, prix, quantite);
        rayon->liste_produits = nouveauProduit;
        nouveauProduit->suivant = produitSelec;
        return 1;
    }

    // Emplacement du produit par prix
    while((produitSelec != NULL) && (prix >= produitSelec->suivant->prix)){
        // Vérification que le produit n'existe pas dans ce rayon
        if(strcmp(designation, produitSelec)== 0){
            printf("Impossible le produit existe déjà");
            return 0;
        }
        produitSelec = produitSelec->suivant;
    }

    // Après avoir trouvé l'emplacement création du produit
    T_Produit *nouveauProduit = creerProduit(designation, prix, quantite);

    // Attention bien relier dans le bon ordre à VERIFIER
    nouveauProduit->suivant = produitSelec->suivant;
    produitSelec->suivant = nouveauProduit;
    printf("Le produit est ajouté avec succès !\n");

    return 1;
}



/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasin(T_Magasin *magasin) {
    // TODO
}



// Fonction purement estethiques permettant de créer un tableau
void espaces(int nb){
    for(int i = 0 ; i<nb; i++)
        printf(" ");
    printf("|");
}

void sep(int nb){
    for(int i = 0; i<nb; i++){
        printf("-");
    }
    printf("\n");
}



/* *****************************************
 * Affichage de tous les produits d'un rayon
 ***************************************** */
void afficherRayon(T_Rayon *rayon) {
    if(rayon->liste_produits != NULL){
        // Affichage de la ligne d'en-tête
        int longmax = 15;
        printf("Designation");
        espaces(longmax-11);
        printf("Prix");
        espaces(15-4);
        printf("Quantité en stock");
        espaces(1);
        printf("\n");
        sep(longmax + 37);

        T_Produit *produiSelec = rayon->liste_produits;
        char prix[20];
        char quantité[20];
        while (produiSelec != NULL){

            // ATTENTION Voir les erreurs de BUFFER

            printf("%s", produiSelec->designation);
            espaces(longmax - strlen(produiSelec->designation) + longmax-11);

            // Affichage et conversion des int en chaînes de caractères
            itoa(produiSelec->prix, prix, 10);
            printf("%s euros", produiSelec->prix);
            espaces(15 - (strlen(prix)+6) );

            itoa(produiSelec->quantite_en_stock, quantité, 10);
            printf("%s", produiSelec->quantite_en_stock);
            espaces(17 - strlen(quantité));

            printf("\n");
        }
        sep(longmax+37);
    } else{
        printf("Attention, le rayon : %s, ne contient aucuns produits\n", rayon->nom_rayon);
    }
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
 * Recherche des produits se situant dans une fourchette de prix entrée par l'utilisateur
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
