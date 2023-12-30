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
void afficherProduits() {
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier produit.txt");
    }
    struct Produit produit;
    while (fscanf(fichier, "%d %s %.2f %d %s", &produit.code, produit.designation,  &produit.prixVente, &produit.quantiteStock) != EOF) {
        printf("%d, nom: %s, prix: %.2f, Quantite: %d\n", produit.code, produit.designation, produit.prixVente, produit.quantiteStock);
    }

    fclose(fichier);
}

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
                printf("\033[0m"); // Remet la couleur par défaut
                printf("Ce produit doit etre approvisionne !\n");
                //printf("\033[0m");
                }
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
struct Commande {
    int numero;
    struct Client client;
    struct Produit produits[10];  // Supposons que MAX_PRODUITS est le nombre maximum de produits par commande
    int nbProduits;
};
int validerClient(char *nomClient) {
    FILE *fichier = fopen("client.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier client.txt\n");
        return 0; // Échec de validation en cas d'erreur de lecture du fichier
    }

    char ligne[200]; // Supposons que chaque ligne contient au maximum 200 caractères
    while (fgets(ligne, sizeof(ligne), fichier)) {
        char *nom = strtok(ligne, " ");
        if (strcmp(nom, nomClient) == 0) {
            fclose(fichier);
            return 1; // Client trouvé et valide
        }
    }

    fclose(fichier);
    return 0; // Client non trouvé ou invalide
}
int verifierDesignationExiste(const char *designationSaisie) {
    FILE *fichier;
    char ligne[100];
    int existe = 0;

    fichier = fopen("produit.txt", "r");
    if (fichier != NULL) {
        while (fgets(ligne, sizeof(ligne), fichier)) {
            struct Produit produit;
            sscanf(ligne, "%d %s %f %f %d %s", &produit.code, produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, produit.derniereDateApprovisionnement);
            if (strcmp(produit.designation, designationSaisie) == 0) {
                existe = 1;
                break;
            }
        }
        fclose(fichier);
    }
    return existe;
}
void passerCommande() {
    struct Client nouveauClient;
    struct Commande nouvelleCommande;
    static int dernierNumeroCommande = 0;

    printf("Saisir votre nom : ");
    scanf("%s", nouveauClient.nom);
    //printf("Saisir votre l'email : ");
    //scanf("%s", nouveauClient.email);
    printf("Saisir votre numero de telephone: ");
    scanf("%d", &nouveauClient.tel);
    //printf("Saisir votre profession: ");
    //scanf("%s", nouveauClient.profession);

    int clientExiste = validerClient(nouveauClient.nom);
    //int clientExiste = enregistrerClient(nouvelleCommande->client);

    if (clientExiste) {
        // Le client est déjà enregistré, procéder à la saisie de la commande
        printf("Client deja enregistre. Saisir les details de la commande...\n");
        // ... (Code pour saisir et enregistrer la commande)
        int nbQ;
        char produit[30];
        printf("Entrer le nom du produit: ");
        scanf("%s",produit);
        if (verifierDesignationExiste(produit)){
             nouvelleCommande.numero = ++dernierNumeroCommande;
    nouvelleCommande.client = nouveauClient;  // Utilisation du client associé à la commande
    // Saisie de la quantité de produits commandée
    printf("Entrez le nombre de produits commandés : ");
    scanf("%d", &nouvelleCommande.nbProduits);
    // Remplissage des détails de chaque produit commandé
    int i;
    for (i = 0; i < nouvelleCommande.nbProduits; i++) {
        printf("Entrez le code du produit %d : ", i+1);
        scanf("%d", &nouvelleCommande.produits[i].code);
        printf("Entrez la quantité du produit %d : \n", i+1);
        scanf("%d", &nouvelleCommande.produits[i].quantiteStock);
        // Vous pouvez également saisir d'autres détails tels que le prix d'achat, le prix de vente, la dernière date d'approvisionnement, etc.
    }
    enregistrerCommande(&nouvelleCommande); // Appel de la fonction pour enregistrer la commande
    }
    }else{
        // Enregistrer le nouveau client
        saisirClient(&nouveauClient);
        enregistrerClient(&nouveauClient);
        // Procéder à la saisie de la commande
        printf("Saisir les détails de la commande...\n");
        // ... (Code pour saisir et enregistrer la commande)
    }

}

void enregistrerCommande(const struct Commande *nouvelleCommande) {
    FILE *fichier;
    fichier = fopen("commandes.txt", "a");
    if (fichier != NULL) {
            int dernierNumeroCommande = 0;
        fprintf(fichier, "-Numero de commande : %d\nClient : %s\n", ++dernierNumeroCommande, nouvelleCommande->client.nom);
        fprintf(fichier, "Nombre de produits : %d\n", nouvelleCommande->nbProduits);
        int i;
        for (i = 0; i < nouvelleCommande->nbProduits; i++) {
            fprintf(fichier, "Produit %d : %s, Quantite : %d\n", i+1, nouvelleCommande->produits[i].designation, nouvelleCommande->produits[i].quantiteStock);
        }
        fclose(fichier);
        printf("La commande a ete enregistree avec succes.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier de commandes.\n");
    }
}
void afficherProduitEnZoneRouge(){
    FILE *fichier;
    fichier = fopen("produit.txt", "r");

    if(fichier !=NULL){
        struct Produit produit;
        printf("produit en zone rouge (quantite <10) :\n");
        while(fscanf(fichier, "%d %[^ ] %f %f %d %s\n", &produit.code, &produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, &produit.derniereDateApprovisionnement) !=EOF){;
        if(produit.quantiteStock < 10){
            printf("\033[1;31m");
            printf("code: %d, designation: %s, prix de vente: %.2f, quantite en stocke: %d\n", produit.code, produit.designation, produit.prixVente, produit.quantiteStock);
            printf("\033[0m");//remet la couleur par defaut
        }
    }
       fclose(fichier);

    }
}



int main() {
    int choix,codeModif,codeRecherche,nouveauClient,n,produit;
    int nombreProduits = 0;
    struct Produit nouveauProduit;
    printf("1- Proprietaire\n");
    printf("2- Client\n");
    printf("Choix: ");
    scanf("%d",&n);
    system("cls");
    if(n == 1){
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
    system("cls");
    break;
        case 2:
            // Rechercher un produit

    printf("Entrez le code du produit a rechercher : ");
    scanf("%d", &codeRecherche);
    system("cls");
    rechercherProduit(codeRecherche);
    break;

        case 3:
            // Modifier un produit

            printf("Entrez le code du produit a modifier : ");
            scanf("%d", &codeModif);
            modifierProduit(codeModif);
            system("cls");
            break;
        case 4:
             //ajouter un client
            printf("Ajouter un client\n");
            saisirClient(&nouveauClient);
            enregistrerClient(&nouveauClient);
            break;
        case 5:
            //afficher les produits en zone rouge
            system("cls");
            afficherProduitEnZoneRouge();
            break;
        case 6:
             printf("Au revoir !\n");
             break;

        default:
            system("cls");
            printf("Choix invalide.\n");
    }
 } while (choix != 6);
    }
    if(n == 2){
        ACCUEIL;
        int choix2;
        printf("Choix: ");
        scanf("%d",&choix2);
        system("cls");
        if(choix2 == 2){
            afficherProduits();
        }
        if(choix2 == 1){
            passerCommande();
            //saisirCommande();
        }
    }
    return 0;
}



