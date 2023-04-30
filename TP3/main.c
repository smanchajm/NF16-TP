#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include "tp3.h"

int main()
{

// Voir pour les strcopy avec le nom des rayons

    char *nomMagasin = (char*) malloc((MAX*sizeof(char)));
    printf("Quel est le nom du magasin ?");
    scanf("%s", nomMagasin);
    T_Magasin *magasin = creerMagasin(nomMagasin);

    char *nomRayon = (char*) malloc(MAX*sizeof(char));
    printf("Quel est le nom du rayon ?");
    scanf("%s", nomRayon);
    ajouterRayon(magasin, nomRayon);

    float prix = 0;
    int quantite = 0;
    char *designation = (char*) malloc(MAX*sizeof(char));
    printf("Quel est le nom du produit ?");
    scanf("%s", designation);

    printf("Quel est le prix du produit ?");
    scanf("%f", &prix);

    printf("Quel est la quantite ?");
    scanf("%d", &quantite);

    T_Rayon *selec = magasin->liste_rayons;
    if(selec){
        ajouterProduit(selec, designation, prix, quantite);
    } else printf("Select NULL");

    afficherRayon(selec);

    char rep[] = "n";
    printf("FREE ?");
    scanf("%s",rep);
    if(rep == "o"){
        supprimerRayon(magasin, nomRayon);
        free(magasin);
    }
}


    // ============= MENU UTILISATEUR ============= */
/*    char choix = '0';
    while (choix != '9') {
        printf("\n======================================");
        printf("\n1. Creer un magasin");
        printf("\n2. Ajouter un rayon au magasin");
        printf("\n3. Ajouter un produit dans un rayon");
        printf("\n4. Afficher les rayons du magasin");
        printf("\n5. Afficher les produits d'un rayon");
        printf("\n6. Supprimer un produit");
        printf("\n7. Supprimer un rayon");
        printf("\n8. Rechercher un produit par prix");
        printf("\n9. Fusionner deux rayons");
        printf("\n10. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        viderBuffer(); // supprimer de l'entrée standard le retour charriot et les éventuels caractères supplémentaires tapés par l'utilisateur

        switch (choix) {
            case '1' :
            {
                char *nomMagasin = (char*) malloc((MAX*sizeof(char)));
                printf("Quel est le nom du magasin ? ");
                scanf("%s", nomMagasin);
                T_Magasin *magasin = creerMagasin(nomMagasin);
            }



                break;

            case '2' :
            {
                char *nomRayon = (char*) malloc(MAX*sizeof(char));
                printf("Quel est le nom du rayon ?");
                scanf("%s", nomRayon);
                ajouterRayon( )
            }


                break;

            case '3' :
                break;

            case '4' :
                break;

            case '5' :
                break;

            case '6' :
                break;

            case '7' :
               break;

            case '8' :
               break;

            case '9' :
                break;

            case '10' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
        }
        printf("\n\n\n");
    }

    return 0;
}*/