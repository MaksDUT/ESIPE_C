# TP7 Sudoku graphique 
 Le TP a pour but de concevoir un sudoku graphique en C avec la librairie MLV.

 Il fait partie d'une suite de TP (fil rouge) réalisé pendant mon cursus en premiere année à l'ESIPE en programmation C.
 Pour plus d'information sur le TP, on peut le retrouver [ici](http://igm.univ-mlv.fr/~borie/esipe/tp7.pdf).

### Pour Commencer

On retrouve dans ce TP deux éxécutable.

*   le premier éxécutable : ***test*** 
*   le deuxième éxécutable : ***sudoku*** 

#### Test
Le premier test que j'ai effectué sur la librairie MLV. On peut y retrouver :
* fonction d'affichage de la grille de sudoku
* fonction d'affichage de chaque coordonné des cases de la grille
* fonction de recherche à partir des coordonnées de la souris, la case selectionné. 
  
#### Sudoku
Le programme final du TP Sudoku. le programme permet :
* de charger une grille de sudoku choisi au lancement du programme (en argument).
* de pouvoir remplir cette grille depuis l'interface graphique (joue entièrement à la souris).  
* Affichage d'erreur de valeur dans la case sélectionné.
* Addaptation de la grille de jeu à l'ecran de l'utilisateur.


## Commande d'éxécution
 dans le TP7 il y a deux Makefile. Un à la racine du dossier du TP, l'autre dans le sous dossier sudoku (TP7/sudoku).

Pour l'instalation de ***test***  
###### En étant dans le dossier TP7 :
```Bash
    /TP7 make
    /TP7 ./test
```

Pour l'instalation de ***sudoku*** 

###### En étant dans le dossier sudoku :
```Bash
    /TP7/sudoku make
    /TP7/sudoku ./sudoku test
```
l'executable sudoku prends en argument un fichier .txt representant une grille de sudoku. 
Ici l'argument test permet de lancer le programme avec la grille1.txt. 
Plusieurs grilles sont disponible dans le dossier data (TP7/sudoku/data).

exemple d'utilisation avec un fichier
```Bash
    /TP7/sudoku make
    /TP7/sudoku ./sudoku data/grille1.txt
```


