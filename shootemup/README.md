# Shoot'em up
 Le projet a pour but de concevoir un shoot'em up graphique en C avec la librairie MLV.
 
 Pour plus d'information sur le Projet, on peut le retrouver [ici](http://igm.univ-mlv.fr/~borie/esipe/shootemup.pdf).

### Pour Commencer

On retrouve dans ce TP un éxécutable : ***shoot*** 

#### shoot
Le programme final du projet Shoot'em up :



## Commande d'éxécution
Il existe un makefile dans le dossier src.

Pour l'instalation de ***shoot***  
###### En étant dans le dossier src :
```Bash
    shootemup/src make
    shootemup/src ./shoot
```

Il faut savoir qu'il est possible de modifier le jeu avec un fichier ***Ennemis.txt*** qui decrit les ennemis dans le jeu
ansi que ***weapon.txt*** qui decrit les weapon.

exemple pour Ennemis
```txt
  name pv center_x center_y width lenght speed color 
  robot 1    1       1        50    30     2   MLV_COLOR_PINK basic
```

exemple pour weapon
```txt
  name width lenght speed degat reload
  basic   7     7     20    1     150
```

Pour modifier la boucle du jeu et d'autre variable il faut aller dans le fichier ***shootemup.h*** 
qui dispose de variable globale permetant de modifier le jeu.
a chaque modification dans le fichier ***shootemup.h*** il faut relancer le makefile.

