# Mini-Shell Unix en C

## Description du projet

Ce projet est un interpréteur de commandes Unix écrit en langage C. Il vise à reproduire le fonctionnement d’un mini-shell tout en explorant des fonctionnalités avancées telles que l’exécution de processus en arrière-plan et la gestion des tâches suspendues. Le projet a pour but principal d’approfondir la compréhension des appels système Unix et des mécanismes de gestion des processus.

---

## Objectifs pédagogiques

- Maîtriser les appels système liés à la création et gestion des processus (`fork`, `exec`, `wait`).
- Comprendre la communication inter-processus (redirections, pipes).
- Appréhender la gestion des signaux (SIGINT, SIGTSTP) et leur interaction avec les processus.
- Manipuler le terminal et gérer les entrées/sorties.

---

## Fonctionnalités implémentées

✅ **Exécution de commandes** avec recherche dans le `$PATH`.  
✅ **Redirections d’entrée/sortie** :  
- `>` pour rediriger la sortie standard vers un fichier,  
- `<` pour rediriger l’entrée standard à partir d’un fichier,  
- `2>` pour rediriger la sortie d’erreur.  
✅ **Pipes** (`|`) permettant la communication entre plusieurs commandes.  
✅ **Historique des commandes** (commande `history`).  
✅ **Gestion des signaux** :  
- Interruption (Ctrl+C)  
- Suspension (Ctrl+Z)  
✅ **Navigation dans l’arborescence** avec la commande `cd`.

---

## Fonctionnalités en cours de développement

🔄 **Exécution des commandes en arrière-plan** via l’opérateur `&`.  
🔄 **Commande `jobs`** pour lister les processus en tâche de fond.  
🔄 **Commandes `fg` et `bg`** pour relancer les processus suspendus ou en tâche de fond.

---

## Structure du projet

- `main.c` : point d’entrée du shell.
- `parser.c` : analyse des commandes (arguments, redirections, pipes).
- `executor.c` : exécution des commandes et gestion des processus.
- `signals.c` : gestion des signaux (SIGINT, SIGTSTP).
- `history.c` : gestion de l’historique des commandes.
- `utils.c` : fonctions utilitaires (affichage d’erreur, etc.).
- `Makefile` : compilation du projet.

---

## Compilation et exécution

```bash
make
./mysh
