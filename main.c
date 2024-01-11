#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // Pour rand() et srand()
#include "const.h"
#include "structure.h"
#include "fonction.h"




int main(){
    srand(time(0)); // Initialisation du générateur de nombres aléatoires une seule fois
    int choix,choix2,nouveauClient,telClientASupprimer,n,produit,uneFacture;
    int code,mdp = 0000;
    char nomClientASupprimer[50],nomProduit[30],designation[30],designation2[30];
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
        printf("Entrer votre code: ");
        scanf("%d",&code);

         if(code == mdp)
    {
        system("cls");
        int choixProprietaire;
        printf("1- Changer le mot de passe\n");
        printf("2- Menu principale\n");
        printf("Choix: ");
        scanf("%d", &choixProprietaire);
        if (choixProprietaire == 1)
        {
             int nouveauMdp;
            printf("Entrez le nouveau mot de passe : ");
            scanf("%d", &nouveauMdp);
            mdp = nouveauMdp; // Mettre à jour le mot de passe
            printf("Le mot de passe a été mis à jour avec succès.\n");
        }else
        if (choixProprietaire == 2){
        system("cls");
        do
        {
            printf("\033[44m"); // Change tout le fond en bleu
            //printf("\033[44;37m"); // Change le fond en bleu et le texte en blanc

            MENU_PRINCIPALE;
            printf("Choisissez une option : ");
            scanf("%d", &choix);

            switch (choix)
            {
             case 1:
                // Ajouter un nouveau produit
                // Ajouter un nouveau produit
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

                printf("Entrez la designation du produit : ");
                scanf("%s", &nomProduit);
                system("cls");
                rechercherProduitParDesignation(nomProduit);
                break;

            case 3:
                // Modifier un produit
                printf("Entrez la designation du produit a modifier : ");
                scanf("%s", &designation);
                modifierProduit(designation);
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
                //afficher factures regle
                system("cls");
                afficherFacturesRegles();
                break;
            case 7:
               //afficher factures en cours
                system("cls");
                afficherFacturesEnCours();
                break;
            case 8:
                system("cls");
                printf("Entrer la designation du produit a supprimer: ");
                scanf("%s",&designation2);
                supprimerProduit(designation2);
                break;
            case 9:
                 system("cls");
                printf("Entrez le nom du client a supprimer : ");
                scanf("%s", nomClientASupprimer);
                printf("Entrez le numero de telephone du client a supprimer : ");
                scanf("%d", &telClientASupprimer);
                supprimerClient(nomClientASupprimer, telClientASupprimer);
                break;
            case 10:
                system("cls");
                printf("Liste des clients enregistrer:\n\n");
                afficherListeClient();
                break;
            case 11:
                printf("Au revoir !\n");
                break;
            default:
                system("cls");
                printf("Choix invalide.\n");
            }
        }
        while (choix != 11);
        system("cls");
    }

    }else{printf("Mot de passe incorrecte !");}
    }
    if(n == 2)
    {
        do{
        printf("\033[44m"); // Change tout le fond en bleu
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



