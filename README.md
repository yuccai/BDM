#BDM
====

##Sujet
-------
Création d'un moteur de recherche d'images à partir d'une image. La recherche se spécifie selon les descripteurs.

##Descripteurs
--------------

* histogramme
* filtre moyenneur -> Fourier -> coupe-> reconstitution -> filtre de Sobel -> boîte englobante -> points d'intérêts
* filtre moyenneur -> Fourier -> coupe-> reconstitution -> filtre de Sobel -> transformée de Hough

##Utilisation du logiciel
-------------------------
###Compilation
* tar -xvzf fftw-3.3.4.tar.gz
* cd src/lib/fftw3-3.4/
* ./configure
* sudo make install
* sudo make
* cd ../../
* make

###Interface
-----------
Au lancement de l'interface, le dossier /src/img est chargé. On voit apparaître le nom des images chargées dans le dock à gauche. Le bouton `Ajouter un ficher` en haut rajoute les mêmes
images, il faut décommenter une partie du code pour charger les images manuellement mais le dossier /src/img ne sera plus chargé au démarrage. On peut ajouter manuellement les images  en
les plaçant dans le dossier /src/img et relancer l'application.

Au centre de l'application se situent trois onglets :
   1. Le premier permet de visualiser l'image originale mais redimensionnée avec une hauteur de 400 pixels tout en conservant le ratio. Cela permet de ne pas avoir trop de calculs pour
        les images trop grandes
   2. Le second sert à visualiser les composantes LUV de l'image et la somme de ces composantes en base 354 (max des amplitudes des composantes LUV)
   3. Le troisième permet d'effectuer des transformations sur l'image selectionnée en niveau de gris :
    * *Filtre moyen*          : applique un filtre moyen sur l'image de taille 3x3
    * *Fourier*               : applique la transformée de Fourier sur l'image avec l'utilisation de FFTW3
    * *Fourier restreint*     : effectue un filtre passe bas sur l'image
    * *Fourier inverse*       : applique la transformée de Fourier sur l'image avec l'utilisation de FFTW3 (ne pas utiliser cette fonction sans avoir appliquée la transformée
           dans l'autre sens au préalable)
    * *Filtre de Sobel*       : applique un filtre de Sobel de taille 3x3 sur l'image
    * *Points d'intérêts*     : détecte les points d'intérêts de l'image grâce au détecteur de Harris en dimensions 3x3
    * *Seuillage*             : transforme l'image en niveau de gris en une image binaire; les pixels ayant une intensité entre les paramètres seront blancs, les autres seront
            noirs
    * *Transformée de Hough*  : trouve et affiche les droites sur l'image parmis les pixels blancs selon un triplet de paramètres, le mieux étant d'avoir effectué un filtre de
            Sobel et un seuillage au préalable
    * *Erosion-Dilatation*    : dilate et érode l'image avec un cercle de rayon paramétrisable
    * *Négatif*               : les pixels noirs deviennent blancs, les autres deviennent noirs, cet outil couplé à l'érosion et dilatation permet d'effectuer des ouvertures et
            fermetures
    * *Reset*                 : réinitialise l'image initiale en niveau de gris

Il est possible d'effectuer une recherche grâce au bouton `Nouvelle Recherche`. Une fenêtre s'ouvre dans laquelle un bouton `Sélection fichier` permet de choisir une image qui sera
l'image recherchée.


##Similarité
------------
La similarité s'effectue uniquement grâce aux informations colorimétriques.

Dans un premier temps, on détecte les pics croissants de l'histogramme des composantes LUV dans la base 354. La même opération est effectuée sur les autres images. Puis on parcours
les images en comparant les valeurs des pics. Si un des pics coïncide, le chemin de l'image est affiché dans la console. Cette méthode n'est pas la plus optimale mais toutes les
images ayant une zone de couleur commune seront associées.

##Indexation
------------
Aucune indexation spécifique n'a été utilisée, les images sont stockées dans la mémoire du programme sous forme de liste.

