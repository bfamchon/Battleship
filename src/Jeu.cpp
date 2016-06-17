#include "Jeu.hpp"

Jeu::Jeu(): _joueur1("notInit"),_joueur2("notInit"), _nbPret(0){
  _jCourant = &_joueur1;
  _jInactif = &_joueur2;
}

Jeu::~Jeu(){};

void Jeu::changeJoueur() {
  if (_jCourant == &_joueur1){
    _jCourant = &_joueur2;
    _jInactif = &_joueur1;
  }else {
    _jCourant = &_joueur1;
    _jInactif = &_joueur2;
  }
}

void Jeu::setNbPret(int nb){
  _nbPret = nb;
}

int Jeu::getNbPret() const{
  return _nbPret;
}

Joueur Jeu::getJoueur1() const {
  return _joueur1;
}
Joueur Jeu::getJoueur2() const {
  return _joueur2;
}
Joueur* Jeu::getJCourant() const {
  return _jCourant;
}

Joueur* Jeu::getJInactif() const {
  return _jInactif;
}

std::string Jeu::getListeJoueur() const{
  return _joueur1.getPseudo()+"\n"+_joueur2.getPseudo()+"\n";
}

void Jeu::initJoueur(std::string nomJoueur) {
  if (_joueur1.getPseudo() == nomJoueur){
    _joueur1.setPseudo("notInit");
  } else if (_joueur2.getPseudo() == nomJoueur)
    _joueur2.setPseudo("notInit");
}
  
Joueur* Jeu::searchByName(const std::string & nomJoueur){
  if ( _joueur1.getPseudo() == nomJoueur) return &_joueur1;
  if ( _joueur2.getPseudo() == nomJoueur) return &_joueur2;
  return nullptr;
}

void Jeu::setSocketJoueur(sf::TcpSocket * socketJoueur, Joueur * joueur){
  joueur->setSocketJoueur(socketJoueur);
}

int Jeu::searchInPlayerFlotte(Position position, Joueur * joueur,std::vector<int>* posNavire ){
  int stateHit = joueur->searchInFlotte(position);
  if ( stateHit == 3 )
    {
      int boatNum = joueur->getFlotte().searchBoatAt(position);
      int boatSize = joueur->getFlotte().getBoatAt(boatNum).getTaille();
	for ( int i = 0; i < boatSize; ++i )
	  {
	    posNavire->push_back(joueur->getFlotte().getBoatAt(boatNum).getPositionAt(i)._x);
	    posNavire->push_back(joueur->getFlotte().getBoatAt(boatNum).getPositionAt(i)._y);
	  }
    }
  return stateHit;
}
