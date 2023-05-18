#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include "tp3.h"

int main()
{

}


/*
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
        viderBuffer(); // supprimer de l'entrée standard le retour charriot et les éventuels caractères supplémentaires tapés par l'utilisateur



        switch (choix) {
            case '1' :
            {
                char nomMagasin[MAX];
                printf("Quel est le nom du magasin ? ");
                fgets(nomMagasin, 100, stdin);
                nomMagasin[strcspn(nomMagasin, "\n")] = 0;
                magasin = creerMagasin(nomMagasin);
            }
                break;

            case '2' :
            {
                char nomRayon[MAX];
                printf("Quel est le nom du rayon ?");
                fgets(nomRayon, 100, stdin);
                nomRayon[strcspn(nomRayon, "\n")] = 0;

                ajouterRayon(magasin, nomRayon);

            }
                break;

            case '3' :
            {
                float prix;
                int quantite;
                char nomRayon[MAX];
                char designation[MAX];

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
                T_Rayon *selec = magasin->liste_rayons;
                while (selec != NULL){
                    if(strcmp(selec->nom_rayon, nomRayon)== 0) break;
                    selec = selec->suivant;
                }
                if (selec == NULL){
                    printf("ERREUR le rayon n'existe pas.");
                    break;
                }

                ajouterProduit(selec, designation, prix, quantite);
            }

                break;

            case '4' :
            {
                afficherMagasin(magasin);
            }
                break;

            case '5' :
            {
                char nomRayon[MAX];

                printf("Quel est le nom du rayon ?");
                fgets(nomRayon, 100, stdin);
                nomRayon[strcspn(nomRayon, "\n")] = 0;

                // Recherche du rayon
                T_Rayon *selec = magasin->liste_rayons;
                while (strcmp(selec->nom_rayon, nomRayon)!=0){
                    selec = selec->suivant;
                    if(selec == NULL){
                        break;
                    }
                }
                afficherRayon(selec);

            }
                break;

            case '6' :
            {
                char nomRayon[MAX];
                char designation[MAX];


                printf("Quel est le nom du rayon ?");
                fgets(nomRayon, 100, stdin);
                nomRayon[strcspn(nomRayon, "\n")] = 0;

                printf("Quel est le nom du produit ?");
                scanf("%s", designation);
                viderBuffer();

                T_Rayon *selec = magasin->liste_rayons;
                while (strcmp(selec->nom_rayon, nomRayon)!=0){
                    selec = selec->suivant;
                    if (selec == NULL) break;
                }
                printf("%s", selec->nom_rayon);
                printf("%s", designation);
                supprimerProduit(selec, designation);

            }
                break;

            case '7' :
            {
                char nomRayon[MAX];

                printf("Quel est le nom du rayon ?");
                scanf("%s", nomRayon);
                viderBuffer();
                supprimerRayon(magasin, nomRayon);
            }
               break;

            case '8' :
            {
                float min = 0, max = 0;

                printf("Quel est le minimum ?");
                scanf("%f", &min);
                viderBuffer();

                printf("Quel est le maximum ?");
                scanf("%f", &max);
                viderBuffer();

                rechercheProduits(magasin, min, max);

            }
               break;

            case '9' :
            {
                fusionnerRayons(magasin);
            }
                break;

            case 'q' : {
                T_Rayon *selec = magasin->liste_rayons;
                char *tmp;

                while (selec != NULL) {
                    tmp = selec->nom_rayon;
                    selec = selec->suivant;
                    supprimerRayon(magasin, tmp);
                }
                free(magasin);
                printf("Magasin supprime !");
                test = 0;
                printf("\n======== PROGRAMME TERMINE ========\n");

            }
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
        }
        printf("\n\n\n");
    }
    return 0;
}*/