#include "Joueur.hpp"
#include <iostream>
#include <sstream>

Joueur::Joueur(std::string pseudo) : _pseudo(pseudo),_flotte(),_socketJoueur(nullptr)
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

void Joueur::setFlotte(const Flotte & f)
{
  // Au cas où elle contenait déjà des valeurs...
  _flotte.initFlotte();
  std::ostringstream oss;
  oss << f;
  std::istringstream iss(oss.str());
  iss >> _flotte;
}

sf::TcpSocket * Joueur::getSocketJoueur(){
  return _socketJoueur;
}
void Joueur::setSocketJoueur(sf::TcpSocket * socketJoueur){
  _socketJoueur = socketJoueur;
}

/////////////////
//jouer coup eric

bool Joueur::foundInFlotte(Position position) const{
  return _flotte.foundInFlotte(position);
}


// Tourner le bateau boatNum dans une direction valide
void Joueur::turnBoat(int boatNum) { _flotte.turnBoatVPos(boatNum); }

