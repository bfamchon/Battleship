#include "Vue.hpp"

Vue::Vue(std::string title) : _window(sf::VideoMode(800, 600),title,sf::Style::Titlebar | sf::Style::Close) 
{
	_window.setPosition(sf::Vector2i( (sf::VideoMode::getDesktopMode().width-WINDOW_WIDTH)/2,(sf::VideoMode::getDesktopMode().height-WINDOW_HEIGHT)/2 ) );
}

void Vue::drawSpriteBG(std::string pathImg)
{
  sf::Texture bgTexture;
  if (!bgTexture.loadFromFile(pathImg))
    exit(-1);
  sf::Sprite bgSprite;
  bgSprite.setTexture(bgTexture);
  bgSprite.setPosition(0,0);
  _window.draw(bgSprite);

}
