#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "fonction.h"
#include "const.h"
#define MAX_LENGTH 100 // Définir la longueur maximale d'une ligne dans le fichier

void saisirClient(struct Client *nouveauClient)
{
    int pointsFidelite = 0;
    printf("Entrez le nom du client : ");
    scanf(" %[^\n]s", nouveauClient->nom);
    printf("Entrez l'email du client : ");
    scanf("%s", nouveauClient->email);
    printf("Entrez le tel du client: ");
    scanf(" %d", &nouveauClient->tel);
    printf("Entrez la profession du client: ");
    scanf(" %s", nouveauClient->profession);
    //scanf(" %d", nouveauClient->pointsFidelite);
}

void enregistrerClient(struct Client *nouveauClient) {
    FILE *fichier;
    fichier = fopen("client.txt", "a"); // Ouvre le fichier en mode ajout
    if (fichier != NULL) {
        int point = 0; // Initialisation des points de fidélité à 0 par défaut
        nouveauClient->pointsFidelite = point;
        fprintf(fichier, "%s %s %d %s %d\n", nouveauClient->nom, nouveauClient->email, nouveauClient->tel, nouveauClient->profession, nouveauClient->pointsFidelite);
        fclose(fichier);
        printf("Le client a été enregistré avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

void afficherListeClient(){
    FILE *fichier;
    fichier = fopen("client.txt", "r");
    if(fichier == NULL){
        printf("Erreur lors de l'ouverture du fichier ou fichier vide");
    }else{
        struct Client client;
        while(fscanf(fichier, "%s %s %d %s %d", client.nom, client.email, &client.tel, client.profession, &client.pointsFidelite) != EOF){
            printf("Nom: %s Email: %s Tel: %d Profession: %s point de fidelite: %d \n\n", client.nom, client.email, client.tel, client.profession, client.pointsFidelite);
        }
    }
    fclose(fichier);
}

int validerClient(const char *nomClient) {
    FILE *fichier = fopen("client.txt", "r"); // Ouvre le fichier en mode lecture
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier clients.txt\n");
        return 0; // Échec de validation en cas d'erreur de lecture du fichier
    }

    struct Client client;

    while (fscanf(fichier, "%s %s %d %s %d", client.nom, client.email, &client.tel, client.profession, &client.pointsFidelite) != EOF) {
        if (strcmp(client.nom, nomClient) == 0) {
            fclose(fichier);
            return 1; // Client trouvé et valide
        }
    }

    fclose(fichier);
    return 0; // Client non trouvé ou invalide
}

void ajouterPointsFidelite(struct Client *client, int nombrePoints)
{
    client->pointsFidelite += nombrePoints;
}

void afficherPointsFidelite(const struct Client *client)
{
    printf("Le client a %d points de fidélité.\n", client->pointsFidelite);
}
// Fonction pour enregistrer un nouveau produit dans le fichier
int obtenirDernierCodeProduit()
{
    FILE *fichier;
    fichier = fopen("produit.txt", "r");

    int dernierCode = 0;
    if (fichier != NULL)
    {
        struct Produit produit;
        while (fscanf(fichier, "%d %[^ ] %f %f %d %s\n", &produit.code, produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, produit.derniereDateApprovisionnement) != EOF)
        {
            if (produit.code > dernierCode)
            {
                dernierCode = produit.code;
            }
        }
        fclose(fichier);
    }
    return dernierCode;
}

void enregistrerProduit(struct Produit *produit)
{
    FILE *fichier;
    fichier = fopen("produit.txt", "a");

    if (fichier != NULL)
    {
        int dernierCode = obtenirDernierCodeProduit();
        produit->code = dernierCode + 1;

        fprintf(fichier, "%d | %s | %.2f | %.2f | %d | %s\n", produit->code, produit->designation, produit->prixAchat, produit->prixVente, produit->quantiteStock, produit->derniereDateApprovisionnement);
        fclose(fichier);
        printf("Le produit a ete enregistre avec succes. Code attribue : %d\n", produit->code);
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}



void afficherListeProduits() {
    FILE *fichierProduits;
    fichierProduits = fopen("produit.txt", "r"); // Ouvre le fichier en mode lecture

    if (fichierProduits != NULL) { // Vérifie si le fichier a été ouvert avec succès
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

        fclose(fichierProduits); // Ferme le fichier après utilisation
    } else {
        printf("Erreur : Impossible d'ouvrir le fichier produit.txt\n");
    }
}



// Fonction pour enregistrer un nouveau produit dans le fichier
void rechercherProduitParDesignation(const char *designationRecherche) {
    FILE *fichier;
    fichier = fopen("produit.txt", "r");

    if (fichier != NULL) {
        struct Produit produit;
        int trouve = 0;
        while (fscanf(fichier, "%d %[^ ] %f %f %d %s\n", &produit.code, produit.designation, &produit.prixAchat, &produit.prixVente, &produit.quantiteStock, produit.derniereDateApprovisionnement) != EOF) {
            if (strcmp(produit.designation, designationRecherche) == 0) {
                printf("Produit trouve :\n");
                printf("Designation : %s\n", produit.designation);
                if (produit.quantiteStock > 10) {
                    printf("Prix d'achat : %.2f\n", produit.prixAchat);
                    printf("Prix de vente : %.2f\n", produit.prixVente);
                    printf("Quantite en stock : %d\n", produit.quantiteStock);
                    printf("Derniere date d'approvisionnement : %s\n", produit.derniereDateApprovisionnement);
                } else {
                    printf("\033[1;31m");
                    printf("Code : %d, Designation : %s, Prix de vente : %.2f, Quantite en stock : %d\n", produit.code, produit.designation, produit.prixVente, produit.quantiteStock);
                    printf("\033[0m"); // Remet la couleur par défaut
                    printf("\033[44m");
                    printf("Ce produit doit etre approvisionne !\n");
                }
                trouve = 1; // Marquer comme trouvé
                break; // Sortir de la boucle une fois le produit trouvé
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
void modifierProduit(const char *designationModif) {
    FILE *fichierProduits;
    fichierProduits = fopen("produit.txt", "r+");

    if (fichierProduits != NULL) {
        struct Produit produit;

        while (fread(&produit, sizeof(struct Produit), 1, fichierProduits)) {
            if (strcmp(produit.designation, designationModif) == 0) {
                printf("Entrez la nouvelle designation du produit : ");
                scanf(" %[^\n]s", produit.designation);
                printf("Entrez le nouveau prix d'achat du produit : ");
                scanf("%f", &produit.prixAchat);
                printf("Entrez le nouveau prix de vente du produit : ");
                scanf("%f", &produit.prixVente);
                printf("Entrez la nouvelle quantite en stock du produit : ");
                scanf("%d", &produit.quantiteStock);
                printf("Entrez la nouvelle derniere date d'approvisionnement du produit : ");
                scanf(" %[^\n]s", produit.derniereDateApprovisionnement);

                fseek(fichierProduits, -sizeof(struct Produit), SEEK_CUR);
                fwrite(&produit, sizeof(struct Produit), 1, fichierProduits);
                printf("Le produit a ete modifie avec succes.\n");
                fclose(fichierProduits);
                return;
            }
        }
        printf("Produit non trouve.\n");
        fclose(fichierProduits);
    } else {
        printf("Erreur : Impossible d'ouvrir le fichier produits.txt\n");
    }
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
    srand(time(0));  // Initialisation du générateur de nombres aléatoires avec une graine différente à chaque exécution
    return rand() % 10000;  // Numéro de facture aléatoire entre 0 et 9999
}
// Fonction pour enregistrer la facture dans un fichier
void enregistrerFacture(struct Facture *nouvelleFacture, const struct Commande *commande, float montantTotal) {
    int numeroFacture = genererNumeroFacture();
    int numeroCommandeAssociee = commande->numero;
    int dernierNumero = recupererDernierNumeroCommande();

    nouvelleFacture->numeroCommande = numeroCommandeAssociee;
    nouvelleFacture->montantTotal = montantTotal;
    //nouvelleFacture->montantVerse = 0.0;

    if (commande->montantVerse >= montantTotal) {
        strcpy(nouvelleFacture->statut, "REGLE");
    } else {
        strcpy(nouvelleFacture->statut, "EN COURS");
    }

    FILE *fichier = fopen("facture.txt", "a"); // Ouvre le fichier en mode "append"
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier pour enregistrer la facture.\n");
        return;
    }
    int num = genererNumeroFacture();
    nouvelleFacture->numeroFacture = num;
    fprintf(fichier, "Facture numéro : %d\n", nouvelleFacture->numeroFacture);
    fprintf(fichier, "Numéro de commande associé : %d\n", dernierNumero);
    fprintf(fichier, "Montant total : %.2f\n", nouvelleFacture->montantTotal);
    fprintf(fichier, "Montant versé : %.2f\n", nouvelleFacture->montantVerse);
    fprintf(fichier, "Statut : %s\n", nouvelleFacture->statut);

    // Éventuellement, écrire d'autres détails de la facture

    fprintf(fichier, "----------------------------------------\n");

    fclose(fichier);
}
float calculerMontantTotal(struct Commande *commande) {
    float montantTotal = 0.0;

    struct Produit *produit = commande->listeProduits;
    while (produit != NULL) {
        montantTotal += produit->prixVente * produit->quantiteStock;
        produit = produit->suivant;
    }

    return montantTotal;
}
// Fonction pour récupérer le prix de vente d'un produit depuis le fichier produit.txt
float getPrixVenteFromFichier(const char *designation) {
    FILE *fichierProduits = fopen("produit.txt", "r");
    if (fichierProduits == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier produits.txt\n");
        return -1; // Retourner une valeur indiquant une erreur
    }

    int code;
    char nom[50];
    float prixAchat, prixVente;
    int quantiteStock;
    char derniereDateApprovisionnement[20];

    while (fscanf(fichierProduits, "%d %s %f %f %d %s", &code, nom, &prixAchat, &prixVente, &quantiteStock, derniereDateApprovisionnement) == 6) {
        if (strcmp(nom, designation) == 0) {
            fclose(fichierProduits);
            return prixVente;
        }
    }

    fclose(fichierProduits);
    return -1; // Retourner une valeur indiquant que le produit n'a pas été trouvé
}
// Fonction pour passer une commande
void passerCommande() {
    struct Client nouveauClient;
    struct Commande nouvelleCommande;
    struct Facture nouvelleFacture;

 while (1) {
        printf("Entrez le nom du client : ");
        scanf("%s", nouveauClient.nom);

        int clientExiste = validerClient(nouveauClient.nom);
        if (!clientExiste) {
            printf("Client non trouvé. Veuillez l'enregistrer.\n");
            saisirClient(&nouveauClient);
            enregistrerClient(&nouveauClient);
        } else {
            strcpy(nouvelleCommande.client.nom, nouveauClient.nom);
            break; // Sortir de la boucle si le client est trouvé
        }
    }

    // Générer le numéro de commande une seule fois
    int numeroCommande = genererNumeroFacture();

    nouvelleCommande.numero = numeroCommande;
    nouvelleFacture.numeroCommande = numeroCommande; // Utiliser le même numéro pour la commande et la facture
    int nbProduits;
    printf("Combien de produits souhaitez-vous commander ? ");
    scanf("%d", &nbProduits);

    nouvelleCommande.nbProduits = nbProduits;
    nouvelleCommande.listeProduits = NULL; // Initialisation de la liste de produits

    float montantTotal = 0.0;
    int i;
    for (i = 0; i < nouvelleCommande.nbProduits; i++) {
        struct Produit *nouveauProduit = (struct Produit *)malloc(sizeof(struct Produit));
        if (nouveauProduit == NULL) {
            printf("Erreur d'allocation de memoire pour le produit.\n");
            // Gérer l'échec de l'allocation mémoire comme requis
            return;
        }

        printf("Entrez la designation du produit %d : ", i + 1);
        scanf("%s", nouveauProduit->designation);

        int produitExiste = verifierDesignationExiste(nouveauProduit->designation);
        if (produitExiste) {
            printf("Produit existant. Entrez la quantite : ");
            scanf("%d", &nouveauProduit->quantiteStock);
            float prixVente = getPrixVenteFromFichier(nouveauProduit->designation);
            if (prixVente != -1) {
                montantTotal += prixVente * nouveauProduit->quantiteStock;
            } else {
                printf("Erreur : Produit non trouve ou prix de vente non disponible.\n");
                free(nouveauProduit); // Libérer la mémoire allouée pour le produit
                i--; // Décrémenter pour ressaisir ce produit
                continue;
            }
        } else {
            printf("Produit inexistant!\n");
            free(nouveauProduit); // Libérer la mémoire allouée pour le produit
            i--; // Décrémenter pour ressaisir ce produit
            continue;
        }

        // Autres détails à saisir pour le produit
        // ...

        nouveauProduit->suivant = nouvelleCommande.listeProduits;
        nouvelleCommande.listeProduits = nouveauProduit;
    }

    float montantVerse;
    printf("Montant versé par le client : ");
    scanf("%f", &montantVerse);
    nouvelleCommande.montantVerse = montantVerse;

    // Vérification du statut de la facture
    if (nouvelleCommande.montantVerse >= montantTotal) {
        strcpy(nouvelleFacture.statut, "REGLE");
    } else {
        strcpy(nouvelleFacture.statut, "EN COURS");
    }
    if (nouvelleCommande.montantVerse >= montantTotal) {
        recompenserClient(&nouveauClient, montantTotal);
    }
    enregistrerCommande(&nouvelleCommande);
    //creerFacture(&nouvelleFacture, &nouvelleCommande, montantTotal);
    nouvelleFacture.montantVerse = montantVerse;
    enregistrerFacture(&nouvelleFacture, &nouvelleCommande, montantTotal);
    //recompenserClient(nouveauClient.nom, montantTotal);

    //nouvelleFacture.montantVerse = montantVerse;
    //
}




int recupererDernierNumeroCommande() {
    int dernierNumero;
    FILE *fichier = fopen("dernier_numero_commande.txt", "r");
    if (fichier != NULL) {
        fscanf(fichier, "%d", &dernierNumero);
        fclose(fichier);
    } else {
        printf("Erreur lors de la lecture du dernier numéro de commande.\n");
        // Gérer l'erreur comme nécessaire (par exemple, en renvoyant -1)
        dernierNumero = -1;
    }
    return dernierNumero;
}


// Fonction pour sauvegarder le dernier numéro de commande dans un fichier
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
            fprintf(fichier, "Produit %d : %s, Quantite : %d\n", i + 1, nouvelleCommande->listeProduits[i].designation, nouvelleCommande->listeProduits[i].quantiteStock);
        }

        fprintf(fichier, "\n");
        fclose(fichier);

        sauvegarderDernierNumeroCommande(dernierNumero); // Sauvegarde du nouveau numéro
        system("cls");
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
// Fonction pour créer une facture à partir d'une commande
void creerFacture(struct Facture *nouvelleFacture, const struct Commande *commande, float montantTotal) {
    int numeroFacture = genererNumeroFacture(); // Générer le numéro de facture une fois
    struct Facture facture;

    // Utiliser le numéro de commande de la commande passée en paramètre
    int numeroCommandeAssociee = commande->numero;

    nouvelleFacture->numeroCommande = numeroCommandeAssociee;
    nouvelleFacture->montantTotal = montantTotal;
    //nouvelleFacture->montantVerse = 0.0;

    if (commande->montantVerse >= montantTotal) {
        strcpy(nouvelleFacture->statut, "REGLE");
    } else {
        strcpy(nouvelleFacture->statut, "EN COURS");
    }

    FILE *fichier = fopen("facture.txt", "a");
    if (fichier != NULL) {
        fprintf(fichier, "Facture numéro : %d\n", numeroFacture); // Utilisation du numéro de facture généré
        fprintf(fichier, "Numero de commande associe : %d\n", nouvelleFacture->numeroCommande);
        fprintf(fichier, "Montant total : %.2f\n", nouvelleFacture->montantTotal);
        fprintf(fichier, "Montant versé : %.2f\n", facture.montantVerse);
        fprintf(fichier, "Statut : %s\n", nouvelleFacture->statut);
        fprintf(fichier, "----------------------------------------\n");

        fclose(fichier);
        printf("La facture a ete enregistree avec succes.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier de factures.\n");
    }
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

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "Numero de facture : %d", &numeroFacture) == 1) {
            printf("Numero de facture : %d\n", numeroFacture);
        } else if (sscanf(ligne, "Statut : %[^\n]", statut) == 1) {
            printf("Statut de la facture : %s\n", statut);
        } else if (sscanf(ligne, "Montant total : %f", &montantTotal) == 1) {
            printf("Montant total : %.2f\n", montantTotal);
        } else if (sscanf(ligne, "Montant verse : %f", &montantVerse) == 1) {
            printf("Montant verse : %.2f\n", montantVerse);
        }
    }

    fclose(fichier);
}
void afficherFacturesEnCours() {
    FILE *fichier;
    FILE *fichierCommande;
    fichier = fopen("facture.txt", "r");
    fichierCommande = fopen("commandes.txt", "r");

    if (fichier == NULL || fichierCommande == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int numeroFacture, numeroCommande;
    char statut[20];
    float montantTotal, montantVerse;
    char ligne[100];
    char Client[50];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "Facture numéro : %d", &numeroFacture) == 1) {
            // Lire les autres détails de la facture
            fgets(ligne, sizeof(ligne), fichier); // Numéro de commande associé
            sscanf(ligne, "Numéro de commande associé : %d", &numeroCommande);

            fgets(ligne, sizeof(ligne), fichier); // Montant total
            sscanf(ligne, "Montant total : %f", &montantTotal);

            fgets(ligne, sizeof(ligne), fichier); // Montant versé
            sscanf(ligne, "Montant versé : %f", &montantVerse);

            fgets(ligne, sizeof(ligne), fichier); // Statut
            sscanf(ligne, "Statut : %[^\n]", statut);

            fgets(ligne, sizeof(ligne), fichierCommande);
            sscanf(ligne, "Client : %[^\n]", Client);

            if (strcmp(statut, "EN COURS") == 0) {
                printf("Numero de facture : %d\n", numeroFacture);
                printf("Numero de commande associe : %d\n", numeroCommande);
                printf("Montant total : %.2f\n", montantTotal);
                printf("Montant verse : %.2f\n", montantVerse);
                printf("Statut de la facture : %s\n", statut);
                printf("Nom du client : %s\n", Client);
                printf("----------------------------------------\n");
            }
        }
    }

    fclose(fichier);
    fclose(fichierCommande);
}

void afficherFacturesRegles() {
    FILE *fichier;
    fichier = fopen("facture.txt", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int numeroFacture, numeroCommande;
    char statut[20];
    float montantTotal, montantVerse;
    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "Facture numéro : %d", &numeroFacture) == 1) {
            // Lire les autres détails de la facture
            fgets(ligne, sizeof(ligne), fichier); // Numéro de commande associé
            sscanf(ligne, "Numéro de commande associé : %d", &numeroCommande);

            fgets(ligne, sizeof(ligne), fichier); // Montant total
            sscanf(ligne, "Montant total : %f", &montantTotal);

            fgets(ligne, sizeof(ligne), fichier); // Montant versé
            sscanf(ligne, "Montant versé : %f", &montantVerse);


            fgets(ligne, sizeof(ligne), fichier); // Statut
            sscanf(ligne, "Statut : %[^\n]", statut);

            if (strcmp(statut, "REGLE") == 0) {
                printf("Numero de facture : %d\n", numeroFacture);
                printf("Numero de commande associe : %d\n", numeroCommande);
                printf("Montant total : %.2f\n", montantTotal);
                printf("Montant verse : %.2f\n", montantVerse);
                printf("Statut de la facture : %s\n", statut);
                printf("----------------------------------------\n");
            }
        }
    }

    fclose(fichier);
}
// Fonction pour récompenser le client et mettre à jour les points de fidélité dans le fichier
void recompenserClientDansFichier(char *nomClient, int pointsAjoutes) {
    FILE *fichierTemp;
    FILE *fichierClient;
    struct Client tempClient;

    fichierTemp = fopen("temp.txt", "w"); // Fichier temporaire pour écrire les modifications
    fichierClient = fopen("client.txt", "r"); // Fichier client.txt en mode lecture

    if (fichierClient == NULL || fichierTemp == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Parcours du fichier client.txt et mise à jour des points de fidélité pour le client spécifié
    while (fscanf(fichierClient, "%s %s %d %s %d %s", tempClient.nom, tempClient.email, &tempClient.tel, tempClient.profession, &tempClient.pointsFidelite, tempClient.adresse) != EOF) {
        if (strcmp(tempClient.nom, nomClient) == 0) {
            tempClient.pointsFidelite += pointsAjoutes;
        }
        fprintf(fichierTemp, "%s %s %d %s %d %s\n", tempClient.nom, tempClient.email, tempClient.tel, tempClient.profession, tempClient.pointsFidelite, tempClient.adresse);
    }

    fclose(fichierClient);
    fclose(fichierTemp);

    remove("client.txt"); // Suppression du fichier client.txt
    rename("temp.txt", "client.txt"); // Renommage du fichier temporaire en client.txt
    printf("Points de fidélité mis à jour dans le fichier.\n");
}

// Fonction pour récompenser le client en fonction du montant de la facture
void recompenserClient(struct Client *client, float montantFacture) {
    int pointsAjoutes = 0;

    if (montantFacture > 50000 && montantFacture <= 100000) {
        pointsAjoutes = 1;
    } else if (montantFacture > 100000) {
        pointsAjoutes = 3;
    }

    // Charger les données du fichier
    FILE *fichier = fopen("client.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fichier == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    struct Client clientActuel;
    while (fscanf(fichier, "%s %s %d %s %d", clientActuel.nom, clientActuel.email, &clientActuel.tel, clientActuel.profession, &clientActuel.pointsFidelite) != EOF) {
        if (strcmp(clientActuel.nom, client->nom) == 0) {
            clientActuel.pointsFidelite += pointsAjoutes;
        }
        fprintf(temp, "%s %s %d %s %d\n", clientActuel.nom, clientActuel.email, clientActuel.tel, clientActuel.profession, clientActuel.pointsFidelite);
    }

    fclose(fichier);
    fclose(temp);

    remove("client.txt");
    rename("temp.txt", "client.txt");
}

void supprimerProduit(const char *designationSuppression) {
    FILE *fichier;
    FILE *temp;
    fichier = fopen("produit.txt", "rb");
    temp = fopen("temp.txt", "wb");

    if (fichier != NULL && temp != NULL) {
        struct Produit produit;

        while (fread(&produit, sizeof(struct Produit), 1, fichier)) {
            if (strcmp(produit.designation, designationSuppression) != 0) {
                fwrite(&produit, sizeof(struct Produit), 1, temp);
            }
        }

        fclose(fichier);
        fclose(temp);

        remove("produit.txt");
        rename("temp.txt", "produit.txt");
        printf("Le produit a ete supprime avec succes.\n");
    } else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}

void supprimerClient(const char *nomClientASupprimer, int telClientASupprimer) {
    FILE *fichierLecture, *fichierEcriture;
    fichierLecture = fopen("client.txt", "r");
    fichierEcriture = fopen("temp.txt", "w");

    if (fichierLecture == NULL || fichierEcriture == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    char ligne[200]; // Supposons que chaque ligne contient au maximum 200 caractères

    while (fgets(ligne, sizeof(ligne), fichierLecture)) {
        char nom[50], email[50];
        int tel;
        sscanf(ligne, "%s %s %d", nom, email, &tel);

        if (strcmp(nom, nomClientASupprimer) != 0 || tel != telClientASupprimer) {
            fputs(ligne, fichierEcriture);
        }
    }

    fclose(fichierLecture);
    fclose(fichierEcriture);

    remove("client.txt"); // Supprimer l'ancien fichier client
    rename("temp.txt", "client.txt"); // Renommer le fichier temporaire en client.txt
    printf("Le client a ete supprime avec succes.\n");
}

