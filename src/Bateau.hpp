#ifndef BATEAU_HPP
#define BATEAU_HPP

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include "Position.hpp"

/*
 * Représente un bateau
 *
 * @param: _etatPos   > Touché(true 1) / intact(false 0) à la position
 * @param: _nom       > nom du bateau
 * @param: _taille    > taille du bateau
 * @param: _direction > haut 1 bas 2 gauche 3 droite 4
 * @param: _coule     > coulé true ou false
 *
 * ASKME: Baptiste FAMCHON
 */


class Bateau {
private:
  std::string _nom;
  std::vector<std::pair<bool,Position>> _etatPos; 
  int _taille;
  int _direction;
  bool _coule;

public:
  Bateau(int);
  void determinerNom(int);
  int getTaille() const;
  std::string getNom() const;
  bool foundInBateau(Position) const;
  void setDir(int);
  void setEtatPos(bool,Position);
  void setCoule(bool);
  void changeBoatPosition(int);
  
  // Flux de sortie au format "<taille>;<direction>;<coule>;<etatPos>\n".
  friend std::ostream & operator<<(std::ostream & os, const Bateau & b );
  
};

#endif
