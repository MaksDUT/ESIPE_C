# TP6 Backtracking (Resolver Sudoku) 
 Le TP a pour but de découvrir le principe de backtracking et de concevoir un resolver de sudoku en C.
 
 Il fait partie d'une suite de TP (fil rouge) réalisé pendant mon cursus en premiere année à l'ESIPE en programmation C.
 Pour plus d'information sur le TP, on peut le retrouver [ici](http://igm.univ-mlv.fr/~borie/esipe/tp6.pdf).

### Pour Commencer

On retrouve dans ce TP deux éxécutable.

*   le premier éxécutable : ***Exercice2*** 
*   le deuxième éxécutable : ***sudoku*** 

#### Exercice2
Il est le fichier qui correspond à l'exercice 2 du TP.

  
#### Sudoku
Le programme final du TP Backtracking.


## Commande d'éxécution
 dans le TP6 il y a deux Makefile. Un à la racine du dossier du TP, l'autre dans le sous dossier sudoku (TP6/sudoku).

Pour l'instalation de ***Exercice2***  
###### En étant dans le dossier TP6 :
```Bash
    /TP6 make
    /TP6 ./Exercice2
```

Pour l'instalation de ***sudoku*** 
l'executable sudoku prends en argument un fichier .txt representant une grille de sudoku. 
Ici l'argument test permet de lancer le programme avec la grille1.txt. 
Plusieurs grilles sont disponible dans le dossier data (TP7/sudoku/data).

###### En étant dans le dossier sudoku :

exemple d'utilisation avec un fichier
```Bash
    /TP6/sudoku make
    /TP6/sudoku ./sudoku data/grille1.txt
```

plusieurs commande dans le Makefile ont été rajouté pour lancer directement l'éxécutable.

#####Commandes Makefile

`make run_1:` Compile et lance le programme avec le fichier grille1.txt. 

Il existe 5 fichiers dans le dossier data (TP6/sudoku/data) chaque grille dispose de sa commande run_ suivi de son numero (*exemple:* grille2.txt --->`make run_2`) 

aux totals 
`run_1` `run_2` `run_3` `run_4` `run_5`


