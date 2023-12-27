#include <stdio.h>
#include <string.h>
#include "const.h"


struct Produit {
    int code;
    char designation[50];
    float prixAchat;
    float prixVente;
    int quantiteStock;
    char derniereDateApprovisionnement[20];
};
struct Client {
    char nom[50];
    char email[50];
    int tel[15];
    char profession[50];
    int pointsFidelite;
};
void saisirClient(struct Client *nouveauClient) {
    printf("Entrez le nom du client : ");
    scanf(" %[^\n]s", nouveauClient->nom);
    printf("Entrez l'email du client : ");
    scanf(" %s", nouveauClient->email);
    printf("Entrez le tel du client: ");
    scanf(" %d", nouveauClient->tel);
    printf("Entrez la profession du client: ");
    scanf(" %s", nouveauClient->profession);
}

void enregistrerClient(const struct Client *nouveauClient) {
    // Code pour enregistrer le client dans un fichier ou une base de données
    FILE *fichier;
    fichier = fopen("client.txt", "a");
    // Par exemple, vous pouvez ouvrir un fichier et y écrire les détails du client
    if (fichier != NULL) {
        fprintf(fichier, "%s %s %d %s %d\n", nouveauClient->nom, nouveauClient->email, nouveauClient->tel, nouveauClient->profession, nouveauClient->pointsFidelite);
        fclose(fichier);
        printf("Le client a ete enregistrer avec succes.");
    }
}
void ajouterPointsFidelite(struct Client *client, int nombrePoints) {
    client->pointsFidelite += nombrePoints;
}

void afficherPointsFidelite(const struct Client *client) {
    printf("Le client a %d points de fidélité.\n", client->pointsFidelite);
}
/*void afficherClient(const struct Client *client){
    int i,nbClient;
    FILE *fichier = fopen("client.txt", "r");
        if(fichier == NULL){
            printf("Aucun client enregistrer!");
        }


        printf("Liste des client enregistrer\n");
        printf("nom : %s\n", Client.nom);
        printf("email : %.2f\n", Client.email);

        }
            fclose(fichier);
        }*/

// Fonction pour enregistrer un nouveau produit dans le fichier
void enregistrerProduit(struct Produit *produit) {
    FILE *fichier;
    fichier = fopen("produit.txt", "a");

    if (fichier != NULL) {
        fprintf(fichier, "%d %s %.2f %.2f %d %s\n", produit->code, produit->designation, produit->prixAchat, produit->prixVente, produit->quantiteStock, produit->derniereDateApprovisionnement);
        fclose(fichier);
        printf("Le produit a ete enregistre avec succes.\n");
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
                printf("Produit trouve :\n");

                printf("Code : %d\n", produit.code);
                if(produit.quantiteStock > 10){

                printf("Designation : %s\n", produit.designation);
                printf("Prix d'achat : %.2f\n", produit.prixAchat);
                printf("Prix de vente : %.2f\n", produit.prixVente);
                printf("Quantite en stock : %d\n", produit.quantiteStock);
                printf("Derniere date d'approvisionnement : %s\n", produit.derniereDateApprovisionnement);
                trouve = 1;}else{
                printf("\033[1;31m");
                 printf("Code : %d, Designation : %s, Prix de vente : %.2f, Quantite en stock : %d\n", produit.code, produit.designation, produit.prixVente, produit.quantiteStock);
                 //printf("\033[0m"); // Remet la couleur par défaut
                printf("Ce produit doit etre approvisionne !\n");}
                break;
            }
        }
        if (!trouve) {
            printf("Produit non trouve.\n");
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
                printf("Entrez la nouvelle designation du produit : ");
                scanf(" %[^\n]s", produit.designation);
                printf("Entrez le nouveau prix d'achat du produit : ");
                scanf("%f", &produit.prixAchat);
                printf("Entrez le nouveau prix de vente du produit : ");
                scanf("%f", &produit.prixVente);
                printf("Entrez la nouvelle quantite en stock du produit : ");
                scanf("%d", &produit.quantiteStock);
                printf("Entrez la nouvelle derniere date d'approvisionnement du produit : ");
                scanf(" %s", produit.derniereDateApprovisionnement);
                modifie = 1;
            }
            fprintf(temp, "%d %s %.2f %.2f %d %s\n", produit.code, produit.designation, produit.prixAchat, produit.prixVente, produit.quantiteStock, produit.derniereDateApprovisionnement);
        }
        if (!modifie) {
            printf("Produit non trouve.\n");
        } else {
            printf("Le produit a ete modifie avec succes.\n");
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
    int codeRecherche,nouveauClient;
    struct Produit nouveauProduit;
    do {
    MENU_PRINCIPALE;
    printf("Choisissez une option : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            // Ajouter un nouveau produit
          // Ajouter un nouveau produit
    printf("Entrez le code du produit : ");
    scanf("%d", &nouveauProduit.code);
    printf("Entrez la designation du produit : ");
    scanf(" %[^\n]s", nouveauProduit.designation);
    printf("Entrez le prix d'achat du produit : ");
    scanf("%f", &nouveauProduit.prixAchat);
    printf("Entrez le prix de vente du produit : ");
    scanf("%f", &nouveauProduit.prixVente);
    printf("Entrez la quantite en stock du produit : ");
    scanf("%d", &nouveauProduit.quantiteStock);
    printf("Entrez la derniere date d'approvisionnement du produit : ");
    scanf(" %s", nouveauProduit.derniereDateApprovisionnement);
    enregistrerProduit(&nouveauProduit);
    break;
        case 2:
            // Rechercher un produit

    printf("Entrez le code du produit a rechercher : ");
    scanf("%d", &codeRecherche);
    rechercherProduit(codeRecherche);
    break;

        case 3:
            // Modifier un produit

            printf("Entrez le code du produit a modifier : ");
            scanf("%d", &codeModif);
            modifierProduit(codeModif);
            break;
        case 4:
             //ajouter un client
            printf("Ajouter un client\n");
            saisirClient(&nouveauClient);
            enregistrerClient(&nouveauClient);
            break;
        case 5:
            printf("Au revoir !\n");
            break;

        default:
            printf("Choix invalide.\n");
    }
 } while (choix != 5);
    return 0;
}



