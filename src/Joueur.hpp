/**
 * \file Joueur.hpp
 * \brief Represente un joueur
 * \author FAMCHON Baptite
 * \version 1.0
 * \date 16 juin 2016
 *
 * Represente un joueur
 *
 */

#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include "SFML/Network.hpp"
#include <string>
#include <vector>
#include "Flotte.hpp"

const int SEA_CELL = 0;
const int MISS_CELL = 1;
const int HIT_CELL = 2;
const int BOAT_SINK = 3;
const int ALL_BOAT_SINK = 4;

/*
 * @param: _testedHits 100 cases en 1 ligne : 0 sea / 1 miss / 2 hit / 3 sink
 * 
 */

/*!  \class Joueur
   * \brief Represente un joueur
   *
   */
class Joueur {
private:
  std::string _pseudo;  /*!<Pseudo du joueur>*/
  Flotte _flotte;  /*!<Flotte du joueur>*/
  std::vector <int> _testedHits;  /*!<Coups testes>*/
  sf::TcpSocket * _socketJoueur;  /*!<Pointeur du socket joueur sur le serveur>*/
public:
  /*!
   *  \brief Constructeur
   *  Constructeur de la classe Joueur avec un pseudo donne
   *  \param [in] <pseudo> {Pseudo du joueur}
   */
  Joueur(std::string pseudo);

  /*!
   *  \brief Initialiser les coups testes a un etat donne
   *  
   *  \param [in] <etatCoup> {Etat d'initialisation}
   */  
  void initTestedHits(int etatCoup);

  /*!
   *  \brief Recuperer le pseudo
   *  \return Le pseudo
   *  
   */  
  std::string getPseudo() const;

  /*!
   *  \brief Donner un pseudo au joueur
   *  
   *  \param [in] <pseudo> {Pseudo du joueur}
   */  
  void setPseudo(std::string pseudo);

  /*!
   *  \brief Recuperer la flotte
   *  \return La flotte du joueur
   *  
   */  
  Flotte getFlotte() const;

  /*!
   *  \brief Remplacer la flotte par celle que l'on passe en parametre
   *  
   *  \param [in] <f> {La flotte que l'on veut}
   */  
  void setFlotte(const Flotte & f);

  /*!
   *  \brief Reinitialiser la flotte avec des bateaux aleatoires
   *  
   *  
   */  
  void setRandFlotte();

  /*!
   *  \brief Recuperer le coup teste a l'indice x,y
   *  \return L'etat de la case a la position demandee
   *  \param [in] <x> {Coordonne de la case}
   *  \param [in] <y> {Coordonne de la case}
   */  
  int getHitAt(int x,int y) const;

  /*!
   *  \brief Mettre la case x,y a l'etat voulu
   *  \param [in] <etat> {Etat voulu}
   *  \param [in] <x> {Coordonne de la case}
   *  \param [in] <y> {Coordonne de la case}
   */  
  void setHitAt(int etat,int x,int y);

  /*!
   *  \brief Recuperer le socket du joueur
   *  \return Le socket du joueur
   *  
   */
  sf::TcpSocket * getSocketJoueur();

  /*!
   *  \brief Lier le socket joueur
   *  
   *  \param [in] <socketJoueur> {Le socket auquel on veut le lier}
   */
  void setSocketJoueur(sf::TcpSocket * socketJoueur);

  /*!
   *  \brief Affecter l'etat voulu a la case x y du bateau
   *  \param [in] <etat> {Etat de la case}
   *  \param [in] <x> {Coordonne de la case}
   *  \param [in] <y> {Coordonne de la case}
   */
  void setFlotteAt(int etat,int x,int y);

  /*!
   *  \brief Deplacer le bateau a la position demandee
   *  \param [in] <boatNum> {Numero du bateau}
   *  \param [in] <p> {Position voulue}
   */
  void mooveBoat(int boatNum,Position p);

  /*!
   *  \brief Rechercher le numero bateau a la position p
   *  \return L'indice du bateau
   *  \param [in] <p> {Position du bateau recherchee}
   */
  int searchInFlotte(Position p);

  /*!
   *  \brief Tourner le bateau voulu dans le sens des aiguilles d'une montre
   *  \param [in] <boatNum> {Le numero de bateau}
   */
  void turnBoat(int boatNum);
};

#endif
