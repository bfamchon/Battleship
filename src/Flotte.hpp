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
  int estValide(Position p,int taille,int oldDir);
  bool estValideHaut(Position p,int taille);
  bool estValideBas(Position p,int taille,int brdSize);
  bool estValideGauche(Position p,int taille);
  bool estValideDroite(Position p,int taille,int brdSize);
  bool foundInFlotte(Position p) const;
  int searchBoatAt(Position p) const;
  void turnBoatVPos(int boatNum);
  void setBoatHitAt(Position p,int boatNum);
  bool allTouched(int boatNum) const;
  void setBoatSink(int boatNum);
  bool allBoatSink() const;
  int getBoatSizeAt(int boatNum)const;
  Bateau getBoatAt(int boatNum)const;
  void mooveBoatVPos(int boatNum,Position p);

  friend std::ostream & operator<<(std::ostream & os, const Flotte &);
  friend std::istream & operator>>(std::istream & is, Flotte &);
};

bool operator==(const Flotte & f1,const Flotte & f2);
#endif
