#include "Menu.hpp"
#include "WaitingRoom.hpp"


Menu::Menu() : Vue::Vue("Battle Not Cheap - Ready to battle ? Let's connect !") {}

void Menu::run()
{
	sf::Text connectText;
	sf::Font font;
	
	if (!font.loadFromFile("../Fonts/DooM.ttf"))
		exit(-1);
	connectText.setFont(font);
	connectText.setString("Connect now !");
	connectText.setCharacterSize(24);
	connectText.setColor(Black);
	connectText.setPosition(50,300);
	
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
					if ( connectText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
					{
						_window.close();
						WaitingRoom wr;
						wr.run();
					}
				}
			}
			if ( connectText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
				connectText.setColor(RedWine);
			if ( ! connectText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
				connectText.setColor(Black);
		}

		_window.clear(White);

		drawSpriteBG("../Textures/general_bg.png");
		_window.draw(connectText);
		
		_window.display();
	}
}
