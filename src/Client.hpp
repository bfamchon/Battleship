/**
 * \file Client.hpp
 * \brief Classe Cliente de gestion des echanges réseau de BattleShip 
 * \author Sailly E
 * \version 0.9
 * \date 16 juin 2016
 *
 * Classe de gestion des echanges reseau cote Client
 *
 */
#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#pragma once
#include "SFML/Network.hpp"
#include "PacketType.hpp"
#include "Joueur.hpp"


/*! \class CLient
   * \brief classe client reseau
   *
   *  La classe gere les connexion avec le serveur
   */
class Client
{
private:
  sf::TcpSocket _mySocket; /*!<Socket de connection au serveur>*/ 
  Joueur _joueur; /*! <C'est le joueur du client > */
  bool _bloquant;          /*!<Flag pour rendre le socket bloquant>*/
  bool _joueurIsActif;     /*!<Flag pour signifier au programme principal de désactiver la zone de saisie>*/
  bool _closeRunWait;      /*!<Flag pour demander au programme principal de fermer la fenetre>*/ 
  int _winner;  /*!<Flag pour demander au programme principal d'afficher la fenetre Winner>*/
         
public:
  /*!
     *  \brief Constructeur
     *  Constructeur de la classe Client
     *  \param
     */
	Client();
  /*!
     *  \brief Destructeur
     *  Destructeur de la classe Client
     */
	~Client();


  
  /*!
     *  \brief Constructeur
     *  Sert a passer le socket en bloquant 
     *  \param bloquant de type boolean
     */
  void setBloquant(bool bloquant);
  void setJRandFlotte();
  void turnJBoat(int);
  Joueur getJoueur();
  void mooveJBoat(int,Position);
  
  bool getJoueurIsActif() const;
  void setJoueurIsActif(bool joueurIsActif);
  
  bool getCloseRunWait() const;
  void setCloseRunWait(bool etat);
  int getWinner() const;
  void setWinner(int);
  std::string _listeJoueurs; // conteneur pour affichage WaitingRoom
  std::string _messageServeur; // conteneur pour affichage WaitingRoom

  sf::Socket::Status connect(const sf::IpAddress & IP, unsigned short port);
  sf::Socket::Status send (PacketType type, const std::string & msg);
  sf::Socket::Status send (sf::Packet & packet);
  sf::Socket::Status receive(std::string & msg);
  std::string  handlePackets(sf::Packet & packet);


	
};


#endif
