#include <SFML/System.hpp>
#include "Serveur.hpp"
#include "PacketType.hpp"
#include <iostream>
#include <sstream>
//#include "Client.hpp"
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
	      { 
	 	packet>>it->second;
                if (_jeu.getJCourant()->getPseudo() == "notInit"){
		  _jeu.getJCourant()->setPseudo(it->second);
		   _jeu.changeJoueur();
		}
		broadCast(SEND_LISTE_ATTENTE,
			  _jeu.getListeJoueur() );
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

	    case SEND_COUP: //eric a faire
	      //Recoit un coup du client
	      {std::string msg;
               	packet>>msg;
	      }
	      break;
	      
	    case  SEND_FLOTTE: // eric a faire
	      {std::string msg;
		packet>>msg; //flotte sous forme de string
                //it->second; //Pseudo
		Joueur* j = _jeu.searchByName(it->second);
		 Flotte f;
		 std::istringstream iss(msg);
		 iss >> f;
		 std::cout << f << std::endl;
		 j->setFlotte(f);
		 //a supprimer juste our test
                 std::ostringstream oss,oss2;
		 oss << _jeu.getJoueur1().getFlotte();
		 std::cout<< "Joueur 1 : \n"<< oss.str() << std::endl;		 
		 oss2 << _jeu.getJoueur2().getFlotte();
		 std::cout<< "Joueur 2 : \n"<< oss2.str() << std::endl;
		 //fin a supprimer
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
	  _jeu.initJoueur(it->second);
	  it=_clients.erase(it);
	  broadCast(SEND_LISTE_ATTENTE,_jeu.getListeJoueur() );
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

sf::Socket::Status sendClient(sf::TcpSocket & Socketclient ,PacketType type, const std::string & msg){
  sf::Packet packet;
  packet<<type<<msg;
  return Socketclient.send(packet);
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
      if(_listner.accept(*nextClient) == sf::Socket::Done && _clients.size()<2) //ici
	{
	  _clients.insert(std::make_pair(nextClient, ""));
	  nextClient=nullptr;
	} else {
	sf::Packet packet;
	packet<< SERVEUR_FULL <<"Desole partie complette";
     	nextClient->send(packet);
      }
	
      //Handle messages du clien vers serveur 	
      handlePackets();

    }
}

