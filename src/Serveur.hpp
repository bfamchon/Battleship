#ifndef SERVEUR_HPP_
#define SERVEUR_HPP_

#pragma once
#include <unordered_map>
#include "SFML/Network.hpp"
#include "PacketType.hpp"
#include "Jeu.hpp"
#include <vector>

class Serveur
{
private:
	typedef std::unordered_map<sf::TcpSocket *, std::string> Clients;
	Clients _clients;
        Jeu _jeu;
	sf::TcpListener _listner;
        bool _quit;
        bool _bloquant;

	void handlePackets();
	void broadCast(PacketType type, const std::string & msg);
        sf::Socket::Status sendClient(sf::TcpSocket & Socketclient ,PacketType type, const std::string & msg);
        void setBloquant(bool bloquant);
        
  
public:
	Serveur(unsigned short port);
	~Serveur();
        void run();	
};


#endif
