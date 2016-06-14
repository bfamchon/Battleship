#include <SFML/System.hpp>
#include "Serveur.hpp"
#include "PacketType.hpp"
#include <iostream>
#include "Client.hpp"
//#include <vector>

Serveur::Serveur(unsigned short port)
{
  _listner.listen(port);
  _listner.setBlocking(false);
  _quit =  false;
}



Serveur::~Serveur()
{
}

void Serveur::handlePackets()
{
  
  //handle incoming data
  for(Clients::iterator it=_clients.begin(); it!=_clients.end();)
    {
      sf::Packet packet;
      sf::Socket::Status status=it->first->receive(packet);
		
      switch (status)
	{
	case sf::Socket::Done:
	  PacketType type;
	  packet>>type;

	  switch(type)
	    {
	    case INITIAL_NAME_DATA:
	      //store the name
	      {packet>>it->second;
		//	std::cout<<it->second<<" has joined\n";
		// broadCast(INITIAL_NAME_DATA, it->second+" has joined\n");
		// creer joueur et
	      
		//renvoyer la liste d'attente
		sf::sleep(sf::milliseconds(1000));
		std::string listeAttente = "";
		for(Clients::iterator it2=_clients.begin(); it2!=_clients.end();)
		  {
		    listeAttente += it2->second;
		    listeAttente += "\n";
		  }
		  broadCast(SEND_LISTE_ATTENTE, listeAttente );
	      }
              break;
	      
	    case GENERAL_MSG:
	      {std::string msg;
	      packet>>msg;
	      std::cout<<it->second<<": "<<msg<<"\n";
	      broadCast(GENERAL_MSG, it->second+": "+msg);
	      }
	      break;

	    case  SHUTDOWN_SERVEUR: //commande pour arreter le serveur
              {std::string msg = "Arret serveur";
	      std::cout<<it->second<<": "<<msg<<"\n";
	      broadCast(GENERAL_MSG, it->second+": "+msg);
	      _quit = true;
	      }
	      break;
	      
	    case  DISCONNECT:
	      //traiter deconnexion
	      {

	      }
	      break;
	      /*
	    case  :

	      break;
	      */
	      //default:
	      
	    }

	  ++it;
	  break;

	case sf::Socket::Disconnected:
	  std::cout<<it->second<<" has been disconnected\n";
	  broadCast(GENERAL_MSG, it->second+" has been disconnected\n");
	  it=_clients.erase(it);
	  break;

	default:
	  ++it;
	}
    }
}

void Serveur::broadCast(PacketType type, const std::string & msg)
{
  for(Clients::iterator it=_clients.begin(); it!=_clients.end(); ++it)
    {
      sf::Packet pack;
      pack<<type<<msg;
      it->first->send(pack);
    }
 }

void sendClient(Client & client ,PacketType type, const std::string & msg){
  //sf::Packet pack;
  //pack<<type<<msg;
  client.send(type,msg);
}

void Serveur::run()
{
  sf::Thread thread([&]()
		    {
		      while(!_quit)
			{
			  std::string s;
			  std::getline(std::cin, s);
			  broadCast(SERVEUR_MSG, "SERVEUR: "+s);
			}
		    });
  thread.launch();

  sf::TcpSocket * nextClient=nullptr;
  while(!_quit)
    {
      //Handle newcoming clients
      if(nextClient==nullptr)
	{
	  nextClient=new sf::TcpSocket;
	  nextClient->setBlocking(false);
	}
      if(_listner.accept(*nextClient) == sf::Socket::Done)
	{
	  _clients.insert(std::make_pair(nextClient, ""));
	  nextClient=nullptr;
	}
      handlePackets();
    }
}

