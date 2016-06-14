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
	      		
		//	std::cout<<it->second<<" has joined\n";
		//	broadCast(GENERAL_MSG, it->second+" has joined\n");
		broadCast(SEND_LISTE_ATTENTE,
			  _jeu.getListeJoueur() );

		/*if (_jeu._joueur1.getPseudo() !=
		  _jeu._joueur1.setPseudo(it->second);
		    */
		// creer joueur et
	      
		//renvoyer la liste d'attente
		//sf::sleep(sf::milliseconds(1000));
		/*	std::string listeAttente = "";
		for(Clients::iterator it2=_clients.begin(); it2!=_clients.end();)
		  {
		    listeAttente += it2->second;
		    listeAttente += "\n";
		  }
		  broadCast(SEND_LISTE_ATTENTE, listeAttente );*/
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
	      
	    case  SEND_FLOTTE:
	      {/*std::string msg;
	       packet>>msg;
               it->second;
	       packet>>it->second;
                if (_jeu.getJCourant()->getPseudo() == "notInit"){
		  _jeu.getJCourant()->setPseudo(it->second);
		   _jeu.changeJoueur();
	       
	       msg >>
	       */
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

  //int cpt = 0;
  sf::TcpSocket * nextClient=nullptr;
  while(!_quit)
    {
      //Handle newcoming clients
      /* if (cpt !=_clients.size() ){
        std::cout << "nb client " <<_clients.size() << std::endl;
        cpt = _clients.size() ;
	}*/
      // if (_clients.size()<2){
        if(nextClient==nullptr)
	  {
	    nextClient=new sf::TcpSocket;
	    nextClient->setBlocking(false);
	  }
	if(_listner.accept(*nextClient) == sf::Socket::Done && _clients.size()<2) //ici
	  {
	    _clients.insert(std::make_pair(nextClient, ""));
	    nextClient=nullptr;
	  }
	handlePackets();
	// }
	/* else {
	sf::Packet packet;
	packet<< SERVEUR_FULL <<"Désolé partie complette";
	nextClient->send(packet);
      }*/
    }
}

