solution provisiore pour d�ploiement 
(source: [deploying-qt-applications-on-linux-and-windows](https://lemirep.wordpress.com/2013/06/01/deploying-qt-applications-on-linux-and-windows-3/))

#	Libs et d�pendances Qt 
### pour d�ploiement d'appli Qt sur machines sans Qt install�

ici se trouvent les librairies et d�pendances Qt 
n�cessaires au fonctionnement de l'appli sur des 
machines qui ne r�pertorient pas le framework Qt.

Proc�d�: 

- ex�cuter le projet en "release"
- isoler l'�x�cutable g�n�r� dans un dossier

- sous windows:
> - copier le contenu de *Windowsx64* � la racine de l'�x�cutable isol�
> - appli � lancer avec cet ex�cutable
> + selon les librairies qt utilis�s dans le projet, 
ajouter les .dll depuis "`location_de_qt_sur_machine`/`version5.x`/`compilateur`/bin/"`

- sous linux:
> - de m�me pour *Linux64* 
> - modifier la derni�re ligne du script bash selon l'emplacement de l'ex�cutable
> - rendre ce script ex�cutable ("chmod +x") et lancer l'appli avec
> + selon les librairies qt utilis�s dans le projet, 
ajouter les .so.x depuis "`location_de_qt_sur_machine`/`version5.x`/`compilateur`/lib/"

+ pour conna�tre ce qui est n�cessaire pour faire fonctionner l'appli: 
> renommer le r�pertoire o� Qt est install� et tester l'ex�cutable
