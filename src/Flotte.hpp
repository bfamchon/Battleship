#ifndef FLOTTE_HPP
#define FLOTTE_HPP

#include "Bateau.hpp"
#include <vector>
#include <iostream>
#include <sstream>
/*
 * Représente l'ensemble des bateaux
 *
 * ASKME: Baptiste FAMCHON
 */


class Flotte {
private:
  std::vector<Bateau> _bateaux;
  int _nbBateaux;

public:
  Flotte();
  void initFlotte();
  void genererFlotte();
  int estValide(Position,int,int);
  bool estValideHaut(Position,int);
  bool estValideBas(Position,int,int);
  bool estValideGauche(Position,int);
  bool estValideDroite(Position,int,int);
  bool foundInFlotte(Position) const;
  int searchBoatAt(Position) const;
  void turnBoatVPos(int);
  void setBoatHitAt(Position,int);
  bool allTouched(int) const;
  void setBoatSink(int);
  bool allBoatSink() const;
  int getBoatSizeAt(int)const;
  friend std::ostream & operator<<(std::ostream & os, const Flotte &);
  friend std::istream & operator>>(std::istream & is, Flotte &);
};

bool operator==(const Flotte & f1,const Flotte & f2);
#endif
