#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#pragma once
#include "SFML/Network.hpp"
#include "PacketType.hpp"

class Client
{
private:
  std::string _myName;
  sf::TcpSocket _mySocket;
public:
  Client(const std::string & name);
  ~Client();


  sf::Socket::Status connect(const sf::IpAddress & IP, unsigned short port);
  sf::Socket::Status send (PacketType type, const std::string & msg);
  sf::Socket::Status receive(std::string & msg);
  void handlePackets(const sf::Packet & packet);
	
};


#endif
