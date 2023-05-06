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


/* ********************************
 * Ajout d'un rayon dans un magasin
 ******************************** */
int ajouterRayon(T_Magasin *magasin, char *nomRayon) {

    // Retourne 0 si le nom est nul
    if(strlen(nomRayon)==0){
        printf("Impossible.\nLes Informations sont erronees .\nVeuillez recommencer.");
        return 0;
    }

    // Insertion du nouveau rayon en t�te de liste
    if ((magasin->liste_rayons != NULL) && strcmp(nomRayon, magasin->liste_rayons->nom_rayon) == 0){
        printf("Impossible.\nLe rayon existe deja.\n");
        return 0;
    }
    if((magasin->liste_rayons == NULL) || (strcmp(nomRayon, magasin->liste_rayons->nom_rayon) < 0)){
        T_Rayon *nouveauRayon = creerRayon(nomRayon);
        T_Rayon *tmp = magasin->liste_rayons;
        magasin->liste_rayons = nouveauRayon;
        nouveauRayon->suivant = tmp;
        printf("Insertion du rayon en tete de liste.\n");
        return 1;
    }

    // S�lection des deux premiers rayons -> Cela va nous permettre de parcourir la liste cha�n�e
    T_Rayon *rayonSelec = magasin->liste_rayons;
    T_Rayon *rayonSelecSuivant = magasin->liste_rayons->suivant;

    // Voir comment g�rer le dernier rayon
    // Permet de trouver la place du nouveau rayon dans l'ordre alphab�tique -> strcmp
    while ((rayonSelecSuivant != NULL)) {
        if((strcmp(nomRayon, rayonSelecSuivant->nom_rayon) > 0)) break;
        rayonSelec = rayonSelecSuivant;
        rayonSelecSuivant = rayonSelecSuivant->suivant;
    }

    // si le rayon existe d�j� alors on retourne 0
    if (strcmp(nomRayon, rayonSelec->nom_rayon) == 0){
        printf("Impossible.\nLe rayon existe deja.\n");
        return 0;
    }

    // Cr�ation d'un rayon
    T_Rayon *nouveauRayon = creerRayon(nomRayon);
    // si le non du rayon est ajout� en queue de cha�ne
    if (rayonSelecSuivant == NULL) {
        nouveauRayon->suivant = NULL;
        rayonSelec->suivant = nouveauRayon;
    } else {
        nouveauRayon->suivant = rayonSelecSuivant;
        rayonSelec->suivant = nouveauRayon;
    }
    printf("Le rayon est ajoute avec succes !\n");
    return 1;
}


/* ********************************
 * Ajout d'un produit dans un rayon
 ******************************** */
int ajouterProduit(T_Rayon *rayon, char *designation, float prix, int quantite) {
    // Voir insertion avec de mauvaises val

    // Retourne 0 si les informations sont impossibles
    if((strlen(designation)==0) || (prix <= 0) || (quantite <= 0)){
        printf("Attention les informations renseignees sont incorrectes.\nVeuillez recommencer.\n");
        return 0;
    }

    if(rayon->liste_produits != NULL) {
        if (strcmp(rayon->liste_produits->designation, designation) == 0) {
            printf("Impossible le produit existe deja");
            return -1;
        }
    }
    // V�rifier que le rayon existe !!
    if(rayon == NULL){
        printf("Attention le rayon n'existe pas.");
        return 0;
    }


    // Insertion du produit en t�te de liste
    if((rayon->liste_produits == NULL) || (prix < rayon->liste_produits->prix)){
        printf("Insertion du produit en tete de liste.\n");
        T_Produit *tmp = rayon->liste_produits;
        T_Produit *nouveauProduit = creerProduit(designation, prix, quantite);
        rayon->liste_produits = nouveauProduit;
        nouveauProduit->suivant = tmp;
        return 1;
    }

    T_Produit *produitSelec = rayon->liste_produits;
    // Emplacement du produit par prix
    while((produitSelec->suivant != NULL) && (prix >= produitSelec->suivant->prix)){
        // V�rification que le produit n'existe pas dans ce rayon
        if(strcmp(designation, produitSelec->suivant->designation)== 0){
            printf("Impossible le produit existe deja");
            return -1;
        }
        produitSelec = produitSelec->suivant;
    }

    // Apr�s avoir trouv� l'emplacement cr�ation du produit
    T_Produit *nouveauProduit = creerProduit(designation, prix, quantite);

    // Attention bien relier dans le bon ordre � VERIFIER
    nouveauProduit->suivant = produitSelec->suivant;
    produitSelec->suivant = nouveauProduit;
    printf("Le produit est ajoute avec succes !\n");

    return 1;
}



/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasin(T_Magasin *magasin) {
    int nb_produit = 0;
    // On test s'il y a des rayons ajoutés ou si le magasin est vide
    if (magasin->liste_rayons == NULL){
        printf("Rien dans le magasin");
        return;
    }
    printf("Le magasin %s vous propose : \n", magasin->nom);
    T_Rayon * iter = magasin->liste_rayons;
    T_Produit *iter2 =NULL;
    while(iter != NULL) {
        iter2 = iter->liste_produits;
        while(iter2 != NULL){
            nb_produit ++;
            iter2 = iter2->suivant;
        }
        printf("Nom du rayon : %s || Nombre de produit : %d\n",iter->nom_rayon, nb_produit);
        iter = iter->suivant;
        nb_produit = 0;
    }
}



// Fonction purement estethiques permettant de cr�er un tableau
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

    if(rayon == NULL){
        printf("Ce rayon n'existe pas.");
        return;
    }

    if(rayon->liste_produits){
        // Affichage de la ligne d'en-t�te
        int longmax = 15;
        printf("Designation");
        espaces(longmax-11);
        printf("Prix");
        espaces(15-4);
        printf("Quantite en stock");
        espaces(1);
        printf("\n");
        sep(longmax + 37);

        T_Produit *produiSelec = rayon->liste_produits;
        /*char prix = (char) produiSelec->prix;
        char quantite = (char) produiSelec->quantite_en_stock;*/
        while (produiSelec != NULL){

        char prix[MAX], quantite[MAX];
        sprintf(prix,"%.2f", produiSelec->prix);
        sprintf(quantite,"%d", produiSelec->quantite_en_stock);

            // ATTENTION Voir les erreurs de BUFFER

            printf("%s", produiSelec->designation);
            espaces(longmax - strlen(produiSelec->designation));

            // Affichage et conversion des int en cha�nes de caract�res

            printf("%s euros", prix);
            espaces(15 - (strlen(prix)+6) );

            printf("%s", quantite);
            espaces(17 - strlen(quantite));

            printf("\n");
            produiSelec = produiSelec->suivant;
        }
        sep(longmax+37);
    } else{
        printf("Attention, le rayon : %s, ne contient aucuns produits\n", rayon->nom_rayon);
    }
}



/* **************************************
 * Suppression d'un produit dans un rayon
 ************************************** */
int supprimerProduit(T_Rayon* rayon, char* designation_produit) {
    // Existence du rayon
    if(rayon == NULL){
        printf("Impossible le rayon n'existe pas.");
        return 0;
    }
    T_Produit* temp = rayon->liste_produits; //M�moire tampon pour le rechainage
    T_Produit* premier_produit = rayon->liste_produits; //Pointeur de tête pour l'itération

    //Si le rayon ne contient aucun produit.
    if (rayon->liste_produits == NULL){
        printf("Le rayon est vide");
        return 0;
    }


    //On vérifie si le produit n'est pas en tête du rayon

    if (strcmp(rayon->liste_produits->designation, designation_produit)==0){
        rayon->liste_produits = rayon->liste_produits->suivant;
        free(temp->designation);
        free(temp);
        return 1;
    }

    //Tant que le rayon n'est pas finit, on cherche si le produit existe
    while (premier_produit->suivant != NULL){
        if (strcmp(premier_produit->suivant->designation,designation_produit) == 0){
            temp = premier_produit->suivant;
            premier_produit->suivant = premier_produit->suivant->suivant;
            free(temp);
            return 1;
        }
        premier_produit = premier_produit->suivant;
    }
    return 0;
}



/* *************************************************************
 * Suppression d'un rayon et de tous les produits qu'il contient
 ************************************************************* */
int supprimerRayon(T_Magasin *magasin, char *nom_rayon){
    if (magasin->liste_rayons == NULL){
        printf("\nAttention, le magasin est vide.\n");
        return 0;
    }

    // Si le rayon est en t�te de liste
    if (strcmp(magasin->liste_rayons->nom_rayon, nom_rayon) == 0){
        T_Produit *produitSelec = magasin->liste_rayons->liste_produits, *tmp;
        while(produitSelec != NULL){
            tmp = produitSelec;
            produitSelec = produitSelec->suivant;
            free(tmp);
        }
        //suppression du rayon
        T_Rayon *temp = magasin->liste_rayons;
        magasin->liste_rayons = temp->suivant;
        free(temp->nom_rayon);
        free(temp);
        printf("\nLe rayon est supprime de la tete de liste\n");
        return 1;
    }
    // Si le rayon n'est pas en t�te de liste
    else{
        T_Rayon *rayonSelec = magasin->liste_rayons;
        T_Rayon *rayonSelecSuivant = rayonSelec->suivant;
        while ( rayonSelecSuivant != NULL && strcmp(rayonSelecSuivant->nom_rayon, nom_rayon) !=0 ){
            rayonSelec = rayonSelecSuivant;
            rayonSelecSuivant = rayonSelecSuivant->suivant;
        }
        if (rayonSelecSuivant == NULL){
            printf("\nCe rayon n'existe pas, impossible de le supprimer\n");
            return 0;
        }
        // Si trouve en milieu de liste alors on reforme le chainage
        if (strcmp(rayonSelecSuivant->nom_rayon, nom_rayon) ==0){

            T_Produit *produitSelec = rayonSelec->suivant->liste_produits, *tmp;
            while (produitSelec != NULL){
                tmp = produitSelec;
                produitSelec = produitSelec->suivant;
                free(tmp);
            }
            T_Rayon *tmp2 = rayonSelecSuivant->suivant;
            free(rayonSelec->suivant);
            rayonSelec->suivant = tmp2;
            printf("\nLe rayon a bien ete supprime.\n", nom_rayon, magasin->nom);
            return 1;
        }
    }
}



/*void ajouterProduitClasse(head_classe *tete_liste, char* designation, float prix, int quantite, T_Rayon* rayon) {
    // On crée une nouvelle cellule struct Classe
    printf("DEBUT");
    struct Classe* new_list = malloc(sizeof(struct Classe));
    new_list->designation = designation;
    new_list->prix = prix;
    new_list->rayon = rayon;
    new_list->quantite = quantite;
    printf("MID");
    new_list->suivant = NULL;
    head_classe *iter = tete_liste;
    struct Classe* prec = NULL;
    printf("FIN");

    // Si la liste Classe est nulle, la cellule nouvelle doit être au début
    if (*tete_liste == NULL) {
        printf("NULLLL");
        //printf("%s", tete_liste->designation);
        *tete_liste = new_list;
        //(*tete_liste)->suivant = NULL;
        printf("TEST");
        return;
    } else {
        struct Classe* iter = *tete_liste;
        struct Classe* prec = NULL;

        printf("TEST ELSE");
        while((*iter)->suivant != NULL){
            if((*iter)->suivant->prix < new_list->prix){
                prec = *iter;
                *iter = (*iter)->suivant;
            }
        }
        prec->suivant = new_list;
        new_list->suivant = (*iter)->suivant->suivant;
    }
}*/

void ajouterProduitClasse(head_classe *tete_liste, char* designation, float prix, int quantite, T_Rayon* rayon) {
    // On cr�e une nouvelle cellule struct Classe
    struct Classe* new_list = malloc(sizeof(struct Classe));
    new_list->designation = designation;
    new_list->prix = prix;
    new_list->rayon = rayon;
    new_list->quantite = quantite;
    new_list->suivant = NULL;

    // Si la liste Classe est nulle, la cellule nouvelle doit �tre au d�but
    if (*tete_liste == NULL) {
        *tete_liste = new_list;
        (*tete_liste)->suivant = NULL;
        return;
    }
    else {
        struct Classe* iter = *tete_liste;
        struct Classe* prec = NULL;
        printf("TEST3");


        while((iter)->suivant != NULL){
            if((iter)->suivant->prix < new_list->prix){
                prec = iter;
                iter = iter->suivant;
            } else {
                break;  // Sortir de la boucle si on a trouv� l'emplacement pour la nouvelle cellule
            }
        }



        if(prec == NULL){
            // Si la nouvelle cellule doit �tre au d�but de la liste
            new_list->suivant = *tete_liste;
            *tete_liste = new_list;
        }else{
            // Ins�rer la nouvelle cellule entre prec et iter
            prec->suivant = new_list;
            new_list->suivant = iter;
        }
    }
}






/* **************************************************************************************
 * Recherche des produits se situant dans une fourchette de prix entr�e par l'utilisateur
 ************************************************************************************** */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max) {

    // Création de la Liste de type Classe, et de head, pointeur de tête vers la liste
    struct Classe* List;
    head_classe head = NULL;

    T_Rayon* actuel_rayon = magasin->liste_rayons;
    // Si le magasin est vide, il n'y a rien �  chercher
    if(magasin->liste_rayons == NULL) {
        return;
    }
    // On traverse les rayons de notre magasin, jusqu'a trouver un produit P tel que : min prix < prix P < max prix.
    while(actuel_rayon != NULL){
        T_Produit* produit_actuel = actuel_rayon->liste_produits;
        while(produit_actuel != NULL){
            if(produit_actuel->prix > prix_min && produit_actuel->prix < prix_max){
                printf("%s", produit_actuel->designation);
                // On ajoute le dit produit et on le transforme en cellule Classe.
                ajouterProduitClasse(&head, produit_actuel->designation, produit_actuel->prix, produit_actuel->quantite_en_stock, actuel_rayon);

            }
            produit_actuel = produit_actuel->suivant;
        }
        actuel_rayon = actuel_rayon->suivant;
    }
    // Si aucune cellule Classe, on a trouvé aucun produit correspondant aux critères
    if (head == NULL){
        printf("Aucun produit dans cette intervalle n'a été trouvé. \n");
    }
    else {
        // Iter pointe vers la tête de la chaine Classe
        head_classe *iter = head;
        while(*iter != NULL){
            printf("Marque : %s || Prix : %f || Quantité en stock : %d || Rayon : %s \n", (*iter)->designation, (*iter)->prix, (*iter)->quantite, (*iter)->rayon->nom_rayon);
            *iter = (*iter)->suivant;
        }
    }
}



T_Rayon* rechercheRayons (T_Magasin *magasin, char * nomRayon){
    T_Rayon * premier_rayon = magasin->liste_rayons;
    while ((magasin->liste_rayons!= NULL) && (strcmp(nomRayon,magasin->liste_rayons->nom_rayon)!=0)){
        //Parcours de la liste des rayons jusqu'a tomber soit sur NULL soit sur le bon rayon ( stocke dans magasin->liste_rayons)
        magasin->liste_rayons = magasin ->liste_rayons->suivant;
    }
    if (magasin->liste_rayons == NULL){ //cas pas trouve
        magasin->liste_rayons = premier_rayon;
        return NULL;
    }
    else {
        T_Rayon * rayon_trouve = magasin->liste_rayons;
        magasin->liste_rayons = premier_rayon;
        return rayon_trouve;
    }
}


/* *********************
 * Fusionner deux rayons
 ********************* */
void fusionnerRayons(T_Magasin *magasin) {
    T_Rayon *rayon1 = NULL;
    T_Rayon *rayon2 = NULL;
    char nomRayon1[MAX];
    char nomRayon2[MAX];

    // Saisie des noms des rayons
    printf("Quel est le nom du premier rayon ?");
    scanf("%s", nomRayon1);
    viderBuffer();
    printf("Quel est le nom du second rayon rayon ?");
    scanf("%s", nomRayon2);
    viderBuffer();

    // V�rification que les noms des rayons sont valides
    if((strlen(nomRayon1)==0) || (strlen(nomRayon2)==0) || (nomRayon1 == nomRayon2)) {
        printf("Attention les noms sont invalides veuillez recommencer\n");
        return;
    }

    // Recherche des rayons
    rayon1 = rechercheRayons(magasin, nomRayon1);
    rayon2 = rechercheRayons(magasin, nomRayon2);


    // V�rification que les rayons ont �t�s selectionn�
    if((rayon1 == NULL) || (rayon2 == NULL)){
        printf("Attention un des rayons n'existe pas.\n");
        return;
    }

    char nomNouvRayon[MAX];
    printf("Quel est le nom du nouveau rayon ?");
    scanf("%s", nomNouvRayon);
    viderBuffer();
    if(strlen(nomNouvRayon)==0){
        printf("Ce nom est invalide.");
        return;
    }

    // Voir comment ajouter le rayon dans la liste avec la fonction ajoutRayon

    char designation[MAX];

    ajouterRayon(magasin, nomNouvRayon);

    T_Rayon *nouvRayon = rechercheRayons(magasin, nomNouvRayon);




    // Ajout des produits dans le nouveau rayon en utilisant la fonction ajouterProduit qui ajoute par prix croissant
    // err apr�s

    T_Produit *produitSelec = rayon1->liste_produits;
    int res;
    while (produitSelec != NULL){
        //strcpy(designation, produitSelec->designation);
        ajouterProduit(nouvRayon, produitSelec->designation, produitSelec->prix, produitSelec->quantite_en_stock);
        if(produitSelec->suivant == NULL){
            break;
        }
        produitSelec = produitSelec->suivant;
    }
    produitSelec = rayon2->liste_produits;
    while (produitSelec != NULL){
        //strcpy(designation, produitSelec->designation);
        res = ajouterProduit(nouvRayon, produitSelec->designation, produitSelec->prix, produitSelec->quantite_en_stock);
        // Renommage si le produit existe d�j� dans le premier rayon
        if(res == -1){
            ajouterProduit(nouvRayon, strcat(produitSelec->designation, nomRayon2), produitSelec->prix, produitSelec->quantite_en_stock);
        }
        if(produitSelec->suivant == NULL){
            break;
        }
            produitSelec = produitSelec->suivant;
    }
    printf("Les rayons sont fusionnes");
    supprimerRayon(magasin, rayon1->nom_rayon);
    supprimerRayon(magasin, rayon2->nom_rayon);
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


