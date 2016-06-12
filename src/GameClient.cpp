#include "GameClient.hpp"

/*
 * Initialise simplement la fenetre avec une taille de 800*600,
 * un titre, et une impossibilité de resize.
 * La fenetre est ensuite centrée sur l'écran.
 */

GameClient::GameClient() : _window(sf::VideoMode(800, 600),
				   "Battle Not Cheap - Ready to battle ? Let's connect !",
				   sf::Style::Titlebar | sf::Style::Close),
			   _wantsToPlay(true)
{
	_window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-WINDOW_WIDTH)/2,
					 (sf::VideoMode::getDesktopMode().height-WINDOW_HEIGHT)/2 ));
}

/*
 * La première interface est le menu, le client
 * a la possibilité de quitter, ou de rejoindre 
 * un serveur.
 *
 */

void GameClient::run()
{
  sf::Text connectText,quitText;
  sf::Font font;
  sf::Music music;
  
  // Si le chargement des fichiers échoue
  if (!music.openFromFile("../Audio/menu.ogg"))
    exit(-1);
  if (!font.loadFromFile("../Fonts/DooM.ttf"))
    exit(-1);
  
  // Initialisation des sprites & autres bidules
  connectText.setFont(font);
  connectText.setString("Connect now !");
  connectText.setCharacterSize(20);
  connectText.setColor(Black);
  connectText.setPosition(50,300);
  
  quitText.setFont(font);
  quitText.setString("Quit the game");
  quitText.setCharacterSize(20);
  quitText.setColor(Black);
  quitText.setPosition(50,350);
  
  music.setVolume(40);
  music.play();
  
  while (_window.isOpen())
    {
      sf::Event event;
      while (_window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    {
	      _wantsToPlay=false;
	      _window.close();
	    }
	  if (event.type == sf::Event::MouseButtonPressed)
	    {
	      if (event.mouseButton.button == sf::Mouse::Left)
		{
		  // Si le client clique dans la zone d'un texte
		  if ( connectText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
		    {
		      music.stop();
		      runWaitingRoom();
		    }
		  if ( quitText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
		    {
		      _wantsToPlay=false;
		      _window.close();
		    }
		}
	    }
	  // Si la souris est dans la zone du texte
	  if ( connectText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
	    connectText.setColor(RedWine);
	  if ( ! connectText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
	    connectText.setColor(Black);
	  
	  if ( quitText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
	    quitText.setColor(RedWine);
	  if ( ! quitText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
	    quitText.setColor(Black);
	}
      
      _window.clear(White);
      
      drawSpriteBG("../Textures/general_bg.png");
      _window.draw(connectText);
      _window.draw(quitText);
      _window.display();
    }
}

/*
 * La deuxième interface est la Waiting Room, le joueur
 * choisit sa flotte, et attend l'autre personne 
 * 
 * CF explications de run()
 *
 */

void GameClient::runWaitingRoom()
{
  _window.setTitle("Battle Not Cheap - Let's place your ships captain !");
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
	      if (event.mouseButton.button == sf::Mouse::Left)
		{
		  runBoards();
		  
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

/*
 * La troisième interface est le jeu.
 *
 * CF explications de run()
 * 
 */

void GameClient::runBoards()
{
  _window.setTitle("Battle Not Cheap - FIRE !");
  
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
	      if (event.mouseButton.button == sf::Mouse::Left)
		{
		  _window.close();
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

void GameClient::drawSpriteBG(std::string pathImg)
{
  sf::Texture bgTexture;
  if (!bgTexture.loadFromFile(pathImg))
    exit(-1);
  sf::Sprite bgSprite;
  bgSprite.setTexture(bgTexture);
  bgSprite.setPosition(0,0);
  _window.draw(bgSprite);
  
}

bool GameClient::getWantsToPlay() { return _wantsToPlay; }
