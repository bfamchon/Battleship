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

void Serveur::declancheChangementJoueur(){

  _jeu.changeJoueur();
  //on met � jour les clients 
  
  //envoi de stop play
  sendMsgClient(_jeu.getJInactif()->getSocketJoueur(),
		STOP_PLAY,
		"");
  
  //envoi de start play
  sendMsgClient(_jeu.getJCourant()->getSocketJoueur(),
		START_PLAY,
		""); 
  
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
		if (_jeu.getJoueur1().getPseudo() != it->second
		    && _jeu.getJoueur2().getPseudo() != it->second){
		  //le Pseudo n'existe pas
		  Joueur* j = _jeu.searchByName("notInit");
		  j->setPseudo(it->second);
		  j->setSocketJoueur(it->first);

		  broadCast(SEND_LISTE_ATTENTE,
			    _jeu.getListeJoueur() );
		} else {
		  _sameName=true;
		  sendMsgClient(it->first,DISCONNECT,"Pseudo deja utilise !");
		}
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
              //voir ajout d'une verification du joueur : a t il le droit de jouer !

	      
	      //Recoit un coup du client
	      { sf::Packet sendPacket;
		//std::string msg;
                Position p;
		packet>> p._x >>p._y;
		std::vector <int> boatState;
	        int res = _jeu.searchInPlayerFlotte(p,_jeu.getJInactif(),&boatState);
		// V�rifier les coordon�es
		if ( res == 3 )
		  {
		    for (unsigned int i = 0 ; i < boatState.size() ; ++i )
		      std::cout << boatState[i] << " ";
		    std::cout << std::endl;
		  }
		sendPacket.clear();
		sendPacket<<SEND_RESPONSE_COUP<< res << p._x << p._y;
                sendPacketClient(_jeu.getJCourant()->getSocketJoueur(),sendPacket);

                declancheChangementJoueur();
		
	      }
	      break;
	      
	    case  SEND_FLOTTE: 
	      {std::string msg;
		packet>>msg; //flotte sous forme de string
                //it->second; //Pseudo
		Joueur* j = _jeu.searchByName(it->second);
		Flotte f;
		std::istringstream iss(msg);
		iss >> f;
		j->setFlotte(f);
		_jeu.setNbPret(_jeu.getNbPret()+1);
		if (_jeu.getNbPret()<2){
		  sendMsgClient(it->first,
				SEND_USER_WAIT,
				"Bienvenue attente deuxieme joueur !");     
		} else {
     
		  //d�ja un joueur pret � jouer
		  if (sendMsgClientRet(it->first,
				       SEND_USER_WAIT,
				       "Bienvenue !") ==sf::Socket::Done){      
		    sendMsgClient(_jeu.getJInactif()->getSocketJoueur(),
				  STOP_PLAY,
				  ""); 
		     
		    //on cherche le joureur actif
		    //envoi de start play
		    sendMsgClient(_jeu.getJCourant()->getSocketJoueur(),
				  START_PLAY,
				  ""); 
		  }
		}
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
	  std::cout<<it->second<<" s'est d�connect�\n";
	  broadCast(GENERAL_MSG, it->second+" s'est d�connect�\n");
	  if (!_sameName ){
	    _jeu.initJoueur(it->second);
	  }else _sameName = false;
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

sf::Socket::Status Serveur::sendMsgClientRet(sf::TcpSocket * Socketclient,
					  PacketType type, const std::string & msg){
  sf::Packet packet;
  packet<<type<<msg;
  return Socketclient->send(packet);
}

void Serveur::sendMsgClient(sf::TcpSocket * Socketclient,
			    PacketType type, const std::string & msg){
  sf::Packet packet;
  packet<<type<<msg;
  sf::Socket::Status st = Socketclient->send(packet);
  if (st == sf::Socket::Done){/*nothing to do*/}
}

sf::Socket::Status Serveur::sendPacketClientRet(sf::TcpSocket * Socketclient,
					      sf::Packet & packet){
  return Socketclient->send(packet);
}

void Serveur::sendPacketClient(sf::TcpSocket * Socketclient,
			       sf::Packet & packet){
  sf::Socket::Status st = Socketclient->send(packet);
  if (st == sf::Socket::Done){/*nothing to do*/}
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

