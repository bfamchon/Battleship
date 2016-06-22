/**
 * \file Bateau.hpp
 * \brief Represente un bateau
 * \author FAMCHON Baptite
 * \version 1.0
 * \date 16 juin 2016
 *
 * Represente un bateau
 *
 */

#ifndef BATEAU_HPP
#define BATEAU_HPP

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include "Position.hpp"

/*
 * Represente un bateau
 *
 * @param: _etatPos   > Touche(true 1) / intact(false 0) a la position
 * @param: _nom       > nom du bateau
 * @param: _taille    > taille du bateau
 * @param: _direction > haut 1 bas 2 gauche 3 droite 4
 * @param: _coule     > coule true ou false
 *
 * ASKME: Baptiste FAMCHON
 */

/*!  \class Bateau
   * \brief Represente un bateau
   *
   */
class Bateau {
private:
  std::string _nom; /*!<Nom du bateau>*/
  std::vector<std::pair<bool,Position>> _etatPos; /*!<Etat Position pour chaque case du bateau>*/
  int _taille; /*!<Taille du bateau>*/
  int _direction; /*!<Direction du bateau>*/
  bool _coule; /*!<Etat global du bateau, coule ou non>*/

public:
  /*!
   *  \brief Constructeur
   *  Constructeur de la classe Bateau d'une taille donnee
   *  \param [in] <taille> {Taille du bateau}
   */
  Bateau(int taille);

  /*!
   *  \brief Determiner le nom en fonction de la taille
   *  \param [in] <taille> {Taille du bateau}
   */
  void determinerNom(int taille);

  /*!
   *  \brief Accesseur pour la taille du bateau
   *  \return La taille du bateau
   */
  int getTaille() const;

  /*!
   *  \brief Accesseur pour le nom du bateau
   *  \return Le nom du bateau
   */
  std::string getNom() const;

  /*!
   *  \brief Regarder si la position est trouvee dans le bateau
   *  \return Trouvee ou non
   *  \param [in] <p> {Position testee}
   */  
  bool foundInBateau(Position p) const;

  /*!
   *  \brief Donner une direction au bateau
   *  
   *  \param [in] <dir> {Direction donnee}
   */  
  void setDir(int dir);

  /*!
   *  \brief Recuperer la direction du bateau
   *  
   */ 
  int getDir() const;

  /*!
   *  \brief Affecter les etats et positions en fonction de la direction
   *  et de la taille.
   *  \param [in] <etat> {Etat des cases du bateau}
   *  \param [in] <p> {Premiere case du bateau}
   */ 
  void setEtatPos(bool etat,Position p);

  /*!
   *  \brief Donner un etat au bateau
   *  
   *  \param [in] <etatBateau> {Coule ou non coule}
   */  
  void setCoule(bool etatBateau);

  /*!
   *  \brief Recuperer l'etat du bateau
   *  
   *  \return Coule ou non
   */  
  bool getCoule() const;

  /*!
   *  \brief Changer la position du bateau dans une direction donnee
   *  
   *  \param [in] <dir> {Direction voulue}
   */  
  void changeBoatPosition(int dir);

  /*!
   *  \brief Recuperer la position de la case donnee
   *  \return Position de la case
   *  \param [in] <indice> {Indice de la case}
   */  
  Position getPositionAt(int indice) const;

  /*!
   *  \brief Effacer le vecteur etatPos
   * 
   */  
  void reinitEtatPos();

  /*!
   *  \brief Mettre touche, la case de position donnee
   *  
   *  \param [in] <p> {Position de la case touchee}
   */  
  void setHited(Position p);

  /*!
   *  \brief Recuperer l'etat a l'indice demande
   *  \return Touche ou non
   *  \param [in] <indice> {Indice de la case}
   */  
  bool getEtatAt(int indice) const;

  /*!
   *  \brief Flux de sortie au format "<direction>;<coule>;<etat>_<position1X>_<position1Y>;..."
   */  
  friend std::ostream & operator<<(std::ostream & os, const Bateau & b );
};

#endif
