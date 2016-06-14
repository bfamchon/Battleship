#include "Joueur.hpp"
#include <iostream>

Joueur::Joueur(std::string pseudo) : _pseudo(pseudo),_flotte()
{
  initTestedHits(SEA_CELL);
}

void Joueur::initTestedHits(int etatCoup)
{
  for ( unsigned int i = 0 ; i < 100 ; ++i )
    _testedHits.push_back(etatCoup);
}

std::string Joueur::getPseudo() const { return _pseudo; }
void Joueur::setPseudo(std::string pseudo) { _pseudo = pseudo; }
Flotte Joueur::getFlotte() const { return _flotte; }
void Joueur::setRandFlotte() { _flotte.genererFlotte(); }
int Joueur::getHitAt(int x,int y) const { return _testedHits[y*10+x]; }
void Joueur::setHitAt(int etat, int x, int y) { _testedHits[y*10+x] = etat; }
