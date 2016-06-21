/**
 * \file GameClient.hpp
 * \brief Représente l'interface graphique cote client
 * \author FAMCHON Baptite
 * \version 1.0
 * \date 16 juin 2016
 *
 *
 */
#ifndef GAMECLIENT_HPP
#define GAMECLIENT_HPP


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "PacketType.hpp"
#include "Client.hpp"
#include "Position.hpp"
#include "Joueur.hpp"

/*
 * Constantes utiles pour simplifier l'écriture
 * et la lecture du code.
 * Elles ne sont pas toutes utilisées pour le moment.
 *
 * ASKME: Baptiste FAMCHON
 */

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int GRID_WIDTH = 350;
const int GRID_HEIGHT = 350;
const int CELL_SIZE = 35;
const int CELL_WIDTH = GRID_WIDTH / CELL_SIZE;
const int CELL_HEIGHT = GRID_HEIGHT / CELL_SIZE;

const int DIR_HAUT = 1;
const int DIR_BAS = 2;
const int DIR_GAUCHE = 3;
const int DIR_DROITE = 4;

const sf::Color White (255,255,255);
const sf::Color Black (0,0,0);
const sf::Color Gray (150,150,150);
const sf::Color DarkGray (100,100,100);
const sf::Color RedWine (80,28,28);

/*!  \class GameClient
   * \brief Represente l'interface graphique cote client
   *
   */
class GameClient {
private:
  sf::RenderWindow _window; /*!<Fenetre principale>*/
  bool _wantsToPlay; /*!<Le joueur veut continuer à jouer>*/
  sf::Sprite _sprBG; /*!<Le sprite du background>*/
  Client _client; /*!<La liaison au client pour le reseau>*/

  /*!
   *  \brief Fenetre d'erreur
   */
  void runError();

  /*!
   *  \brief Fenetre des resultats
   */
  void runResult();

  /*!
   *  \brief Fenetre des regles
   */
  void runRegles();

  /*!
   *  \brief Fenetre d'attente et placement des bateaux
   */
  void runWaitingRoom();

  /*!
   *  \brief Fenetre de jeu
   */
  void runBoards();

  /*!
   *  \brief Dessiner la flotte du joueur
   *  \param [in] <posx> {Position x de la grille}
   *  \param [in] <posy> {Position y de la grille}
   */
  void drawSpritesGrid(float posx,float posy);

  /*!
   *  \brief Dessiner la grille des coups testes
   *  \param [in] <posx> {Position x de la grille}
   *  \param [in] <posy> {Position y de la grille}
   */
  void drawSpritesHits(float posx,float posy);
public:  
  /*!
   *  \brief Constructeur de GameClient
   *  \param [in] <bg> {Texture du background}
   */
  GameClient(const sf::Texture& bg);

  /*!
   *  \brief Destructeur de GameClient
   *  
   */
  ~GameClient();

  /*!
   *  \brief Lancer l'interface graphique
   *  
   */
  void run();

  /*!
   *  \brief Savoir si le joueur veut rejouer
   *  \return Il veut continuer, ou non...
   */
  bool getWantsToPlay();

  /*!
   *  \brief Positionner la fenetre sur l'ecran.
   *         Le PC d'Eric avait quelques lags pour deplacer les fenetres, 
   *         de base centrees sur l'ecran...
   *  \param [in] <nb> {1 ou 2}
   */
  void setWindowPosition(int nb); // eric pour debug
};

#endif
