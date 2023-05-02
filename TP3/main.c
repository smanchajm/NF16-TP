#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include "tp3.h"

int main()
{

    // BOUVLE inf affichage rayons

// Voir pour les strcopy avec le nom des rayons
// Attention d�bugger supprimerrayon
/*
    char *nomMagasin = (char*) malloc((MAX*sizeof(char)));
    printf("Quel est le nom du magasin ?");
    scanf("%s", nomMagasin);
    T_Magasin *magasin = creerMagasin(nomMagasin);

    char *nomRayon = (char*) malloc(MAX*sizeof(char));
    printf("Quel est le nom du rayon ?");
    scanf("%s", nomRayon);
    ajouterRayon(magasin, nomRayon);

    char n[] = "o";

    T_Rayon *selec = magasin->liste_rayons;

    // ATTENTIONS DOUBLONS produits
    while (strcmp(n, "o")==0) {
        float prix = 0;
        int quantite = 0;
        char *designation = (char *) malloc(MAX * sizeof(char));
        printf("Quel est le nom du produit ?");
        scanf("%s", designation);

        printf("Quel est le prix du produit ?");
        scanf("%f", &prix);

        printf("Quel est la quantite ?");
        scanf("%d", &quantite);

        printf("TEST");
        ajouterProduit(selec, designation, prix, quantite);
        printf("\nVoulez vous continuer ? o/n");
        scanf("%s", &n);

    }
    printf("DONE");
    afficherRayon(magasin->liste_rayons);

    char rep[] = "n";
    printf("FREE ?");
    scanf("%s",rep);
    if(strcmp("o", rep)==0){
        int res;
        res = supprimerRayon(magasin, nomRayon);
        if(res == 1){
            printf("Le rayon est bien supprime !");
        }
        free(magasin);
        printf("FINISH");
    }
    // ATTEBTION rajouter des conditions d'existence sur afficher produit
    afficherRayon(magasin->liste_rayons);*/



    T_Magasin *magasin = NULL;

    // ============= MENU UTILISATEUR =============
    char choix = '0';
    int test = 0;
    while (choix != 'q') {

        printf("\n======================================");
        if (test == 0) {
            printf("\n1. Creer un magasin");
            printf("\nq. Quitter");
            test = 1;
        } else {
            printf("\n1. Creer un magasin");
            printf("\n2. Ajouter un rayon au magasin");
            printf("\n3. Ajouter un produit dans un rayon");
            printf("\n4. Afficher les rayons du magasin");
            printf("\n5. Afficher les produits d'un rayon");
            printf("\n6. Supprimer un produit");
            printf("\n7. Supprimer un rayon");
            printf("\n8. Rechercher un produit par prix");
            printf("\n9. Fusionner deux rayons");
            printf("\nq. Quitter");
        }
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        viderBuffer(); // supprimer de l'entr�e standard le retour charriot et les �ventuels caract�res suppl�mentaires tap�s par l'utilisateur



        switch (choix) {
            case '1' :
            {
                char *nomMagasin = (char*) malloc((MAX*sizeof(char)));
                printf("Quel est le nom du magasin ? ");
                scanf("%s", nomMagasin);
                viderBuffer();
                magasin = creerMagasin(nomMagasin);
            }
                break;

            case '2' :
            {
                char *nomRayon = (char*) malloc(MAX*sizeof(char));
                printf("Quel est le nom du rayon ?");
                scanf("%s", nomRayon);
                viderBuffer();
                ajouterRayon(magasin, nomRayon);
            }
                break;

            case '3' :
            {
                // VOIR RAYON NEXISTE PAS
                float prix = 0;
                int quantite = 0;
                char *designation = (char*) malloc(MAX*sizeof(char));
                char *nomRayon = (char*) malloc(MAX*sizeof(char));

                printf("Quel est le nom du rayon ?");
                scanf("%s", nomRayon);
                viderBuffer();

                printf("Quel est le nom du produit ?");
                scanf("%s", designation);
                viderBuffer();

                printf("Quel est le prix du produit ?");
                scanf("%f", &prix);
                viderBuffer();

                printf("Quel est la quantite ?");
                scanf("%d", &quantite);
                viderBuffer();

                // Recherche du rayon
                printf("%s\n",designation);
                T_Rayon *selec = magasin->liste_rayons;
                printf("%s\n",selec->nom_rayon);
                while (selec != NULL){
                    if(strcmp(selec->nom_rayon, nomRayon)== 0) break;
                    selec = selec->suivant;
                }
                printf("%s",selec->nom_rayon);
                if (selec == NULL){
                    printf("ERREUR");
                    break;
                }

                ajouterProduit(selec, designation, prix, quantite);
                free(designation);
                free(nomRayon);
            }

                break;

            case '4' :
            {
                afficherMagasin(magasin);
            }
                break;

            case '5' :
            {
                char *nomRayon = malloc(MAX * sizeof(char));

                printf("Quel est le nom du rayon ?");
                scanf("%s", nomRayon);

                // Recherche du rayon
                T_Rayon *selec = magasin->liste_rayons;
                while (strcmp(selec->nom_rayon, nomRayon)!=0){
                    selec = selec->suivant;
                }
                afficherRayon(selec);
                free(nomRayon);

            }
                break;

            case '6' :
            {
                char *nomRayon = (char*) malloc(MAX*sizeof(char));
                char *designation = (char*) malloc(MAX*sizeof(char));


                printf("Quel est le nom du rayon ?");
                scanf("%s", nomRayon);
                viderBuffer();

                printf("Quel est le nom du produit ?");
                scanf("%s", designation);
                viderBuffer();

                T_Rayon *selec = magasin->liste_rayons;
                while (strcmp(selec->nom_rayon, nomRayon)!=0){
                    selec = selec->suivant;
                }
                int res;
                res = supprimerProduit(selec, designation);
                printf("%d", &res);
            }
                break;

            case '7' :
            {
                char *nomRayon = (char*) malloc(MAX*sizeof(char));

                printf("Quel est le nom du rayon ?");
                scanf("%s", nomRayon);
                viderBuffer();

                int res;
                res = supprimerRayon(magasin, nomRayon);
                if(res == 1){
                    printf("Le rayon est bien supprime !");
                }
                free(nomRayon);
            }
               break;

            case '8' :
               break;

            case '9' :
                break;

            case 'q' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                free(magasin);
                test = 0;
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
        }
        printf("\n\n\n");
    }

    return 0;
}