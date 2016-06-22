/**
 * \file Client.hpp
 * \brief Classe Cliente de gestion des echanges reseau de BattleShip 
 * \author Sailly E
 * \version 1.0
 * \date 20 juin 2016
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


/*! \class Client
   * \brief classe client reseau
   *  La classe gere les connexion avec le serveur elle sert de lien 
   * entre l'interface graphique et le reseau
   */
class Client
{
private:
  sf::TcpSocket _mySocket; /*!<Socket de connection au serveur > */ 
  Joueur _joueur;          /*! <C'est le joueur du client > */
  bool _bloquant;          /*!<Flag pour rendre le socket bloquant > */
  bool _joueurIsActif;     /*!<Flag pour signifier au programme principal de desactiver la zone de saisie > */
  bool _closeRunWait;      /*!<Flag pour demander au programme principal de fermer la fenetre > */ 
  int _winner;             /*!<Flag pour demander au programme principal d'afficher la fenetre Winner > */
  bool _serveurShutDown;   /*!<Flag pour signifier que le serveur s'arrete */        
public:
  /*!
     *  \brief Constructeur
     *  Constructeur de la classe Client
     */
	Client();
	
  /*!
     *  \brief Destructeur
     *  Destructeur de la classe Client
     */
	~Client();
  
  /*!
     *  \brief Attribut Flag Bloquant
     *  Sert a passer le socket en bloquant 
     *  \param bloquant de type boolean
     */
  void setBloquant(bool bloquant);
  
  /*!
     *  \brief Appel de SetJRandFlotte de la classe Joueur
     *  Genere une Flotte avec des positions aleatoires
     */
  void setJRandFlotte();
  
  /*!
     *  \brief Appel de turnJBoat de la classe Joueur
     *  tourne le navire dans le sens des aiguilles d'une montre
     *  \param [in] <boatNum> {indice du navire}
     */
  void turnJBoat(int boatNum);
  
  /*!
     *  \brief getter de Joueur 
     *  \return le joueur du client
     */
  Joueur getJoueur();
  
  /*!
     *  \brief Deplacer le bateau boatNum a la position p
     *  \param [in] <boatNum> {indice du navire}
     *  \param [in] <p> {position du navire}
     */
  void mooveJBoat(int boatNum,Position p);
  
  /*!
     *  \brief getter de JoueurIsActif 
     *   sert a bloquer ou debloquer la zone de saisie des coups  
     *  \return l'etat du joueur
     */
  bool getJoueurIsActif() const;
  /*!
     *  \brief setter de JoueurIsActif 
     *   sert a bloquer ou debloquer la zone de saisie des coups
     *  \param [in] <joueurIsActif> {etat du joueur}
     */
  void setJoueurIsActif(bool joueurIsActif);
  
  /*!
     *  \brief getter du flag CloseRunWait
     *   permet de sortir de la boucle infinie de CloseRunWait la fenetre 
     *   d'attente de connexion   
     *  \return fermer = true
     */
  bool getCloseRunWait() const;
  /*!
     *  \brief setter du flag CloseRunWait
     *   sert a bloquer ou debloquer la zone de saisie des coups
     *  \param [in] <etat> {Fermer la fenetre}
     */
  void setCloseRunWait(bool etat);
  
  /*!
     *  \brief getter du flag Gagnant
     *   permet de sortir de la boucle infinie du jeux en designant un gagnant 
     *  \return gagnant = true
     */
  int getWinner() const;
  /*!
     *  \brief setter du flag Gagnant
     *   permet de sortir de la boucle infinie du jeux en designant un gagnant 
     *  \param [in] <etat> {gagnant = true}
     */
  void setWinner(int etat);

   /*!
     *  \brief getter du flag Serveur s'arrette
     *  Force l'arret de l'applicatiuon en cas d'arret du serveur
     *  \return arret du serveur = true
     */
  int getShutDown() const;
  /*!
     *  \brief setter du flag Serveur s'arrette
     *  Force l'arret de l'applicatiuon en cas d'arret du serveur  
     *  \param [in] <etat> {arret du serveur  = true}
     */
  void setShutDown(int etat);
  
  std::string _listeJoueurs;   /*!< conteneur pour affichage de la liste des joueurs en attentedans la WaitingRoom > */
  std::string _messageServeur; /*!< conteneur pour affichage du message dans la WaitingRoom > */

/*!
     *  \brief connexion du socket 
     *   permet de se connecter au serveur 
     *  \param [in] <IP> {adresse IP du serveur}
     *  \param [in] <port> {port de connexion du serveur}
     *  \return Status de la demande de connexion
     */
  sf::Socket::Status connect(const sf::IpAddress & IP, unsigned short port);
  /*!
     *  \brief Envoyer un message
     *   envoie d'un message au serveur
     *  \param [in] <type> {Type de messsage}
     *  \param [in] <msg> {message}
     *  \return Status de la demande de connexion
     */
  sf::Socket::Status send (PacketType type, const std::string & msg);
  /*!
     *  \brief Envoyer un packet
     *   envoie d'un packet au serveur
     *  \param [in] <packet> {un  TcpPacket brut}
     *  \return Status de la demande de connexion
     */
  sf::Socket::Status send (sf::Packet & packet);
  /*!
     *  \brief recoit un packet
     *  \param [out] <msg> {un  message}
     *  \return Status de la reception
     */
  sf::Socket::Status receive(std::string & msg);
  /*!
     *  \brief reception d'un packet
     *   arrivee d'un paquet envoye par le serveur
     *   il est decode et genere les differents traitements du client
     *  \param [in] <packet> {un  TcpPacket brut}
     *  \return le message en direction de la console
     */
  std::string  handlePackets(sf::Packet & packet);
	
};


#endif
