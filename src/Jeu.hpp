#ifndef JEU_HPP
#define JEU_HPP

#include "Joueur.hpp"
#include "Flotte.hpp"

class Jeu {
private:
  Joueur _joueur1;
  Joueur _joueur2;
  Joueur* _jCourant;
  Flotte _flotteJ1;
  Flotte _flotteJ2;
  
};

#endif
