#ifndef JEU_HPP
#define JEU_HPP

#include "Joueur.hpp"
#include "Flotte.hpp"
/*! \class Jeu
   * \brief classe Jeu sur le serveur
   *  La classe gere le jeu et fait respecter les regles à tous les joueurs
   */
class Jeu {
private:

  Joueur _joueur1; /*!<Joueur1 */
  Joueur _joueur2; /*!<Joueur2 */
  Joueur* _jCourant; /*!<Pointeur sur le Joueur Actif/Courant */
  Joueur* _jInactif; /*!<Pointeur sur le Joueur Inactif */
  int _nbPret; /*!<Flag pour gerer les connexions */
public:
/*!
     *  \brief Constructeur
     *  Constructeur de la classe Jeu
     */
  Jeu();
  /*!
     *  \brief Destructeur
     *  Constructeur de la classe Jeu
     */
  ~Jeu();
  
  /*!
     *  \brief change le joueur actif
     */
  void changeJoueur();

   /*!
     *  \brief Setter _nbPret
     *  \param [in] <nb> {Nombre de joueurs pret a jouer}
     */
  void setNbPret(int nb);
   /*!
     *  \brief Getter _nbPret
     *  \return Nombre de joueurs pret a jouer
     */
  int getNbPret() const;
   /*!
     *  \brief Getter _joueur1
     *  \return _joueur1
     */
  Joueur getJoueur1() const;
     /*!
     *  \brief Getter _joueur2
     *  \return _joueur2
     */
  Joueur getJoueur2() const;
  /*!
     *  \brief Getter _jCourant
     *  \return pointeur sur _jCourant
     */
  Joueur* getJCourant() const;
    /*!
     *  \brief Getter _jInactif
     *  \return pointeur sur _jInactif
     */
  Joueur* getJInactif() const;
    /*!
     *  \brief Getter _listeJoueurs
     *  \return la liste des joueurs connectes en attente de jouer
     */
  std::string getListeJoueur() const;
  /*!
     *  \brief Initialisation du joueur après deconnection
     *  \param [in] <nomJoueur> {pseudo du joueur}
     */
  void initJoueur(std::string nomJoueur);
  /*!
     *  \brief recherche le joueur d'apres son pseudo
     *  \param [in] <nomJoueur> {pseudo du joueur}
     *  \return un pointeur sur le joueur
     */
  Joueur* searchByName(const std::string & nomJoueur);
  /*!
     *  \brief Initialisation du socket pour le joueur
     *  \param [in] <socketJoueur> {pointeur sur le socket du joueur}
     *  \param [in] <Joueur> {pointeur sur un Joueur}
     */
  void setSocketJoueur(sf::TcpSocket * socketJoueur,Joueur * joueur);
  /*!
     *  \brief recherche dans la flotte du joueur les position des navires
     *  \param [in] <position> {position du tir}
     *  \param [in] <joueur> {pointeur sur le joueur}
     *  \param [in] <posNavire> {pointeur sur un vecteur de position du navire}
     *  \return resultat du tir (1 a l'eau, 2 touche, 3 coule, 4 gagne)
     */
  int searchInPlayerFlotte(Position position, Joueur * joueur,std::vector<int>* posNavire );
  
};


#endif
