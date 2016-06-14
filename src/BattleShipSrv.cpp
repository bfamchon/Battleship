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
  Serveur Srv(5500);

  std::cout<< "attente adresses " <<std::endl;
  std::cout<<"Local host:"<<sf::IpAddress::LocalHost<<"\n"
	   <<"Local: "<<sf::IpAddress::getLocalAddress()<<"\n"
	   <<"Public: "<<sf::IpAddress::getPublicAddress()<<"\n";
  
  std::cout<< "serveur lance" <<std::endl;
  Srv.run();
  
    return 0;
}
