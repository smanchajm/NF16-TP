#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED
#define MAX 70 //Maximum de caractères pour un nom

// Structures et types
struct Produit {
    char *designation;
    float prix;
    int quantite_en_stock;
    struct Produit *suivant;
};
typedef struct Produit T_Produit;

struct Rayon {
    char * nom_rayon;
    T_Produit *liste_produits;
    struct Rayon *suivant;
};
typedef struct Rayon T_Rayon;

struct Magasin {
    char *nom;
    T_Rayon *liste_rayons;
};
typedef struct Magasin T_Magasin;


// Cr�ation et initialisation des structures
T_Produit *creerProduit(char *designation, float prix, int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);

// fonction de permettant de comparer deux mots aphab�tiquement
int ordreAlpha(char *nom1, char *nom2);

// Ajout d'un rayon dans un magasin
int ajouterRayon(T_Magasin *magasin, char *nomRayon);

// Ajout d'un produit dans un rayon
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite);

// Affichage de tous les rayons d'un magasin
void afficherMagasin(T_Magasin *magasin);

// Affichage de tous les produits d'un rayon
void afficherRayon(T_Rayon *rayon);

// Suppression d'un produit dans un rayon
int supprimerProduit(T_Rayon *rayon, char* designation_produit);

// Suppression d'un rayon et de tous les produits qu'il contient
int supprimerRayon(T_Magasin *magasin, char *nom_rayon);

// Recherche des produits se situant dans une fourchette de prix entr�e par l'utilisateur
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);

// Fusionner deux rayons
void fusionnerRayons(T_Magasin *magasin);


// UTILS
void viderBuffer() ;
T_Rayon * rechercherRayon(char *nomRayon, T_Magasin *magasin);


struct Classe{
    char* designation;
    float prix;
    int quantite;
    T_Rayon *rayon;
    struct Classe* suivant;
};

typedef struct Classe* head_classe;

void ajouterProduitClasse(head_classe *tete_liste, char* designation, float prix, int quantite, T_Rayon* rayon);




#endif // TP3_H_INCLUDED
