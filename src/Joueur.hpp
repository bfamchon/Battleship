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
  Joueur(std::string);
  void initTestedHits(int);
  std::string getPseudo() const;
  void setPseudo(std::string);
  Flotte getFlotte() const;
  void setFlotte(const Flotte &);
  void setRandFlotte();
  int getHitAt(int,int) const;
  void setHitAt(int,int,int);
  sf::TcpSocket * getSocketJoueur();
  void setSocketJoueur(sf::TcpSocket * socketJoueur);
  void setFlotteAt(int,int,int);
  void mooveBoat(int,Position);
  //eric
  int searchInFlotte(Position);
  void turnBoat(int);
};

#endif
