# TP de Synthèse - ENSEA in the Shell

## Auteurs

* Alexian PREVOST
* Iprahim TURGUT

## Groupes
* 2G2-TD1-TP2
---

## Table des matières

1. [Contexte du projet](#contexte-du-projet)
2. [Fonctionnalités implémentées](#fonctionnalit%C3%A9s-impl%C3%A9ment%C3%A9es)
3. [Question 1 – Message d’accueil et prompt](#question-1--message-daccueil-et-prompt)
4. [Question 2 – Exécution de commandes simples](#question-2--ex%C3%A9cution-de-commandes-simples)
5. [Question 3 – Gestion de la sortie du shell](#question-3--gestion-de-la-sortie-du-shell)
6. [Question 4 – Affichage du code de retour ou du signal](#question-4--affichage-du-code-de-retour-ou-du-signal)
7. [Question 5 – Mesure du temps d’exécution](#question-5--mesure-du-temps-dex%C3%A9cution)
8. [Question 6 – Commandes avec arguments](#question-6--commandes-avec-arguments)
9. [Question 7 – Redirections d’entrée et sortie](#question-7--redirections-dentr%C3%A9e-et-sortie)
10. [Difficultés rencontrées](#difficult%C3%A9s-rencontr%C3%A9es)
11. [Conclusion](#conclusion)

---

## Contexte du projet

Ce projet a été réalisé dans le cadre du **TP de Synthèse, Ensea in the Shell**, durant les séances 1 et 2 (8 heures).
L’objectif principal est de développer un **micro-shell** (`enseash`) capable d’exécuter des commandes UNIX tout en affichant :

* le **code de retour** ou le **signal** de terminaison de chaque programme exécuté,
* le **temps d’exécution** de chaque commande.

Le projet est développé en **C** en respectant les contraintes suivantes :

* Interdiction d’utiliser `system()` ou `printf()`,
* Lecture des commandes via `read()`, affichage avec `write()`,
* Manipulation des chaînes de caractères avec les fonctions `strn*` pour éviter les dépassements de mémoire,
* Code structuré et commenté en anglais pour les fonctions,
* Utilisation de constantes nommées (pas de nombres magiques).

Ce micro-shell permet de se familiariser avec la création de **processus**, la gestion des **signaux**, la mesure de **temps d’exécution**, et la manipulation des **redirections d’entrée et sortie**.

---

## Fonctionnalités implémentées

Les fonctionnalités suivantes ont été implémentées **jusqu’à la question 7** :

* Q1 : Message d’accueil et prompt
* Q2 : Exécution de commandes simples
* Q3 : Sortie du shell (`exit` et Ctrl+D)
* Q4 : Affichage du code de retour / signal dans le prompt
* Q5 : Mesure du temps d’exécution (millisecondes)
* Q6 : Exécution de commandes avec arguments
* Q7 : Redirections d’entrée (`<`) et sortie (`>`)

---

## Question 1 – Message d’accueil et prompt

### Objectif

Afficher un message d’accueil au lancement du shell et un prompt simple pour chaque commande.

### Fichiers impliqués

* `question1.c`

### Détails d’implémentation

* `welcomePrompt()` affiche le message d’accueil via `write()` :

```c
#define WELCOME_MESSAGE "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\n"
write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
```

* `regularPrompt()` affiche le prompt :

```c
#define PROMPT_MESSAGE "enseash % "
write(STDOUT_FILENO, PROMPT_MESSAGE, strlen(PROMPT_MESSAGE));
```

* En cas d’erreur d’écriture, `regularPrompt()` appelle `exit(EXIT_FAILURE)`.

### Remarques

L’utilisation de `write()` garantit un comportement cohérent avec les lectures faites par `read()` et évite les problèmes de buffering liés à `printf()`.

---

## Question 2 – Exécution de commandes simples

### Objectif

Lire et exécuter des commandes simples (sans arguments) dans une boucle **Read–Eval–Print Loop**.

### Fichiers impliqués

* `question2.c`
* `question3.c` (pour la gestion de `exit`)
* `question5.c` (pour la mesure du temps)

### Détails d’implémentation

* Lecture de la ligne de commande :

  * `read(STDIN_FILENO, bufferCommandeLine, MAX_LINE_SIZE)` lit la saisie.
  * Si `read()` retourne `0`, `exitShell()` est appelé.
  * Si la chaîne lue est vide (retour chariot seul), la commande est ignorée et le prompt est réaffiché.

* Détection de la commande `exit` via `exitCommandCheck()` qui compare la chaîne lue avec la constante `EXIT`.

* Exécution :

  * `StartTime()` est appelée pour récupérer l’instant de départ.
  * Le processus fils est créé avec `fork()`.
  * Dans le fils : `execlp(bufferCommandeLine, bufferCommandeLine, NULL);` pour exécuter la commande simple.
  * Dans le père : `wait(&status)` récupère le statut de retour.
  * `StopTime(start)` calcule la durée d’exécution, stockée via `GetLastExecutionTime()`.

### Extrait clé

```c
if (fork() == 0){
    execlp(bufferCommandeLine, bufferCommandeLine ,NULL);
    exit(EXIT_FAILURE);
}
wait(&status);
```

### Remarques

La gestion actuelle des erreurs dans l’exécution est basique : si `execlp` échoue, le fils termine avec `EXIT_FAILURE`.

---

## Question 3 – Gestion de la sortie du shell

### Objectif

Permettre de quitter le shell via la commande `exit` ou `<Ctrl> + D`.

### Fichiers impliqués

* `question3.c`

### Détails d’implémentation

* `exitCommandCheck(const char *cmd)` retourne vrai si `strcmp(cmd, EXIT) == 0`.
* `exitShell()` affiche le message de sortie et termine proprement le programme :

```c
write(STDOUT_FILENO, EXIT_BYEBYE, strlen(EXIT_BYEBYE));
exit(EXIT_SUCCESS);
```


---

## Question 4 – Affichage du code de retour ou du signal

### Objectif

Afficher dans le prompt le **code de retour** (`exit`) ou le **signal** (`sign`) du programme précédent, ainsi que le temps d’exécution.

### Fichiers impliqués

* `question4.c`
* `question5.c` (pour le temps)

### Détails d’implémentation

* `augmentedPrompt(int status, long time_ms)` construit le prompt enrichi :

```c
char buffer[64] = {0};
sprintf(buffer, "enseash [%s:%d|%ldms] %%%:", WIFEXITED(status) ? EXIT : SIGNAL,
        WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status), time_ms);
write(STDOUT_FILENO, buffer, strlen(buffer));
```

* Les macros POSIX `WIFEXITED`, `WEXITSTATUS`, `WIFSIGNALED`, `WTERMSIG` sont utilisées pour interpréter `status` retourné par `wait()`.

### Affichage

```sh
enseash % ls
enseash [exit:0|1ms] %:
```

---

## Question 5 – Mesure du temps d’exécution

### Objectif

Mesurer la durée d’exécution de chaque commande en millisecondes.

### Fichiers impliqués

* `question5.c`

### Détails d’implémentation

* `StartTime()` retourne un `struct timespec` initialisé via `clock_gettime(CLOCK_MONOTONIC, &start)`.
* `StopTime(start)` récupère le temps courant et calcule la différence en millisecondes :

```c
last_execution_time_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_nsec - start.tv_nsec)/1000000;
```

* `GetLastExecutionTime()` retourne `last_execution_time_ms`.

### Remarques

L’utilisation de `CLOCK_MONOTONIC` évite les problèmes liés aux sauts d’horloge système.

---

## Question 6 – Commandes avec arguments

### Objectif

Permettre l’exécution de commandes contenant des arguments (par ex. `ls -l`, `hostname -i`).

### Fichiers impliqués

* `question6.c`
* `question2.c`, `question5.c`, `question3.c` (appels inter-dépendants)

### Détails d’implémentation

* La chaîne de commande est découpée en tokens en utilisant `strtok(bufferCommandeLine, " ")`.
* Les tokens sont stockés dans `argv[]` (taille maximale définie par `MAX_ARGS`).
* `execvp(argv[0], argv)` est utilisé pour exécuter la commande avec ses arguments.
* Le père attend la fin du fils (`wait(&status)`) et on mesure le temps avec `StartTime()` / `StopTime()`.

### Extrait clé

```c
int ArgCounter = 0;
char *token = strtok(bufferCommandeLine," ");
while (token != NULL) {
    argv[ArgCounter++] = token;
    token = strtok(NULL," ");
}
argv[ArgCounter] = NULL;

if (fork() == 0) {
    execvp(argv[0], argv);
    exit(EXIT_FAILURE);
}
wait(&status);
```
### Affichage

```
enseash % hostname -i
127.0.0.1
```


---

## Question 7 – Redirections d’entrée et sortie

### Objectif

Gérer les redirections des flux standards : entrée (`<`) et sortie (`>`).

### Fichiers impliqués

* `question7.c`
* `question5.c`, `question3.c`

### Détails d’implémentation

* La ligne de commande est analysée avec `strtok(..., " \t")` pour gérer séparateurs espace et tabulation.
* Lorsqu’un token `"<"` ou `">"` est détecté, le token suivant est considéré comme nom de fichier d’entrée ou de sortie.
* Avant `execvp()` dans le processus fils, les redirections sont appliquées :

```c
if (InputFile != NULL) {
    int fd_in = open(InputFile, O_RDONLY);
    if (fd_in < 0) _exit(EXIT_FAILURE);
    dup2(fd_in, STDIN_FILENO);
    close(fd_in);
}
if (OutputFile != NULL) {
    int fd_out = open(OutputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) _exit(EXIT_FAILURE);
    dup2(fd_out, STDOUT_FILENO);
    close(fd_out);
}
execvp(argv[0], argv);
```

* Le père attend la fin du fils et `StopTime(start)` est appelé pour calculer le temps d’exécution.

### Affichage

```sh
enseash % ls > filelist.txt
enseash [exit:0|1ms] %
```

```sh
enseash % wc -l < filelist.txt
7
enseash [exit:0|12ms] %
```

---

## Difficultés rencontrées

* Analyse correcte et découpage sécurisé de la ligne de commande (gestion des séparateurs et tokens).
* Gestion propre des descripteurs de fichiers lors des redirections `<` et `>` (ouverture, `dup2`, fermeture).
* Synchronisation entre processus père et fils pour la récupération des statuts et la mesure du temps.
* Respect strict des contraintes (pas de `printf`, pas de `system()`, utilisation de `read`/`write`).

---

## Conclusion

Le micro-shell `enseash` fonctionne correctement pour toutes les commandes simples, les commandes avec arguments, ainsi que les redirections d’entrée et sortie. Le code est structuré de manière claire et permet d’observer les codes de retour et les temps d’exécution pour chaque commande.

Le projet a permis de se familiariser avec la gestion de processus, la redirection des flux et la mesure précise du temps d’exécution en C.

