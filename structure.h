#ifndef STRUCTURE_H
#define STRUCTURE_H
struct Client {
    char nom[50];
    char email[50];
    int tel;
    char profession[50];
    int pointsFidelite;
    struct Client *suivant; // Pointeur vers le prochain client dans la liste
    char adresse[30];
};

struct Produit {
    int code;
    char designation[50];
    float prixAchat;
    float prixVente;
    int quantiteStock;
    char derniereDateApprovisionnement[20];
    struct Produit *suivant; // Pointeur vers le prochain produit dans la liste
};

typedef struct Commande
{
    int numero;
    struct Client client;
    struct Produit *listeProduits; // Pointeur vers la liste chaînée de produits
    int nbProduits;
    char statut[20];
    float montantVerse;

}Commande;
struct Facture
{
    int numeroFacture;
    int numeroCommande; // Ajout du numéro de commande dans la facture
    float montantTotal;
    float montantVerse;
    char statut[20]; // "EN COURS" ou "REGLE"
    struct Client client;
};
#endif /* STRUCTURES_H */
