# Projet Qt / C++ : << Invasion des aliens >>
## Auteurs : 
- [Romain CROGUENNOC] 
- [Mathias PAITIER]

## Pour compiler le projet :
Sur Clion, il faut tout simplement appuyer sur le bouton Run en haut à droite de l'interface.

## Fonctionnalités
### Fonctionnalités implémentées :
#### Dans le menu
- [x] Sous menu avec les informations du jeu 
- [x] Affichage des 5 meilleurs score
- [x] Entrée du nom du joueur
- [x] Bouton jouer
- [x] Bouton quitter

#### Dans la partie
- [x] Génération aléatoire des aliens
- [x] Déplacement des aliens
- [x] Déplacement du vaisseau
- [x] Tir du vaisseau
- [x] Détection des collisions
- [x] Gestion des vies
- [x] Temps d'attente entre l'apparition des aliens se réduit au fur et à mesure que le score augmente
- [x] Gestion du score
- [x] Gestion du game over (seulement si le joueur est touché, si 3 aliens attaquent la Terre le jeu plante)
- [x] Gestion du retour au menu

### Fonctionnalités non implémentées :
- [ ] Gestion des astéroïdes
- [ ] Gestion des aliens qui tirent
- [ ] Gestion du score en fonction de l'alien
- [ ] Gestion des PVs des aliens
- [ ] Gestion des bonus

#### Jeu très inspiré par la vidéo suivante :
https://www.youtube.com/watch?v=HuWiPKU1DeM

Les *règles* et les *commandes* sont dans le menu **Informations**.

Il se peut que le dossier "cmake-build-debug" ne fasse pas démarrer le jeu, il est donc conseillé de le supprimer et de le regénérer avec CMake.