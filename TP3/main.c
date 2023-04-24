#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

int main()
{
    /*char nommg[] = "oi";
    char *ptnom = &nommg;
    T_Magasin *magasin1 = creerMagasin(ptnom);

    char nomr[] = "fruit";
    char *ptnomr = &nomr;
    ajouterRayon(magasin1, nomr);*/




    // ============= MENU UTILISATEUR ============= */
    char choix = '0';
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
        printf("\n9. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        viderBuffer(); // supprimer de l'entrée standard le retour charriot et les éventuels caractères supplémentaires tapés par l'utilisateur

        switch (choix) {
            case '1' :
                printf("Quelle est le nom du magasin ?");
                char *nom;
                scanf("%s", nom);
                T_Magasin *magasin1 = creerMagasin(nom);

                break;

            case '2' :
                printf("Nom : ");
                char * nom_new = malloc(50 * sizeof(char));
                scanf("%s", nom_new);
                ajouterRayon(magasin1, nom_new);

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
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
        }
        printf("\n\n\n");
    }

    return 0;
}