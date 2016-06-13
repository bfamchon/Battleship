////////////////////////////////////
// Programme Client de BattleShip //
////////////////////////////////////

#include "GameClient.hpp"


////////////////////////////////////////////////////////////
/// Entry point of application
///
///
///
////////////////////////////////////////////////////////////
int main()
{
	bool heWantsToPlay=true;
	sf::Texture txt_BG;

	if (!txt_BG.loadFromFile("../Textures/general_bg.png"))
	  exit(-1);

	while( heWantsToPlay )
	{
	  GameClient gc(txt_BG);
		
		gc.run();
		heWantsToPlay = gc.getWantsToPlay();
	}
	
	return 0;
}
