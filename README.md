# Gestion_produit
Il s'agit d'un programme de gestion de produit dans un magasin

Un propri´etaire de magasin vous contacte pour que vous lui d´eveloppez une application de gestion
de ses produits. Un produit est caract´eris´e par un code, sa d´esignation, le prix d’achat chez un fournisseur, le prix de vente dans le magasin, la quantit´e en stock, la derni`ere date d’approvisionnement
(prenez le format de votre choix). Un produit passe au rouge si sa quantit´e en stock est inf´erieure
`a 10 et il doit dans ce cas ˆetre approvisionn´e.
Pour fid´eliser ses clients, le propri´etaire souhaite aussi les suivre, un client est caract´eris´e par
un num´ero (sur 6 caract`eres au plus), son nom, son email, son tel, sa profession si possible et un
nombre repr´esentant ses points de fid´elit´e. Un client peut passer une commande qui doit contenir
un num´ero de commande (un entier), la liste des produits de la commande avec leur quantit´e et
le client qui l’a pass´e. Une commande cr´ee, entraine la cr´eation d’une facture, une facture est
caract´eris´ee par un num´ero de facture, un num´ero de commande, son montant total (qui d´epend de
la liste des produits dans la commande), le montant vers´e. Il est possible de savoir `a tout moment
le statut d’une facture (EN COURS, REGLE). Une facture EN COURS est celle qui n’a pas encore ´
´et´e totalement r´egl´ee et celle avec un statut REGLE est celle dont montant restant est nul. ´
On souhaite r´ealiser les op´erations suivantes (liste non exhaustive) :
• Enregistrer un nouveau produit
• Modifier un produit existant
• Rechercher un produit
• Passer une commande
• Quels sont les produits qui sont en zone rouge
• Quelles sont les factures (avec les nom, contacts etc des clients) qui ne sont pas encore r´egl´ees.
• Ajouter un client
• R´ecompenser une client. Cette op´eration consiste `a ajouter un nombre de points sur les points
de fid´elit´e d’un client `a chaque facture r´egl´ee. Ces points se calculent de la mani`ere suivante
: Chaque facture r´egl´ee d’un montant sup´erieur `a 50000 FCFA et inf´erieur `a 100000 FCFA
vaut 1 point et les factures r´egl´ees d’un montant sup´erieur `a 100000 FCFA valent 3 points.
Cette op´eration doit ˆetre r´ealis´ee `a chaque fois que le client r`egle une facture.

Afin de rendre plus attrayante votre application, pensez `a sauvegarder les informations de chaque
session dans des fichiers.
1. Un fichier clients.txt qui contiendra les informations sur tous les clients du magasin.
2. Un fichier produits.txt qui contiendra les informations sur l’ensemble des produits du magasin.
3. Un fichier commandes.txt qui contiendra l’ensemble des information sur les commandes
effectu´ees.
4. Un fichier factures.txt sur l’ensemble des factures.
Pour la gestion des fichiers, il est fortement recommander de bien formater le contenu. Une
structure possible est la suivante pour le fichier de produits.txt : Chaque ligne est un produit :
PD001 | biscuit | 100 | 200 | 60 | 10/12/2023
PD003 | t´el´eviseur LG 49 pouces | 200000 | 230000 | 15 | 10/09/2023
o`u le premier produit a pour code PD001, sa d´esignation est biscuit, son prix d’achat est 100
FCFA et son prix de vente est 200 FCFA, sa quantit´e disponible ou en stock est 60 et la date du
dernier approvisionnement est 10/12/2023. Faire pareil pour les autres fichiers, imaginer votre
propre structure ou formatage. Pour la lecture dans le fichier, informez-vous sur comment faire le
Split d’une chaine de caract`eres.
Modalit´e de livraison du travail:
• Vous devez utiliser les listes chain´ees pour r´ealiser le travail.
• Les projets seront r´ealis´es en groupe, d´epos´e sur GitHub, chaque ´etudiant du groupe devra
obligatoirement contribuer `a la r´ealisation du projet sinon la note 0 lui sera attribu´ee.
• Le d´elai de livraison est de 3 semaines `a partir de la date de r´eception.
• Chaque groupe devra exposer son travail, le jour de pr´esentation sera fix´e au pr´ealable.
• Utiliser la compilation s´epar´ee ¸ca veut dire vous devez avoir un Makefile et les fichiers .h et
.c de votre projet.
• La note de TP compte pour 50% de la note finale de l’examen.
Remarque: Pour toute ´eventuelle question, bien vouloir contacter l’examinateur M. Samuel
NYOBE (samuel.nyobe@facsciences-uy1.cm)
