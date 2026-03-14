# Unrolled Linked List C

> 📌 **This documentation is available in two versions / Cette documentation est disponible en deux versions**
> - **English**: See section [## English Version](#english-version) below
> - **Français**: Voir la section [## Version Française](#version-française) ci-dessous

---

# English Version

## 📝 Description

**Unrolled Linked List** project written in C that demonstrates how to store values inside chained pages instead of using one node per element.

This project implements an **unrolled linked list** data structure where each node, called a page, stores multiple values and a bitmap indicating which slots are occupied. It provides insertion, search, deletion by location, compaction, display, and memory cleanup.

The repository contains **two implementations**:
- A **normal version** dedicated to `int`
- A **generic macro-based version** supporting `int`, `char`, and `float`

## 📐 Data Structure Principle

### Unrolled Linked List

Instead of storing one value per node like a classic linked list, an unrolled linked list stores several values inside each node:

```text
Page 0                 Page 1
+-----------+          +-----------+
| 5 | 9 | - |  ---->   | 2 | - | 7 |
+-----------+          +-----------+
 bitmap: 110           bitmap: 101
```

Each page contains:
- An array of values
- A bitmap used to know which positions are filled
- A pointer to the next page

In this project, the page capacity is chosen by the user between `1` and `8`, because the occupancy is stored in an 8-bit bitmap.

## 🔐 Core Operations

1. **Initialization**:
	- Ask the user how many elements a page can contain
	- Allocate the first page
	- Initialize counters and bitmap

2. **Insertion**:
	- Scan pages to find the first free slot
	- Store the value in that slot
	- Create a new page if all existing pages are full

3. **Search**:
	- Traverse all pages
	- Compare occupied slots with the requested value
	- Store every matching location in a dynamic result array

4. **Deletion**:
	- Remove a value using its page reference and index
	- Clear the corresponding bitmap bit

5. **Compaction**:
	- Move values leftward into the first holes found
	- Reduce fragmentation after deletions
	- Remove empty pages at the end in the normal implementation

## 📂 Project Structure

```text
unrolled-linked-list-c/
├── makefile                         # Build configuration
├── README.md                        # Documentation (this file)
├── unrolledLinkedListNormal.c       # Demo program for the int-only version
├── unrolledLinkedListDynamic.c      # Demo program for the generic version
├── include/
│   ├── colorConsole.h               # ANSI color macros for terminal output
│   ├── listManagementNormal.h       # Structures and prototypes for the normal version
│   └── listManagementDynamic.h      # Macros, structures, and prototypes for the generic version
└── src/
	 ├── listManagementNormal.c       # Implementation of the int-only unrolled list
	 └── listManagementDynamic.c      # Macro-generated generic implementation
```

## ✨ Features

- **Unrolled list implementation**: Store multiple values per node/page
- **Configurable page size**: Choose the number of elements per page from `1` to `8`
- **Insertion**: Add values while reusing free slots when possible
- **Search**: Retrieve every occurrence of a given value
- **Deletion by location**: Remove values precisely from known positions
- **Compaction**: Move values to fill holes left by deletions
- **Typed generic version**: Support `int`, `char`, and `float` through macros
- **Colored output**: Display page occupancy and values with ANSI colors
- **Memory cleanup**: Free all allocated pages before program exit

## 🔧 Requirements

- GCC (GNU Compiler Collection)
- Make
- Bash or Unix/Linux terminal
- No external dependencies (standard C library only)

## 💾 Build & Run

```bash
make                         # Compile both executables
./unrolledLinkedListNormal   # Run the int-only demo
./unrolledLinkedListDynamic  # Run the generic typed demo
make clean                   # Remove object files and executables
```

## 🚀 Usage

### 1️⃣ Normal Version

The `unrolledLinkedListNormal` program:
- Creates a list of `int`
- Asks the user for the page capacity
- Inserts random integers
- Prints the list state
- Searches for occurrences of `9`
- Removes them
- Compacts the list
- Prints the final state

### 2️⃣ Dynamic Generic Version

The `unrolledLinkedListDynamic` program:
- Creates three lists: `int`, `char`, and `float`
- Asks the user for each page capacity
- Inserts random values into each list
- Prints each list
- Searches and removes one target value per type
- Compacts each list
- Frees all allocated memory

## 💡 Usage Examples

### Example 1: Normal Version

```bash
$ ./unrolledLinkedListNormal

Choose the number of elements in a page (1-8): 4

LIST: int

Page 0 : 1111
  [0]  3
  [1]  9
  [2]  1
  [3]  6

Page 1 : 1111
  [0]  9
  [1]  4
  [2]  8
  [3]  2

# The program then removes all 9 values and compacts the list
```

### Example 2: Dynamic Version

```bash
$ ./unrolledLinkedListDynamic
Choose the number of elements in a page (1-8): 3
Choose the number of elements in a page (1-8): 3
Choose the number of elements in a page (1-8): 3

LIST: int
...
Removed occ in List:
...
Compacted List:
...

-----------------------------

LIST: char
...

-----------------------------

LIST: float
...
```

## ⚙️ Page Capacity Limit

The maximum page capacity is `8` because the list uses a `uint8_t` bitmap.

Each bit of the bitmap represents one slot:

```text
bit:    7 6 5 4 3 2 1 0
state:  0 0 0 1 1 0 1 1
```

If bit `i` is set to `1`, the slot `i` contains a value. If it is `0`, the slot is empty.

## 📄 License

This project is provided for exemple purposes.

---

**Author**: Nitros  
**Date**: March 2026  
**Language**: C

---

# Version Française

## 📝 Description

Projet de **Unrolled Linked List** écrit en C permettant de stocker plusieurs valeurs dans chaque nœud de la liste chaînée au lieu d’une seule.

Ce projet implémente une structure de données de type **liste chaînée déroulée** dans laquelle chaque nœud, appelé page, contient plusieurs valeurs ainsi qu’un bitmap indiquant quelles cases sont occupées. Le programme fournit les opérations d’insertion, recherche, suppression par position, compaction, affichage et libération mémoire.

Le dépôt contient **deux implémentations** :
- Une **version classique** dédiée au type `int`
- Une **version générique par macros** compatible avec `int`, `char` et `float`

## 📐 Principe de la structure

### Unrolled Linked List

Au lieu de stocker une seule valeur par nœud comme une liste chaînée classique, une unrolled linked list stocke plusieurs valeurs dans chaque page :

```text
Page 0                 Page 1
+-----------+          +-----------+
| 5 | 9 | - |  ---->   | 2 | - | 7 |
+-----------+          +-----------+
 bitmap: 110           bitmap: 101
```

Chaque page contient :
- Un tableau de valeurs
- Un bitmap pour savoir quelles positions sont occupées
- Un pointeur vers la page suivante

Dans ce projet, la capacité d’une page est choisie par l’utilisateur entre `1` et `8`, car l’occupation est stockée dans un bitmap sur 8 bits.

## 🔐 Opérations principales

1. **Initialisation** :
	- Demande à l’utilisateur combien d’éléments une page peut contenir
	- Alloue la première page
	- Initialise les compteurs et le bitmap

2. **Insertion** :
	- Parcourt les pages pour trouver le premier emplacement libre
	- Stocke la valeur dans cette case
	- Crée une nouvelle page si toutes les pages existantes sont pleines

3. **Recherche** :
	- Traverse toutes les pages
	- Compare les cases occupées avec la valeur recherchée
	- Stocke toutes les positions trouvées dans un tableau dynamique de résultats

4. **Suppression** :
	- Supprime une valeur à partir de sa page et de son indice
	- Efface le bit correspondant dans le bitmap

5. **Compaction** :
	- Déplace les valeurs vers les premiers trous disponibles
	- Réduit la fragmentation après suppression
	- Supprime les pages vides à la fin dans la version normale

## 📂 Structure du projet

```text
unrolled-linked-list-c/
├── makefile                         # Configuration de compilation
├── README.md                        # Documentation (ce fichier)
├── unrolledLinkedListNormal.c       # Programme de démonstration pour la version int
├── unrolledLinkedListDynamic.c      # Programme de démonstration pour la version générique
├── include/
│   ├── colorConsole.h               # Macros ANSI pour la coloration du terminal
│   ├── listManagementNormal.h       # Structures et prototypes de la version normale
│   └── listManagementDynamic.h      # Macros, structures et prototypes de la version générique
└── src/
	 ├── listManagementNormal.c       # Implémentation de la liste déroulée en int
	 └── listManagementDynamic.c      # Implémentation générique générée par macros
```

## ✨ Fonctionnalités

- **Implémentation d’unrolled list** : plusieurs valeurs stockées par page
- **Taille de page configurable** : choix du nombre d’éléments par page entre `1` et `8`
- **Insertion** : ajout de valeurs en réutilisant les cases libres
- **Recherche** : récupération de toutes les occurrences d’une valeur
- **Suppression par position** : suppression précise à partir d’une localisation connue
- **Compaction** : déplacement des valeurs pour remplir les trous
- **Version générique typée** : prise en charge de `int`, `char` et `float` via macros
- **Affichage coloré** : visualisation des bitmaps et des valeurs avec des couleurs ANSI
- **Nettoyage mémoire** : libération de toutes les pages allouées avant la fin du programme

## 🔧 Prérequis

- GCC (GNU Compiler Collection)
- Make
- Bash ou terminal Unix/Linux
- Aucune dépendance externe (utilise uniquement la bibliothèque standard C)

## 💾 Compilation et exécution

```bash
make                         # Compile les deux exécutables
./unrolledLinkedListNormal   # Lance la démo de la version int
./unrolledLinkedListDynamic  # Lance la démo de la version générique typée
make clean                   # Supprime les fichiers objets et les exécutables
```

## 🚀 Utilisation

### 1️⃣ Version normale

Le programme `unrolledLinkedListNormal` :
- Crée une liste de `int`
- Demande à l’utilisateur la capacité des pages
- Insère des entiers aléatoires
- Affiche l’état de la liste
- Recherche les occurrences de `9`
- Les supprime
- Compacte la liste
- Affiche l’état final

### 2️⃣ Version générique dynamique

Le programme `unrolledLinkedListDynamic` :
- Crée trois listes : `int`, `char` et `float`
- Demande une capacité de page pour chaque type
- Insère des valeurs aléatoires dans chaque liste
- Affiche chaque liste
- Recherche et supprime une valeur cible par type
- Compacte chaque liste
- Libère toute la mémoire allouée

## 💡 Exemples d’utilisation

### Exemple 1 : Version normale

```bash
$ ./unrolledLinkedListNormal

Choose the number of elements in a page (1-8): 4

LIST: int

Page 0 : 1111
  [0]  3
  [1]  9
  [2]  1
  [3]  6

Page 1 : 1111
  [0]  9
  [1]  4
  [2]  8
  [3]  2

# Le programme supprime ensuite toutes les occurrences de 9 puis compacte la liste
```

### Exemple 2 : Version générique

```bash
$ ./unrolledLinkedListDynamic
Choose the number of elements in a page (1-8): 3
Choose the number of elements in a page (1-8): 3
Choose the number of elements in a page (1-8): 3

LIST: int
...
Removed occ in List:
...
Compacted List:
...

-----------------------------

LIST: char
...

-----------------------------

LIST: float
...
```

## ⚙️ Limite de capacité des pages

La capacité maximale d’une page est `8` car la liste utilise un bitmap de type `uint8_t`.

Chaque bit du bitmap représente une case :

```text
bit:    7 6 5 4 3 2 1 0
state:  0 0 0 1 1 0 1 1
```

Si le bit `i` vaut `1`, la case `i` contient une valeur. S’il vaut `0`, la case est vide.

## 📄 License

Ce projet est mis à disposition à titre d'exemple.

---

**Auteur** : Nitros  
**Date** : Mars 2026  
**Langage** : C