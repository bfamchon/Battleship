////////////////////////////////////////////////////////////
// Programme Serveur de BattleShip
////////////////////////////////////////////////////////////

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>

#include "Serveur.hpp"

using namespace sf;
////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
  int lePort = 5500;

  if  (argc == 2) {lePort = std::stoi(argv[1]);} 

  std::cout<<"attente adresses " <<std::endl;
  std::cout<<"Local host               :"<<sf::IpAddress::LocalHost<<"\n"
	   <<"Local                    : "<<sf::IpAddress::getLocalAddress()<<"\n"
           <<"Le port de connexion est : "<< lePort <<"\n";

  Serveur Srv(lePort);
  
  std::cout<< "serveur lance sur port : "<< lePort  <<std::endl;
  Srv.run();
  
    return 0;
}
