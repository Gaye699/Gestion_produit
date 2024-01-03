#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // Pour rand() et srand()
#include <time.h>
#include "const.h"
struct Client {
    char nom[50];
    char email[50];
    int tel;
    char profession[50];
    int pointsFidelite;
    struct Client *suivant;
};
struct Produit
{
    int code;
    char designation[50];
    float prixAchat;
    float prixVente;
    int quantiteStock;
    char derniereDateApprovisionnement[20];
};
struct Commande
{
    int numero;
    struct Client client;
    struct Produit produits[10];  // Supposons que MAX_PRODUITS est le nombre maximum de produits par commande
    int nbProduits;
    char statut[20];
};
struct Facture
{
    int numeroFacture;
    int numeroCommande; // Ajout du num�ro de commande dans la facture
    float montantTotal;
    float montantVerse;
    char statut[20]; // "EN COURS" ou "REGLE"
};
void saisirClient(struct Client *nouveauClient)
{
    printf("Entrez le nom du client : ");
    scanf(" %[^\n]s", nouveauClient->nom);
    printf("Entrez l'email du client : ");
    scanf(" %s", nouveauClient->email);
    printf("Entrez le tel du client: ");
    scanf(" %d", &nouveauClient->tel);
    printf("Entrez la profession du client: ");
    scanf(" %s", nouveauClient->profession);
}

void enregistrerClient(const struct Client *nouveauClient)
{
    // Code pour enregistrer le client dans un fichier ou une base de donn�es
    FILE *fichier;
    fichier = fopen("client.txt", "a");
    // Par exemple, vous pouvez ouvrir un fichier et y �crire les d�tails du client
    if (fichier != NULL)
    {
        fprintf(fichier, "%s %s %d %s %d\n", nouveauClient->nom, nouveauClient->email, nouveauClient->tel, nouveauClient->profession, nouveauClient->pointsFidelite);
        fclose(fichier);
        printf("Le client a ete enregistrer avec succes.");
    }
}
void ajouterPointsFidelite(struct Client *client, int nombrePoints)
{
    client->pointsFidelite += nombrePoints;
}

void afficherPointsFidelite(const struct Client *client)
{
    printf("Le client a %d points de fid�lit�.\n", client->pointsFidelite);
}
void afficherListeProduits() {
    FILE *fichierProduits;
    fichierProduits = fopen("produit.txt", "r"); // Ouvre le fichier en mode lecture

    if (fichierProduits != NULL) { // V�rifie si le fichier a �t� ouvert avec succ�s
        struct Produit produit;

        // Lecture et affichage de chaque produit dans le fichier
        while (fscanf(fichierProduits, "%d %s %f %f %d %s", &produit.code, produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, produit.derniereDateApprovisionnement) == 6) {
            printf("Code : %d\n", produit.code);
            printf("Designation : %s\n", produit.designation);
            printf("Prix d'achat : %.2f\n", produit.prixAchat);
            printf("Prix de vente : %.2f\n", produit.prixVente);
            printf("Quantite en stock : %d\n", produit.quantiteStock);
            printf("Derniere date d'approvisionnement : %s\n", produit.derniereDateApprovisionnement);
            printf("\n");
        }

        fclose(fichierProduits); // Ferme le fichier apr�s utilisation
    } else {
        printf("Erreur : Impossible d'ouvrir le fichier produit.txt\n");
    }
}

// Fonction pour enregistrer un nouveau produit dans le fichier
void enregistrerProduit(struct Produit *produit)
{
    FILE *fichier;
    fichier = fopen("produit.txt", "a");

    if (fichier != NULL)
    {
        fprintf(fichier, "%d %s %.2f %.2f %d %s\n", produit->code, produit->designation, produit->prixAchat, produit->prixVente, produit->quantiteStock, produit->derniereDateApprovisionnement);
        fclose(fichier);
        printf("Le produit a ete enregistre avec succes.\n");
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

// Fonction pour rechercher un produit dans le fichier
void rechercherProduit(int codeRecherche)
{
    FILE *fichier;
    fichier = fopen("produit.txt", "r");

    if (fichier != NULL)
    {
        struct Produit produit;
        int trouve = 0;
        while (fscanf(fichier, "%d %[^ ] %f %f %d %s\n", &produit.code, produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, produit.derniereDateApprovisionnement) != EOF)
        {
            if (produit.code == codeRecherche)
            {
                printf("Produit trouve :\n");

                printf("Code : %d\n", produit.code);
                if(produit.quantiteStock > 10)
                {

                    printf("Designation : %s\n", produit.designation);
                    printf("Prix d'achat : %.2f\n", produit.prixAchat);
                    printf("Prix de vente : %.2f\n", produit.prixVente);
                    printf("Quantite en stock : %d\n", produit.quantiteStock);
                    printf("Derniere date d'approvisionnement : %s\n", produit.derniereDateApprovisionnement);
                    trouve = 1;
                }
                else
                {
                    printf("\033[1;31m");
                    printf("Code : %d, Designation : %s, Prix de vente : %.2f, Quantite en stock : %d\n", produit.code, produit.designation, produit.prixVente, produit.quantiteStock);
                    printf("\033[0m"); // Remet la couleur par d�faut
                    printf("Ce produit doit etre approvisionne !\n");
                    //printf("\033[0m");
                }
                break;
            }
        }
        if (!trouve)
        {
            printf("Produit non trouve.\n");
        }
        fclose(fichier);
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

// Fonction pour modifier un produit existant
void modifierProduit(int codeModif)
{
    FILE *fichier;
    FILE *temp;
    fichier = fopen("produit.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fichier != NULL && temp != NULL)
    {
        struct Produit produit;
        int modifie = 0;
        while (fscanf(fichier, "%d %[^ ] %f %f %d %s\n", &produit.code, produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, produit.derniereDateApprovisionnement) != EOF)
        {
            if (produit.code == codeModif)
            {
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
        if (!modifie)
        {
            printf("Produit non trouve.\n");
        }
        else
        {
            printf("Le produit a ete modifie avec succes.\n");
        }
        fclose(fichier);
        fclose(temp);
        remove("produit.txt");
        rename("temp.txt", "produit.txt");
    }
    else
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}
int validerClient(char *nomClient)
{
    FILE *fichier = fopen("client.txt", "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier client.txt\n");
        return 0; // �chec de validation en cas d'erreur de lecture du fichier
    }

    char ligne[200]; // Supposons que chaque ligne contient au maximum 200 caract�res
    while (fgets(ligne, sizeof(ligne), fichier))
    {
        char *nom = strtok(ligne, " ");
        if (strcmp(nom, nomClient) == 0)
        {
            fclose(fichier);
            return 1; // Client trouv� et valide
        }
    }

    fclose(fichier);
    return 0; // Client non trouv� ou invalide
}
int verifierDesignationExiste(const char *designationSaisie)
{
    FILE *fichier;
    char ligne[100];
    int existe = 0;

    fichier = fopen("produit.txt", "r");
    if (fichier != NULL)
    {
        while (fgets(ligne, sizeof(ligne), fichier))
        {
            struct Produit produit;
            sscanf(ligne, "%d %s %f %f %d %s", &produit.code, produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, produit.derniereDateApprovisionnement);
            if (strcmp(produit.designation, designationSaisie) == 0)
            {
                existe = 1;
                break;
            }
        }
        fclose(fichier);
    }
    return existe;
}
int genererNumeroFacture() {
    srand(time(0));  // Initialisation du g�n�rateur de nombres al�atoires avec une graine diff�rente � chaque ex�cution
    return rand() % 10000;  // Num�ro de facture al�atoire entre 0 et 9999
}
// Fonction pour passer une commande
void passerCommande() {
    struct Client nouveauClient;
    struct Commande nouvelleCommande;

    int dernierNumeroCommande = recupererDernierNumeroCommande();
    nouvelleCommande.numero = ++dernierNumeroCommande;  // Incr�ment du num�ro de commande

    printf("Saisir votre nom : ");
    scanf("%s", nouveauClient.nom);

    printf("Saisir votre numero de telephone: ");
    scanf("%d", &nouveauClient.tel);

    int clientExiste = validerClient(nouveauClient.nom);

    if (clientExiste) {
        printf("Client d�j� enregistr�. Saisir les d�tails de la commande...\n");

        char produit[30];
        printf("Entrer le nom du produit: ");
        scanf("%s", produit);

        if (verifierDesignationExiste(produit)) {
            nouvelleCommande.client = nouveauClient;
            printf("Entrez le nombre de produits command�s : ");
            scanf("%d", &nouvelleCommande.nbProduits);

            // Initialisation des produits
            int i;
            for (i = 0; i < nouvelleCommande.nbProduits; i++) {
                nouvelleCommande.produits[i].code = 0;  // Valeur par d�faut
                strcpy(nouvelleCommande.produits[i].designation, "");  // Cha�ne vide par d�faut
                nouvelleCommande.produits[i].quantiteStock = 0;  // Valeur par d�faut
            }

            // Saisie des d�tails de chaque produit
            float montantTotal = 0.0;
    for (i = 0; i < nouvelleCommande.nbProduits; i++) {
        printf("Entrez le code du produit %d : ", i + 1);
        scanf("%d", &nouvelleCommande.produits[i].code);
        printf("Entrez la d�signation du produit %d : ", i + 1);
        scanf("%s", nouvelleCommande.produits[i].designation);
        printf("Entrez la quantit� du produit %d : ", i + 1);
        scanf("%d", &nouvelleCommande.produits[i].quantiteStock);

        // Calcul du montant total
        montantTotal += nouvelleCommande.produits[i].prixVente * nouvelleCommande.produits[i].quantiteStock;
    }

    // Demander � l'utilisateur le montant qu'il souhaite verser
    float montantVerse;
    printf("Entrez le montant que vous souhaitez verser : ");
    scanf("%f", &montantVerse);

    // Cr�ation de la facture et d�finition du statut en fonction du montant vers�
    struct Facture nouvelleFacture;
    nouvelleFacture.numeroFacture = ++dernierNumeroCommande;
    nouvelleFacture.numeroCommande = nouvelleCommande.numero;
    nouvelleFacture.montantTotal = montantTotal;
    nouvelleFacture.montantVerse = montantVerse;

    if (montantVerse < montantTotal) {
        strcpy(nouvelleFacture.statut, "EN COURS"); // Si le montant est inf�rieur au total, statut en cours
    } else if (montantVerse == montantTotal || montantVerse > montantTotal) {
        strcpy(nouvelleFacture.statut, "REGLE"); // Si le montant est �gal au total, statut r�gl�
    }

    // Enregistrement de la commande et de la facture
    enregistrerCommande(&nouvelleCommande);
    creerFacture(&nouvelleFacture);
    sauvegarderDernierNumeroCommande(dernierNumeroCommande);
    recompenserClient(&nouveauClient, montantTotal);
            system("cls");
        }
    } else {
        system("cls");
        printf("Vous devez d'abord vous enregistrer !\n");
        saisirClient(&nouveauClient);
        enregistrerClient(&nouveauClient);
        system("cls");

    }
}
int recupererDernierNumeroCommande() {
    int dernierNumero = 0;
    FILE *fichier = fopen("dernier_numero_commande.txt", "r");
    if (fichier != NULL) {
        fscanf(fichier, "%d", &dernierNumero);
        fclose(fichier);
    }
    return dernierNumero;
}

// Fonction pour sauvegarder le dernier num�ro de commande dans un fichier
void sauvegarderDernierNumeroCommande(int dernierNumero) {
    FILE *fichier = fopen("dernier_numero_commande.txt", "w");
    if (fichier != NULL) {
        fprintf(fichier, "%d", dernierNumero);
        fclose(fichier);
    }
}

void enregistrerCommande(struct Commande *nouvelleCommande) {
    int dernierNumero = recupererDernierNumeroCommande();
    FILE *fichier;
    fichier = fopen("commandes.txt", "a");

    if (fichier != NULL) {
        fprintf(fichier, "Numero de commande : %d\nClient : %s\n", ++dernierNumero, nouvelleCommande->client.nom);
        fprintf(fichier, "Nombre de produits : %d\n", nouvelleCommande->nbProduits);
        int i;
        for (i = 0; i < nouvelleCommande->nbProduits; i++) {
            fprintf(fichier, "Produit %d : %s, Quantite : %d\n", i + 1, nouvelleCommande->produits[i].designation, nouvelleCommande->produits[i].quantiteStock);
        }

        fprintf(fichier, "\n");
        fclose(fichier);

        sauvegarderDernierNumeroCommande(dernierNumero); // Sauvegarde du nouveau num�ro
        printf("La commande a ete enregistree avec succes.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier de commandes.\n");
    }
}

void afficherProduitEnZoneRouge()
{
    FILE *fichier;
    fichier = fopen("produit.txt", "r");

    if(fichier !=NULL)
    {
        struct Produit produit;
        printf("produit en zone rouge (quantite <10) :\n");
        while(fscanf(fichier, "%d %[^ ] %f %f %d %s\n", &produit.code, &produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, &produit.derniereDateApprovisionnement) !=EOF)
        {
            ;
            if(produit.quantiteStock < 10)
            {
                printf("\033[1;31m");
                printf("code: %d, designation: %s, prix de vente: %.2f, quantite en stocke: %d\n", produit.code, produit.designation, produit.prixVente, produit.quantiteStock);
                printf("\033[0m");//remet la couleur par defaut
            }
        }
        fclose(fichier);

    }
}
// Fonction pour cr�er une facture � partir d'une commande
void creerFacture(const struct Commande *commande, float montantTotal) {
    int numeroFacture = genererNumeroFacture();

    struct Facture nouvelleFacture;
    nouvelleFacture.numeroFacture = numeroFacture;
    nouvelleFacture.numeroCommande = commande->numero; // Utilisation du num�ro de la commande
    nouvelleFacture.montantTotal = montantTotal;
    nouvelleFacture.montantVerse = 0.0;
    strcpy(nouvelleFacture.statut, "EN COURS");

    enregistrerFactureDansFichier(&nouvelleFacture);
}

void enregistrerFactureDansFichier(struct Facture *nouvelleFacture) {
    FILE *fichier;
    fichier = fopen("facture.txt", "a");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(fichier, "Num�ro de facture : %d\n", nouvelleFacture->numeroFacture);
    fprintf(fichier, "Num�ro de commande : %d\n", nouvelleFacture->numeroCommande);
    fprintf(fichier, "Montant total : %.2f\n", nouvelleFacture->montantTotal);
    fprintf(fichier, "Montant vers� : %.2f\n", nouvelleFacture->montantVerse);
    fprintf(fichier, "Statut : %s\n", nouvelleFacture->statut);
    fprintf(fichier, "\n");

    fclose(fichier);
}
void afficherStatutFacture() {
    FILE *fichier;
    fichier = fopen("facture.txt", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int numeroFacture;
    char statut[20];
    float montantTotal, montantVerse;
    char ligne[100];

    int isStartOfNewFacture = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "Num�ro de facture : %d", &numeroFacture) == 1) {
            isStartOfNewFacture = 1;
            printf("Numero de facture : %d\n", numeroFacture);
        } else if (isStartOfNewFacture && sscanf(ligne, "Statut : %s", statut) == 1) {
            printf("Statut de la facture : %s\n", statut);
        } else if (isStartOfNewFacture && sscanf(ligne, "Montant total : %f", &montantTotal) == 1) {
            printf("Montant total : %.2f\n", montantTotal);
        } else if (isStartOfNewFacture && sscanf(ligne, "Montant vers� : %f", &montantVerse) == 1) {
            printf("Montant vers� : %.2f\n", montantVerse);
            printf("\n");
            isStartOfNewFacture = 0;
        }
    }

    fclose(fichier);
}
void recompenserClient(struct Client *client, float montantFacture) {
    int points = 0;

    if (montantFacture > 50000 && montantFacture <= 100000) {
        points = 1;
    } else if (montantFacture > 100000) {
        points = 3;
    }

    client->pointsFidelite += points;
}
int main()
{
    int choix,choix2,codeModif,codeRecherche,nouveauClient,n,produit,uneFacture;
    int nombreProduits = 0;
    struct Produit nouveauProduit;
    do{
    printf("1- Proprietaire\n");
    printf("2- Client\n");
    printf("3- Quiter\n");
    printf("Choix: ");
    scanf("%d",&n);
    system("cls");
    if(n == 1)
    {
        do
        {
            MENU_PRINCIPALE;
            printf("Choisissez une option : ");
            scanf("%d", &choix);

            switch (choix)
            {
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
                //afficher status factures
                system("cls");
                afficherStatutFacture(&uneFacture);
                break;
            case 7:
                printf("Au revoir !\n");
                break;
            case 8:

                break;

            default:
                system("cls");
                printf("Choix invalide.\n");
            }
        }
        while (choix != 8);
        system("cls");
    }
    if(n == 2)
    {
        do{
        ACCUEIL;
        printf("Choix: ");
        scanf("%d",&choix2);
        system("cls");
        switch(choix2){
        case 1:
            passerCommande();
            break;
        case 2:
            afficherListeProduits();
            break;
            system("cls");
        case 3:
            printf("Au revoir !\n");
             MENU_PRINCIPALE;
             system("cls");
            break;
        default:
            system("cls");
            printf("Choix invalide");
        }
      }while(choix2 != 3);
      system("cls");
    }
}while(n != 3);
system("cls");
printf("Au revoir et a la prochaine");
    return 0;
}



