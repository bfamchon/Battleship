#ifndef SERVEUR_HPP_
#define SERVEUR_HPP_

#pragma once
#include <unordered_map>
#include "SFML/Network.hpp"
#include "PacketType.hpp"
#include "Jeu.hpp"
#include <vector>

class Serveur
{
private:
  typedef std::unordered_map<sf::TcpSocket *, std::string> Clients;
  Clients _clients;
  Jeu _jeu;
  sf::TcpListener _listner;
  bool _quit;
  bool _bloquant;
  bool _sameName = false;

  void handlePackets();
  void broadCast(PacketType type, const std::string & msg);
  
  sf::Socket::Status sendMsgClientRet(sf::TcpSocket * Socketclient ,
				      PacketType type, const std::string & msg);

  void sendMsgClient(sf::TcpSocket * Socketclient ,
		     PacketType type, const std::string & msg);
  
  sf::Socket::Status sendPacketClientRet(sf::TcpSocket * Socketclient,
					 sf::Packet & packet);
  
  void sendPacketClient(sf::TcpSocket * Socketclient ,
			sf::Packet & packet);
  
  void setBloquant(bool bloquant);
        
  
public:
  Serveur(unsigned short port);
  ~Serveur();
  void run();	
};


#endif
