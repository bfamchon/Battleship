#ifndef FLOTTE_HPP
#define FLOTTE_HPP

#include "Bateau.hpp"
#include <vector>
#include <iostream>
#include <sstream>

/**
 * \file Client.hpp
 * \brief Représente l'ensemble des bateaux
 * \author FAMCHON Baptite
 * \version Final
 * \date 16 juin 2016
 *
 * Représente l'ensemble des bateaux
 *
 */

/*! \class Flotte
   * \brief Représente l'ensemble des bateaux
   *
   *  La classe gere les connexion avec le serveur
   */
class Flotte {
private:
  std::vector<Bateau> _bateaux; /*!<Représente la flotte>*/
  int _nbBateaux; /*!<Un certain nombre de bateaux, ici 6>*/

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
