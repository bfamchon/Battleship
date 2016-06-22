# Battleship

/////////////////////////////////
//        LIVRABLE 1.00        //
/////////////////////////////////

Jeu de bataille navale en r�seau avec c++ & sfml 

Les commentaires de headers donnent des explications sur les param�tres utilis�s.
Les commentaires de sources sur les fonctions. 


Le jeu est compos� de deux programmes : 
BattleShipSrv.out le serveur en mode console.
BattleShip.out, le client en mode graphique

Le client est compos� de trois �crans :
Ecran de menu : pour se connecter au serveur en sp�cifiant le Pseudo et l'ip du serveur
Ecran d'attente : pour positionner les navires avec un radis pour valider et rentrer dans le jeu.
Ecran de jeu : pour jouer les coups en tour � tour

Plus �cran de r�gles, gagn�, perdu, erreur (Pseudo invalide)

Commandes utilisables pour l'installation :
make clean
make
make doc    //g�n�re la documentation doxygen et latex dans le r�pertoire ./Annexes/ 

I- DEMARRER LE JEU

Ouvrir  un terminal 

Lancer le serveur par la commande  ./bin/BattleshipSrv.out
Si le port 5500 n'est pas utilisable sur votre machine passez votre port en param�tre
Exemple ./bin/BattleshipSrv.out 55001

Sur 2 autre machines (ou le tout sur la m�me) lancer les clients BattleShip.out

Entrez les identifiants Pseudo et Adresse IP et Port (si besoin) du serveur 

Cliquer sur � connect �

Choisir ses bateaux de mani�re al�atoire, les tourner en double cliquant dessus,
ou en les bougeant.

Cliquez sur le radis pour valider votre jeu

Attendre votre adversaire

A la connexion de l'adversaire la partie commence et le serveur d�termine qui joue

Quitter la partie fait gagner l'adversaire et vous d�connecte

Le dernier navire de l'adversaire coul� vous fait gagner 

II- TERMINER LE JEU

Cliquer sur la croix puis sur  �quitter � pour se d�connecter ou la croix
