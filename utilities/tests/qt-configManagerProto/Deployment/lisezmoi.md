solution provisiore pour déploiement 
(source: [deploying-qt-applications-on-linux-and-windows](https://lemirep.wordpress.com/2013/06/01/deploying-qt-applications-on-linux-and-windows-3/))

#	Libs et dépendances Qt 
### pour déploiement d'appli Qt sur machines sans Qt installé

ici se trouvent les librairies et dépendances Qt 
nécessaires au fonctionnement de l'appli sur des 
machines qui ne répertorient pas le framework Qt.

Procédé: 

- exécuter le projet en "release"
- isoler l'éxécutable généré dans un dossier

- sous windows:
> - copier le contenu de *Windowsx64* à la racine de l'éxécutable isolé
> - appli à lancer avec cet exécutable
> + selon les librairies qt utilisés dans le projet, 
ajouter les .dll depuis "`location_de_qt_sur_machine`/`version5.x`/`compilateur`/bin/"`

- sous linux:
> - de même pour *Linux64* 
> - modifier la dernière ligne du script bash selon l'emplacement de l'exécutable
> - rendre ce script exécutable ("chmod +x") et lancer l'appli avec
> + selon les librairies qt utilisés dans le projet, 
ajouter les .so.x depuis "`location_de_qt_sur_machine`/`version5.x`/`compilateur`/lib/"

+ pour connaître ce qui est nécessaire pour faire fonctionner l'appli: 
> renommer le répertoire où Qt est installé et tester l'exécutable
