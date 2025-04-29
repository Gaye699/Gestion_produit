# 🛒 Gestion de Produits - Projet C

Ce projet est une application en langage C conçue pour permettre à un propriétaire de magasin de gérer efficacement ses produits, ses clients, les commandes, et la facturation. L'application utilise la **compilation séparée**, des **listes chaînées**, et enregistre toutes les données dans des **fichiers texte structurés**.

---

## ✨ Fonctionnalités principales

### 🔹 Gestion des Produits
- Ajouter un nouveau produit
- Modifier un produit existant
- Rechercher un produit par désignation
- Afficher les produits en zone rouge (stock < 10)

### 🔹 Gestion des Clients
- Enregistrer un nouveau client
- Supprimer un client
- Afficher la liste des clients
- Récompenser un client fidèle (points fidélité)

### 🔹 Commandes & Factures
- Passer une commande
- Générer automatiquement une facture
- Calculer le statut de la facture : `EN COURS` ou `REGLE`
- Afficher les factures en cours ou réglées
- Associer chaque facture à un client et sa commande

---

## 🗃️ Sauvegarde des données

Les informations sont conservées dans les fichiers suivants :
- `produit.txt` : Produits en stock (code, désignation, prix, quantité, date appro.)
- `client.txt` : Informations clients (nom, contact, profession, points)
- `commandes.txt` : Historique des commandes (numéro, client, produits)
- `facture.txt` : Historique des factures (numéro, statut, montant total, versé)

---

## 🏆 Fidélisation Client

À chaque **facture réglée**, des points fidélité sont attribués :
- **1 point** si la facture est > 50 000 FCFA et ≤ 100 000 FCFA
- **3 points** si la facture est > 100 000 FCFA

Les points sont enregistrés et mis à jour dans le fichier `client.txt`.

---

## 🧪 Technologies et contraintes

- **Langage** : C (ISO C99)
- **Modèle de données** : Listes chaînées
- **Stockage** : Fichiers `.txt`
- **Organisation** : Compilation séparée (`.c` + `.h`)
- **Projet collaboratif**

---

## 🛠 Structure du projet

Gestion_produit/ 
              ├── main.c 
              ├── fonction.c 
              ├── fonction.h 
              ├── structure.h 
              ├── const.h ├
              ── produit.txt 
              ├── client.txt 
              ├── commandes.txt 
              ├── facture.txt 
              ├── Makefile

---

## 🚀 Pour compiler le projet

### ▶️ Avec Code::Blocks
1. Crée un projet `Console Application`
2. Ajoute tous les fichiers `.c` et `.h`
3. Compile avec `F9`

### ▶️ Avec terminal (GCC)
```bash
gcc main.c fonction.c -o gestion_produit.exe
./gestion_produit.exe
