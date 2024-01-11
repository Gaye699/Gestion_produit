#ifndef FONCTION_H
#define FONCTION_H
#include "structure.h" // Inclure les structures nécessaires

void enregistrerProduit(struct Produit *nouveauProduit);
void saisirClient(struct Client *nouveauClient);
void enregistrerClient(struct Client *nouveauClient);
void afficherListeClient();
int validerClient(const char *nomClient);
void passerCommande();
int genererNumeroFacture();
int verifierDesignationExiste(const char *designationSaisie);
void modifierProduit(const char *designationModif);
void rechercherProduitParDesignation(const char *designationRecherche);
void afficherListeProduits() ;
void afficherPointsFidelite(const struct Client *client);
void ajouterPointsFidelite(struct Client *client, int nombrePoints);
int recupererDernierNumeroCommande() ;
void sauvegarderDernierNumeroCommande(int dernierNumero);
void enregistrerCommande(struct Commande *nouvelleCommande);
void afficherProduitEnZoneRouge();
void creerFacture(struct Facture *nouvelleFacture, const struct Commande *commande, float montantTotal);
void enregistrerFacture(struct Facture *nouvelleFacture, const struct Commande *commande, float montantTotal);
void afficherStatutFacture();
void recompenserClient(struct Client *client, float montantFacture);
void recompenserClientDansFichier(char *nomClient, int pointsAjoutes);
void supprimerProduit(const char *designationSuppression);
void supprimerClient(const char *nomClientASupprimer, int telClientASupprimer);
float calculerMontantTotal(struct Commande *commande);

#endif // FONCTION_H

