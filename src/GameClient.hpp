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


class GameClient {
private:
  sf::RenderWindow _window;
  bool _wantsToPlay;
  sf::Sprite _sprBG;
  Joueur _joueur;
  Client _client;

  void runError();
  void runWinner();
  void runWaitingRoom();
  void runBoards();
  void drawSpritesGrid(float,float);
  void drawSpritesHits(float,float);
public:
  GameClient(const sf::Texture&);
  ~GameClient();
  void run();
  bool getWantsToPlay();
  void setWindowPosition(int nb); // eric pour debug
};

#endif
