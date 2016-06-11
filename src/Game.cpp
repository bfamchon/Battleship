#include "Game.hpp"
#include "Menu.hpp"

Game::Game() : Vue::Vue("Battle Not Cheap - FIRE !") {}

void Game::run()
{
	sf::Sprite spr_grid, spr_grid2;
	sf::Texture txt_grid;
	
	if (!txt_grid.loadFromFile("../Textures/grid_bg.png"))
		exit(-1);
	
	spr_grid.setTexture(txt_grid);
	spr_grid.setPosition(25,125);
	
	spr_grid2.setTexture(txt_grid);
	spr_grid2.setPosition(425,125);
	
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
					Menu m;
					m.run();
				}
			}
		}
      
		_window.clear(White);
		drawSpriteBG("../Textures/general_bg.png");
		_window.draw(spr_grid);
		_window.draw(spr_grid2);
		_window.display();
	}
}
