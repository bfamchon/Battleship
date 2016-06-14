#include "Client.hpp"
#include "PacketType.hpp"
#include <iostream>

Client::Client() {}

Client::~Client() {}


sf::Socket::Status Client::connect(const sf::IpAddress & IP, unsigned short port)
{
  //connect to server
  sf::Socket::Status stat= _mySocket.connect(IP, port);
  _mySocket.setBlocking(false);
  return stat;
}

sf::Socket::Status Client::send (PacketType type, const std::string & msg)
{
  sf::Packet packet;
  packet<<type<<msg;
  return _mySocket.send(packet);
}

sf::Socket::Status Client::receive(std::string & msg)
{
  sf::Packet packet;
  sf::Socket::Status status=_mySocket.receive(packet);
  PacketType type;
  packet>>type;
  if(status==sf::Socket::Done)
    {
      std::cout<<msg<<"\n";
      packet>>msg;
    }
  return status;
}

void handlePackets(sf::Packet & packet){
  PacketType type;
  packet>>type;

  switch(type)
    {
    case SEND_LISTE_ATTENTE:
      {
       	
      }
      break;
    }
}



