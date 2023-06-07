#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"
#include "TP4.h"


// Commentaire

int main()
{
    menu();

    /*afficherTexte(index);
    afficherPos(ABR);
    afficher_arbre(ABR->racine, 0);
    afficherMagasin(liste);
    afficherIndex(*ABR);*/
    return 0;
}

void menu(){
    T_Index *ABR = creerIndex();
    T_listePhrases *index;

    // ============= MENU UTILISATEUR =============
    char choix = '0';
    while (choix != 'q') {

        printf("\n======================================");
        printf("\n1. Charger un fichier");
        printf("\n2. Caracteristiques de l'index");
        printf("\n3. Afficher l'index");
        printf("\n4. Rechercher un mot");
        printf("\n5. Afficher les occurences d'un mot");
        printf("\n6. Construire le texte a partir de l'index");
        printf("\nq. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        viderBuffer(); // supprimer de l'entrée standard le retour charriot et les éventuels caractères supplémentaires tapés par l'utilisateur

        switch (choix) {
            case '1' : {
                char *filename = "../TP4/test.txt";
                indexerFichier(ABR, filename);
                printf("\n\n\n");
                index = indexerListe(ABR);
                break;

            }

            case '2' : {
                break;

            }

            case '3' : {
                afficherIndex(*ABR);
                break;

            }

            case '4' : {

                if (ABR->racine == NULL){printf("Alerte index vide!"); break;}
                char word[100];
                printf("Quel mot souhaitez vous rechercher ? \n");
                scanf("%s", word);
                viderBuffer();
                rechercherMot(ABR,word);
                break;
            }

            case '5' : {

                if (ABR->racine == NULL){printf("Alerte index vide!"); break;}
                char word[100];
                printf("Quel mot souhaitez vous rechercher ? \n");
                scanf("%s", word);
                viderBuffer();
                //afficherOccurencesMot(ABR, "superieure");

                afficherOccurencesMot(ABR, word);
                break;

            }

            case '6' : {

                char* nouveau_texte = "../TP4/test2.txt";
                if (ABR->racine == NULL){
                    printf("Erreur! Index vide, impossible de créer un texte \n");
                }
                else {
                    construireTexte(ABR, nouveau_texte);
                }
                break;
            }

            case 'q' : {
                if (ABR){
                    viderIndex(ABR);
                }
                if (index){
                    viderListePhrases(index);
                }
                printf("Arbre supprime !");
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            }

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
        }
        printf("\n\n\n");
    }
    return;
}
