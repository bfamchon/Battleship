#include <SFML/System.hpp>
#include "Serveur.hpp"
#include "PacketType.hpp"
#include <iostream>
#include <sstream>
#include "Position.hpp"
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
		std::cout << "passe1 "<<it->second<< std::endl;

		//if(_jeu.searchByName(it->second) == nullptr) {
		  //le Pseudo n'existe pas
		  std::cout << "passe2"<< std::endl;
		  Joueur* j = _jeu.searchByName("notInit");
		  j->setPseudo(it->second);
		  j->setSocketJoueur(it->first);
		  //	std::cout << it->second << it->first<< std::endl; 
	
		  broadCast(SEND_LISTE_ATTENTE,
			    _jeu.getListeJoueur() );
		  /*} else {
		  sf::Packet retPacket;
		  retPacket<<DISCONNECT
			   <<"Pseudo deja utilise !";
		  if (it->first->send(retPacket) == sf::Socket::Done) {
		    //nothing to do
		    //enlever la connexion
		    std::cout << "passe3"<< std::endl;
		    // _clients.erase(it);
		    std::cout << "passe4"<< std::endl;
		  }
		  }*/
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
                Position p;
		packet>> p._x >>p._y;
		std::cout <<p._x << " " << p._y << std::endl;
		bool res = _jeu.foundInFlotte(p,_jeu.getJInactif());
		std::cout <<res<<std::endl;
                sf::Packet retPacket;
		retPacket<<SEND_RESPONSE_COUP<<res<<p._x << " " << p._y;
		if (_jeu.getJCourant()->getSocketJoueur()->send(retPacket)
			 == sf::Socket::Done){
		       //nothing to do
		     }

		
		
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
		 _jeu.setNbPret(_jeu.getNbPret()+1);
		 std::cout << _jeu.getNbPret() << std::endl;
		 
		 sf::Packet retPacket;
		 if (_jeu.getNbPret()<2){
		   //premier joueur connecté
		   retPacket<<SEND_USER_WAIT
			    <<"Bienvenue attente deuxieme joueur !";
                   if (it->first->send(retPacket) == sf::Socket::Done){
		     //nothing to do
		   }
		 } else {
     
		   //déja un joueur pret à jouer
		   retPacket.clear();
		   retPacket<<SEND_USER_WAIT
			    <<"Bienvenue !";
     
		   if (it->first->send(retPacket) == sf::Socket::Done){
		     //on cherche le joueur inactif
		     // envoie de stop_play
		     retPacket.clear();
		     retPacket<<STOP_PLAY
			      <<"Attente autre joueur !";
		     
		     if (_jeu.getJInactif()->getSocketJoueur()->send(retPacket)
			 == sf::Socket::Done){
		       //nothing to do
		     }
		     //on cherche le joureur actif
		     //envoi de start play
		     retPacket.clear();
		     retPacket<< START_PLAY<<"A vous de jouer !";
		     
		     if (_jeu.getJCourant()->getSocketJoueur()->send(retPacket)
			 == sf::Socket::Done){
		       //nothing to do
		     }
		   }
		 }

		 //a supprimer juste pour test
		 std::ostringstream oss,oss2;
		 oss << _jeu.getJoueur1().getFlotte();
		 std::cout<< "Joueur 1 : \n" << _jeu.getJoueur1().getPseudo()
			  << "\n" << oss.str() << std::endl;		 
		 oss2 << _jeu.getJoueur2().getFlotte();
		 std::cout<< "Joueur 2 : \n" << _jeu.getJoueur2().getPseudo()
			  << "\n"<< oss2.str() << std::endl;
		 
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
			  std::cout << "SERVEUR_: " << s <<std::endl;
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

