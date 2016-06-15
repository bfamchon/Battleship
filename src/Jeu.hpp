#ifndef JEU_HPP
#define JEU_HPP

#include "Joueur.hpp"
#include "Flotte.hpp"

class Jeu {
private:
  Joueur _joueur1;
  Joueur _joueur2;
  Joueur* _jCourant;
  
public:
  Jeu(): _joueur1("notInit"),_joueur2("notInit"){ _jCourant = &_joueur1; };
  ~Jeu(){};
  void changeJoueur() {
    if (_jCourant == &_joueur1){
      _jCourant = &_joueur2;
    }else _jCourant = &_joueur1;
  }
  Joueur* getJCourant() const {return _jCourant; }
  std::string getListeJoueur() const{
    return _joueur1.getPseudo()+"\n"+_joueur2.getPseudo()+"\n";
  }
 void initJoueur(std::string nomJoueur) {
   if (_joueur1.getPseudo() == nomJoueur){
     _joueur1.setPseudo("notInit");
       } else if (_joueur2.getPseudo() == nomJoueur)
                      _joueur2.setPseudo("notInit");
  }
  
 Joueur* searchByName(const std::string & nomJoueur){
   return nullptr;
   if ( _joueur1.getPseudo() == nomJoueur) return & _joueur1;
   if ( _joueur2.getPseudo() == nomJoueur) return & _joueur2;
  }
};
#endif
