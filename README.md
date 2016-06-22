# Battleship

/////////////////////////////////
//        LIVRABLE 1.00        //
/////////////////////////////////

Jeu de bataille navale en réseau avec c++ & sfml 

Les commentaires de headers donnent des explications sur les paramètres utilisés.
Les commentaires de sources sur les fonctions. 


Le jeu est composé de deux programmes : 
BattleShipSrv.out le serveur en mode console.
BattleShip.out, le client en mode graphique

Le client est composé de trois écrans :
Ecran de menu : pour se connecter au serveur en spécifiant le Pseudo et l'ip du serveur
Ecran d'attente : pour positionner les navires avec un radis pour valider et rentrer dans le jeu.
Ecran de jeu : pour jouer les coups en tour à tour

Plus écran de règles, gagné, perdu, erreur (Pseudo invalide)

Commandes utilisables pour l'installation :
make clean
make
make doc    //génère la documentation doxygen et latex dans le répertoire ./Annexes/ 

I- DEMARRER LE JEU

Ouvrir  un terminal 

Lancer le serveur par la commande  ./bin/BattleshipSrv.out
Si le port 5500 n'est pas utilisable sur votre machine passez votre port en paramètre
Exemple ./bin/BattleshipSrv.out 55001

Sur 2 autre machines (ou le tout sur la même) lancer les clients BattleShip.out

Entrez les identifiants Pseudo et Adresse IP et Port (si besoin) du serveur 

Cliquer sur « connect »

Choisir ses bateaux de manière aléatoire, les tourner en double cliquant dessus,
ou en les bougeant.

Cliquez sur le radis pour valider votre jeu

Attendre votre adversaire

A la connexion de l'adversaire la partie commence et le serveur détermine qui joue

Quitter la partie fait gagner l'adversaire et vous déconnecte

Le dernier navire de l'adversaire coulé vous fait gagner 

II- TERMINER LE JEU

Cliquer sur la croix puis sur  «quitter » pour se déconnecter ou la croix
