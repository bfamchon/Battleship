#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#pragma once
#include "SFML/Network.hpp"
#include "PacketType.hpp"

class Client
{
private:
	sf::TcpSocket _mySocket;
        int numJoueur;
        bool _bloquant;
public:
	Client();
	~Client();
  void setBloquant(bool bloquant);
  std::string _listeJoueurs; // conteneur pour affichage WaitingRoom
  std::string _messageServeur; // conteneur pour affichage WaitingRoom

  sf::Socket::Status connect(const sf::IpAddress & IP, unsigned short port);
  sf::Socket::Status send (PacketType type, const std::string & msg);
  sf::Socket::Status receive(std::string & msg);
  std::string  handlePackets(sf::Packet & packet);
	
};


#endif
