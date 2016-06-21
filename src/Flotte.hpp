/**
 * \file Client.hpp
 * \brief Représente l'ensemble des bateaux
 * \author FAMCHON Baptite
 * \version 1.0
 * \date 16 juin 2016
 *
 * Représente l'ensemble des bateaux
 *
 */
#ifndef FLOTTE_HPP
#define FLOTTE_HPP

#include "Bateau.hpp"
#include <vector>
#include <iostream>
#include <sstream>

/*! \class Flotte
   * \brief Représente l'ensemble des bateaux
   *
   */
class Flotte {
private:
  std::vector<Bateau> _bateaux; /*!<Représente la flotte>*/
  int _nbBateaux; /*!<Un certain nombre de bateaux, ici 6>*/

public:
  /*!
   *  \brief Constructeur
   *  Constructeur de la classe Flotte
   */
  Flotte();

  /*!
   *  \brief Initialise la Flotte avec 6 bateaux et leur taille
   *  
   */
  void initFlotte();

  /*!
   *  \brief genere des positions aleatoires pour la flotte
   *  
   */
  void genererFlotte();

  /*!
   *  \brief Trouver une direction valide,
   *         l'ancienne est mémorisée pour ne pas etre reprise
   *  \return La direction valide trouvee
   *  \param [in] <p> {Position testee}
   *  \param [in] <taille> {Taille du bateau}
   *  \param [in] <oldDir> {Ancienne direction}
   */
  int estValide(Position p,int taille,int oldDir);

  /*!
   *  \brief Regarder si la direction est valide vers le haut
   *  \return Valide ou non valide
   *  \param [in] <p> {Position testee}
   *  \param [in] <taille> {Taille du bateau}
   */
  bool estValideHaut(Position p,int taille);

  /*!
   *  \brief Regarder si la direction est valide vers le bas
   *  \return Valide ou non valide
   *  \param [in] <p> {Position testee}
   *  \param [in] <taille> {Taille du bateau}
   *  \param [in] <brdSize> {Taille du plateau}
   */
  bool estValideBas(Position p,int taille,int brdSize);

  /*!
   *  \brief Regarder si la direction est valide vers le gauche
   *  \return Valide ou non valide
   *  \param [in] <p> {Position testee}
   *  \param [in] <taille> {Taille du bateau}
   */
  bool estValideGauche(Position p,int taille);

  /*!
   *  \brief Regarder si la direction est valide vers la droite
   *  \return Valide ou non valide
   *  \param [in] <p> {Position testee}
   *  \param [in] <taille> {Taille du bateau}
   *  \param [in] <brdSize> {Taille du plateau}
   */
  bool estValideDroite(Position p,int taille,int brdSize);

  /*!
   *  \brief Regarder si la position est trouvee dans la flotte
   *  \return Trouvee ou non
   *  \param [in] <p> {Position testee}
   */
  bool foundInFlotte(Position p) const;

  /*!
   *  \brief Trouver le numero de bateau a la position demandee
   *  \return Numero du bateau
   *  \param [in] <p> {Position testee}
   */
  int searchBoatAt(Position p) const;

  /*!
   *  \brief Tourner le bateau dans une position valide
   *         ( sens des aiguilles d'une montre )
   *  \param [in] <boatNum> {Numero de bateau}
   */
  void turnBoatVPos(int boatNum);

  /*!
   *  \brief Mettre le bateau touche a la position donnee
   *  \param [in] <p> {Position donnee}
   *  \param [in] <boatNum> {Numero de bateau}
   */
  void setBoatHitAt(Position p,int boatNum);

  /*!
   *  \brief Regarder si toutes les cases du bateau sont touchees
   *  \return Le bateau est entierement touche ou non
   *  \param [in] <boatNum> {Numero de bateau}
   */
  bool allTouched(int boatNum) const;

  /*!
   *  \brief Mettre le bateau coule
   *  \param [in] <boatNum> {Numero de bateau}
   */
  void setBoatSink(int boatNum);

  /*!
   *  \brief Regarder si tous les bateaux sont coules
   *  \return Tous les bateaux sont coules... Ou non
   */
  bool allBoatSink() const;

  /*!
   *  \brief Recuperer le bateau demande
   *  \return Bateau demande
   *  \param [in] <boatNum> {Numero de bateau}
   */
  Bateau getBoatAt(int boatNum)const;

  /*!
   *  \brief Deplacer le bateau à la position demandee si valide
   *  \param [in] <boatNum> {Numero de bateau}
   *  \param [in] <p> {Position demandee}
   */
  void mooveBoatVPos(int boatNum,Position p);

  /*!
   *  \brief Surcharge de l'operateur de sortie pour une flotte
   *         au format "Bateau1\nBateau2\n..."
   */
  friend std::ostream & operator<<(std::ostream & os, const Flotte &);

  /*!
   *  \brief Surcharge de l'operateur d'entree pour une flotte
   */
  friend std::istream & operator>>(std::istream & is, Flotte &);
};

  /*!
   *  \brief Surcharge de l'operateur d'egalitee pour une flotte
   */
bool operator==(const Flotte & f1,const Flotte & f2);
#endif
