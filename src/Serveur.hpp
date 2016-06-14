#ifndef SERVEUR_HPP_
#define SERVEUR_HPP_

#pragma once
#include <unordered_map>
#include "SFML/Network.hpp"
#include "PacketType.hpp"
#include <vector>

class Serveur
{
private:
	typedef std::unordered_map<sf::TcpSocket *, std::string> Clients;
	Clients _clients;
        
	sf::TcpListener _listner;
        bool _quit;  

	void handlePackets();
	void broadCast(PacketType type, const std::string & msg);
        void sendClient(const Clients & client ,PacketType type, const std::string & msg);
    
public:
	Serveur(unsigned short port);
	~Serveur();
	void run();
  int _cpt ;
	
	
};


#endif
