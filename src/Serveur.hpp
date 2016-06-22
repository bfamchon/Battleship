/**
 * \file Client.hpp
 * \brief Classe Cliente de gestion des echanges reseau de BattleShip 
 * \author Sailly E
 * \version 1.0
 * \date 20 juin 2016
 *
 * Classe de gestion des echanges reseau cote Serveur
 *
 */
 #ifndef SERVEUR_HPP_
#define SERVEUR_HPP_

#pragma once
#include <unordered_map>
#include "SFML/Network.hpp"
#include "PacketType.hpp"
#include "Jeu.hpp"
#include <vector>

/*! \class Serveur
   * \brief classe Serveur reseau
   *  La classe gere le jeu et fait le lien parmis tous les joueurs
   */
class Serveur
{
private:
  typedef std::unordered_map<sf::TcpSocket *, std::string> Clients;
  
  Clients _clients; /*!<Liste de socket client connectes au serveur */ 
  Jeu _jeu;         /*!<Jeu cotes serveur (maitre du jeu) */ 
  sf::TcpListener _listner;/*!<Processus d'ecoute du serveur */ 
  bool _quit;               /*!< Flag de sortie de boucle infinie*/ 
  bool _bloquant;			/*!< Sert a passer les socket en bloquant*/
  bool _sameName = false;   /*!< flag de gestion des connexions uniques*/
  bool _partieEncours = false; /*!< Sert a indiwuer que la partie est encours */

  /*! \brief change le joueur actif
   *  Lance un changement de joueur au niveau du serveur et envoie les messages
   *  aux client pour changer de joueur actif.
   */
  void declancheChangementJoueur();
  /*!
     *  \brief reception d'un packet
     *   arrivee d'un paquet envoye par les clients
     *   il est decode et genere les differents traitements au niveau serveur
     */
  void handlePackets();
  /*!
     *  \brief Envoie un message vers tous les clients
     *  \param [in] <type> {Le type du message}
     *  \param [in] <msg> {Le contenu du message}
     */
  void broadCast(PacketType type, const std::string & msg);
  
  /*!
     *  \brief Envoi d'un message au client
     *   Il envoie un message au client en attendant un statut de retour
     *  \param [in] <Socketclient > {un lien vers le socket}
     *  \param [in] <type> {Le type du message}
     *  \param [in] <msg> {Le contenu du message}
     *  \return Status de la reception
     */
  sf::Socket::Status sendMsgClientRet(sf::TcpSocket * Socketclient ,
				      PacketType type, const std::string & msg);
  /*!
     *  \brief Envoi d'un message au client
     *   Il envoie un message au client SANS statut de retour
     *  \param [in] <Socketclient > {un lien vers le socket}
     *  \param [in] <type> {Le type du message}
     *  \param [in] <msg> {Le contenu du message}
     */
  void sendMsgClient(sf::TcpSocket * Socketclient ,
		     PacketType type, const std::string & msg);
  /*!
     *  \brief Envoi d'un packet au client
     *   Il envoie un packet au client en attendant un statut de retour
     *  \param [in] <Socketclient > {un lien vers le socket}
     *  \param [in] <packet> {un lien vers un packet}
     *  \return Status de la reception
     */
  sf::Socket::Status sendPacketClientRet(sf::TcpSocket * Socketclient,
					 sf::Packet & packet);
  /*!
     *  \brief Envoi d'un packet au client
     *   Il envoie un packet au client SANS statut de retour
     *  \param [in] <Socketclient > {un lien vers le socket}
     *  \param [in] <packet> {un lien vers un packet}
     */
  void sendPacketClient(sf::TcpSocket * Socketclient ,
			sf::Packet & packet);
  /*!
     *  \brief setter de _bloquant
     *   utilise pour rendre les sockets bloquant
     *  \param [in] <bloquant> {bloquant = true}
     */
  void setBloquant(bool bloquant);
        
  
public:
  /*!
     *  \brief Constructeur
     *  Constructeur de la classe Serveur
     *  \param [in] <port> {port d'ecoute du serveur}
     */
  Serveur(unsigned short port);
  /*!
     *  \brief Destructeur
     *  Destructeur de la classe Serveur
     */
  ~Serveur();
  /*!
     *  \brief Lanceur du serveur
     *  Permet de demarrer la boucle d'ecoute
     */
  void run();	
};

#endif
