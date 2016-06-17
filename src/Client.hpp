#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#pragma once
#include "SFML/Network.hpp"
#include "PacketType.hpp"
#include "Joueur.hpp"


class Client
{
private:
	sf::TcpSocket _mySocket;
        bool _bloquant;
        bool _joueurIsActif;
         
public:
int posx, posy; //temporaire
int res;      //temporaire
	Client();
	~Client();
  void setBloquant(bool bloquant);
  bool getJoueurIsActif() const;
  void setJoueurIsActif(bool joueurIsActif);
  std::string _listeJoueurs; // conteneur pour affichage WaitingRoom
  std::string _messageServeur; // conteneur pour affichage WaitingRoom

  sf::Socket::Status connect(const sf::IpAddress & IP, unsigned short port);
  sf::Socket::Status send (PacketType type, const std::string & msg);
  sf::Socket::Status send (sf::Packet & packet);
  sf::Socket::Status receive(std::string & msg);
  std::string  handlePackets(sf::Packet & packet);
  
	
};


#endif
