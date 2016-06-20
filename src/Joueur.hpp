#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include "SFML/Network.hpp"
#include <string>
#include <vector>
#include "Flotte.hpp"

const int SEA_CELL = 0;
const int MISS_CELL = 1;
const int HIT_CELL = 2;
const int BOAT_SINK = 3;
const int ALL_BOAT_SINK = 4;

/*
 * @param: _testedHits 100 cases en 1 ligne : 0 sea / 1 miss / 2 hit / 3 sink
 * 
 */

class Joueur {
private:
  std::string _pseudo;
  Flotte _flotte;
  std::vector <int> _testedHits;
  sf::TcpSocket * _socketJoueur;
public:
  Joueur(std::string pseudo);
  void initTestedHits(int etatCoup);
  std::string getPseudo() const;
  void setPseudo(std::string pseudo);
  Flotte getFlotte() const;
  void setFlotte(const Flotte & f);
  void setRandFlotte();
  int getHitAt(int x,int y) const;
  void setHitAt(int etat,int x,int y);
  sf::TcpSocket * getSocketJoueur();
  void setSocketJoueur(sf::TcpSocket * socketJoueur);
  void setFlotteAt(int etat,int x,int y);
  void mooveBoat(int boatNum,Position p);
  int searchInFlotte(Position p);
  void turnBoat(int boatNum);
};

#endif
