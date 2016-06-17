#ifndef JEU_HPP
#define JEU_HPP

#include "Joueur.hpp"
#include "Flotte.hpp"

class Jeu {
private:
  Joueur _joueur1;
  Joueur _joueur2;
  Joueur* _jCourant;
  Joueur* _jInactif;
  int _nbPret;
public:
  Jeu();
  ~Jeu();
  void changeJoueur();

  void setNbPret(int nb);
  int getNbPret() const;

  Joueur getJoueur1() const;
  Joueur getJoueur2() const;
  Joueur* getJCourant() const;
  Joueur* getJInactif() const;
  std::string getListeJoueur() const;
  void initJoueur(std::string nomJoueur);
  Joueur* searchByName(const std::string & nomJoueur);
  void setSocketJoueur(sf::TcpSocket * socketJoueur,Joueur * joueur);
  int searchInPlayerFlotte(Position position, Joueur * joueur ) const;
  
};


#endif
