#ifndef VUE_HPP
#define VUE_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int GRID_WIDTH = 350;
const int GRID_HEIGHT = 350;
const int CELL_SIZE = 35;
const int CELL_WIDTH = GRID_WIDTH / CELL_SIZE;
const int CELL_HEIGHT = GRID_HEIGHT / CELL_SIZE;

const sf::Color White (255,255,255);
const sf::Color Black (0,0,0);
const sf::Color Gray (240,240,240);
const sf::Color DarkGray (150,150,150);
const sf::Color RedWine (127,26,26);

class Vue {
	protected:
		sf::RenderWindow _window;
	public:
		Vue(std::string);
		virtual void run()=0;
		void drawSpriteBG(std::string);
		
};

#endif
