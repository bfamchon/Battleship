#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <string>
#include <vector>
#include "Flotte.hpp"

const int SEA_CELL = 0;
const int MISS_CELL = 1;
const int HIT_CELL = 2;

/*
 * @param: _testedHits 100 cases en 1 ligne : 0 sea / 1 miss / 2 hit
 * 
 */

class Joueur {
private:
  std::string _pseudo;
  Flotte _flotte;
  std::vector <int> _testedHits;
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
};

#endif
