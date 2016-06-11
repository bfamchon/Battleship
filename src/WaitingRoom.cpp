#include "WaitingRoom.hpp"
#include "Game.hpp"

WaitingRoom::WaitingRoom() : Vue::Vue("Battle Not Cheap - Waiting room ... Place your army captain !") {}

void WaitingRoom::run()
{
	sf::Sprite spr_grid, spr_wlist;
	sf::Texture txt_grid, txt_wlist;
	
	if (!txt_grid.loadFromFile("../Textures/grid_bg.png"))
		exit(-1);
	if (!txt_wlist.loadFromFile("../Textures/waitinglist_bg.png"))
		exit(-1);
	
	spr_grid.setTexture(txt_grid);
	spr_grid.setPosition(50,125);
	
	spr_wlist.setTexture(txt_wlist);
	spr_wlist.setPosition(450,200);
	
	while (_window.isOpen())
    {
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					_window.close();
					Game g;
					g.run();
				}
			}
		}
      
		_window.clear(White);
		drawSpriteBG("../Textures/general_bg.png");
		
		_window.draw(spr_wlist);
		_window.draw(spr_grid);
		_window.display();
	}
}
