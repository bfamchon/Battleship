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
void Joueur::setHitAt(int etat, int x, int y) { _testedHits[y*10+x] = etat;}

void Joueur::setFlotteAt(int etat,int x,int y)
{
  int boatNum = _flotte.searchBoatAt(Position{x,y});
  // Le bateau est touché
  if ( etat == 2 )
    {
      _flotte.setBoatHitAt(Position{x,y},boatNum);
      return;
    }
  // Le serveur envoie 2 ( touché )  ou 3 ( coulé )...
  _flotte.setBoatSink(boatNum);
  
}


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

int Joueur::searchInFlotte(Position p)
{
  if (_flotte.foundInFlotte(p))
    {
      int boatNum = _flotte.searchBoatAt(p);
      
      // Le bateau est touché à la case p
      _flotte.setBoatHitAt(p,boatNum);
      if ( _flotte.allTouched(boatNum) )
	{
	  _flotte.setBoatSink(boatNum);
	  if ( _flotte.allBoatSink() )
	    return ALL_BOAT_SINK;
	  return BOAT_SINK;
	}
      return HIT_CELL;
    }
  return MISS_CELL;
}


// Tourner le bateau boatNum dans une direction valide
void Joueur::turnBoat(int boatNum) { _flotte.turnBoatVPos(boatNum); }
