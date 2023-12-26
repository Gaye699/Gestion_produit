#include <stdio.h>
#include <string.h>

struct Produit {
    int code;
    char designation[50];
    float prixAchat;
    float prixVente;
    int quantiteStock;
    char derniereDateApprovisionnement[20];
};

// Fonction pour enregistrer un nouveau produit dans le fichier
void enregistrerProduit(struct Produit *produit) {
    FILE *fichier;
    fichier = fopen("produit.txt", "a");

    if (fichier != NULL) {
        fprintf(fichier, "%d %s %.2f %.2f %d %s\n", produit->code, produit->designation, produit->prixAchat, produit->prixVente, produit->quantiteStock, produit->derniereDateApprovisionnement);
        fclose(fichier);
        printf("Le produit a �t� enregistr� avec succ�s.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

// Fonction pour rechercher un produit dans le fichier
void rechercherProduit(int codeRecherche) {
    FILE *fichier;
    fichier = fopen("produit.txt", "r");

    if (fichier != NULL) {
        struct Produit produit;
        int trouve = 0;
        while (fscanf(fichier, "%d %[^ ] %f %f %d %s\n", &produit.code, produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, produit.derniereDateApprovisionnement) != EOF) {
            if (produit.code == codeRecherche) {
                printf("Produit trouv� :\n");

                printf("Code : %d\n", produit.code);
                if(produit.quantiteStock > 10){

                printf("D�signation : %s\n", produit.designation);
                printf("Prix d'achat : %.2f\n", produit.prixAchat);
                printf("Prix de vente : %.2f\n", produit.prixVente);
                printf("Quantit� en stock : %d\n", produit.quantiteStock);
                printf("Derni�re date d'approvisionnement : %s\n", produit.derniereDateApprovisionnement);
                trouve = 1;}else{
                printf("\033[1;31m");
                 printf("Code : %d, Designation : %s, Prix de vente : %.2f, Quantite en stock : %d\n", produit.code, produit.designation, produit.prixVente, produit.quantiteStock);
                 //printf("\033[0m"); // Remet la couleur par d�faut
                printf("Ce produit doit etre approvisionne !\n");}
                break;
            }
        }
        if (!trouve) {
            printf("Produit non trouv�.\n");
        }
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

// Fonction pour modifier un produit existant
void modifierProduit(int codeModif) {
    FILE *fichier;
    FILE *temp;
    fichier = fopen("produit.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fichier != NULL && temp != NULL) {
        struct Produit produit;
        int modifie = 0;
        while (fscanf(fichier, "%d %[^ ] %f %f %d %s\n", &produit.code, produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, produit.derniereDateApprovisionnement) != EOF) {
            if (produit.code == codeModif) {
                printf("Entrez la nouvelle d�signation du produit : ");
                scanf(" %[^\n]s", produit.designation);
                printf("Entrez le nouveau prix d'achat du produit : ");
                scanf("%f", &produit.prixAchat);
                printf("Entrez le nouveau prix de vente du produit : ");
                scanf("%f", &produit.prixVente);
                printf("Entrez la nouvelle quantit� en stock du produit : ");
                scanf("%d", &produit.quantiteStock);
                printf("Entrez la nouvelle derni�re date d'approvisionnement du produit : ");
                scanf(" %s", produit.derniereDateApprovisionnement);
                modifie = 1;
            }
            fprintf(temp, "%d %s %.2f %.2f %d %s\n", produit.code, produit.designation, produit.prixAchat, produit.prixVente, produit.quantiteStock, produit.derniereDateApprovisionnement);
        }
        if (!modifie) {
            printf("Produit non trouv�.\n");
        } else {
            printf("Le produit a �t� modifi� avec succ�s.\n");
        }
        fclose(fichier);
        fclose(temp);
        remove("produit.txt");
        rename("temp.txt", "produit.txt");
    } else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}

int main() {
    int choix;
    int codeModif;
    int nombreProduits = 0;
    int codeRecherche;
    struct Produit nouveauProduit;
    do {
    printf("Bienvenue dans le gestionnaire de produits.\n");
    printf("1. Ajouter un nouveau produit\n");
    printf("2. Rechercher un produit\n");
    printf("3. Modifier un produit\n");
    printf("4. Quitter\n");
    printf("Choisissez une option : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            // Ajouter un nouveau produit
          // Ajouter un nouveau produit
    printf("Entrez le code du produit : ");
    scanf("%d", &nouveauProduit.code);
    printf("Entrez la d�signation du produit : ");
    scanf(" %[^\n]s", nouveauProduit.designation);
    printf("Entrez le prix d'achat du produit : ");
    scanf("%f", &nouveauProduit.prixAchat);
    printf("Entrez le prix de vente du produit : ");
    scanf("%f", &nouveauProduit.prixVente);
    printf("Entrez la quantit� en stock du produit : ");
    scanf("%d", &nouveauProduit.quantiteStock);
    printf("Entrez la derni�re date d'approvisionnement du produit : ");
    scanf(" %s", nouveauProduit.derniereDateApprovisionnement);
    enregistrerProduit(&nouveauProduit);
    break;
        case 2:
            // Rechercher un produit

    printf("Entrez le code du produit � rechercher : ");
    scanf("%d", &codeRecherche);
    rechercherProduit(codeRecherche);
    break;

        case 3:
            // Modifier un produit

            printf("Entrez le code du produit � modifier : ");
            scanf("%d", &codeModif);
            modifierProduit(codeModif);
            break;
        case 4:
            printf("Au revoir !\n");
            break;
        default:
            printf("Choix invalide.\n");
    }
 } while (choix != 4);
    return 0;
}



