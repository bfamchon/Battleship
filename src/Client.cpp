#include "Client.hpp"
#include "PacketType.hpp"
#include <iostream>

Client::Client():_joueur(""),_closeRunWait(false),_messageServeur("") {}

Client::~Client() {}

Joueur Client::getJoueur(){
  return _joueur;
}
bool Client::getCloseRunWait() const{ return _closeRunWait;}
void Client::setCloseRunWait(bool etat) { _closeRunWait = etat;}
bool Client::getWinner() const{ return _Winner;}
void Client::setWinner(bool etat) { _Winner = etat;}
void Client::setBloquant(bool bloquant){
  _bloquant= bloquant;
}

void Client::setJRandFlotte(){
  _joueur.setRandFlotte();
}
void Client::turnJBoat(int boatNum){
  _joueur.turnBoat(boatNum);
}

void Client::mooveJBoat(int boatNum,Position p){
  _joueur.mooveBoat(boatNum,p);
}

bool Client::getJoueurIsActif() const{
  return _joueurIsActif;
}
void Client::setJoueurIsActif(bool joueurIsActif){
  _joueurIsActif=joueurIsActif;
}

sf::Socket::Status Client::connect(const sf::IpAddress & IP, unsigned short port)
{
  //connect to server
  

  sf::Socket::Status stat= _mySocket.connect(IP,port);
  _mySocket.setBlocking(false);//_bloquant);
  return stat;
}

sf::Socket::Status Client::send (PacketType type, const std::string & msg)
{
  sf::Packet packet;
  packet<<type<<msg;
  return _mySocket.send(packet);
}

sf::Socket::Status Client::send (sf::Packet & packet)
{
  return _mySocket.send(packet);
}

sf::Socket::Status Client::receive(std::string & msg)
{
  sf::Packet packet;
  sf::Socket::Status status=_mySocket.receive(packet);
  if(status==sf::Socket::Done)
    {
      msg = handlePackets(packet);
      std::cout<<msg<<"\n"; //messages en console si retour positionÃ© dans handlePacke
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

      case SERVEUR_MSG:
      {
       packet >> _messageServeur;
       retour = _messageServeur;
      }
      break;
      
    case DISCONNECT:
      {
       packet >> _messageServeur;
       retour = _messageServeur;
       _closeRunWait=true;
      }
      break;
        
    case SEND_LISTE_ATTENTE:
      {
       packet>>msg;	
       _listeJoueurs = msg;
      }
      break;

    case SEND_USER_WAIT:
      {
	packet >> _messageServeur;
	setJoueurIsActif(false);
      }
      break;
      
    case START_PLAY:
      {
	packet>> _messageServeur;
	setJoueurIsActif(true);
      }
      break;

       case STOP_PLAY:
      {
	packet>> _messageServeur;
	setJoueurIsActif(false);
      }
      break;

      case SEND_RESPONSE_COUP:
      {
	int res,x,y; 
	packet >> res >> x >> y;
	_joueur.setHitAt(res,x,y);
      }
      break;

      case MAJ_FLOTTE:
      {
	int res,x,y;
	packet >> res >> x >> y;
	_joueur.setFlotteAt(res,x,y);
	
	if( res == 3) {_messageServeur = "Touche et Coule !!!!!!!";}
	if( res == 2) {_messageServeur = "Touche !";}
      }
      break;
      
      case SEND_WINNER:
      {
	//une fois positionné le client a gagné
	_Winner = true;
      }
      break;
      
    }
  return retour;
}



