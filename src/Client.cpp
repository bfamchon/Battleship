#include "Client.hpp"
#include "PacketType.hpp"
#include <iostream>

Client::Client() {}

Client::~Client() {}

void Client::setBloquant(bool bloquant){
  _bloquant= bloquant;
}

sf::Socket::Status Client::connect(const sf::IpAddress & IP, unsigned short port)
{
  //connect to server
  sf::Socket::Status stat= _mySocket.connect(IP, port);
  _mySocket.setBlocking(false);//_bloquant);
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
  // PacketType type;
  //packet>>type;
  if(status==sf::Socket::Done)
    {
      msg = handlePackets(packet);
      //std::cout<<msg<<"\n";
      //packet>>msg;
    }
  return status;
}

std::string Client::handlePackets(sf::Packet & packet){
  PacketType type;
  std::string msg;
  std::string retour="";
  packet>>type;
  switch(type)
    {
    case SERVEUR_FULL:
      {
       packet>> _messageServeur;
      }
      break;
      
    case SEND_LISTE_ATTENTE:
      {
       packet>>msg;	
       _listeJoueurs = msg;
      }
      break;
    }
  return retour;
}



