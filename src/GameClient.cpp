#include "GameClient.hpp"
#include "Position.hpp"
#include "RandomInRange.hpp"
#include "Flotte.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <locale>

/*
 * Initialise simplement la fenetre avec une taille de 800*600,
 * un titre, et une impossibilité de resize.
 * La fenetre est ensuite centre sur l'ecran.
 */

GameClient::GameClient(const sf::Texture& bgPath) : _window(sf::VideoMode(800, 600),
				   "Battle Not Cheap - Ready to battle ? Let's connect !",
				   sf::Style::Titlebar | sf::Style::Close),
						    _wantsToPlay(true),
						    _sprBG(bgPath)
{
	_window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-WINDOW_WIDTH)/2,
					 (sf::VideoMode::getDesktopMode().height-WINDOW_HEIGHT)/2 ));
	_window.setFramerateLimit(60);
}

/*
 * La premiere interface est le menu, le client
 * a la possibilite de quitter, ou de rejoindre 
 * un serveur.
 *
 */
GameClient::~GameClient() {}

void GameClient::setWindowPosition(int nb){ // eric pour debug
  if (nb == 1) _window.setPosition(sf::Vector2i(1,1));
  if (nb == 2) _window.setPosition(sf::Vector2i(820,1));
}

void GameClient::runError()
{
   sf::RenderWindow windowErr(sf::VideoMode(400, 100),
	    "Message erreur !",
	    sf::Style::Titlebar | sf::Style::Close);

  windowErr.setPosition(sf::Vector2i(
			 (sf::VideoMode::getDesktopMode().width-400)/2,
			 (sf::VideoMode::getDesktopMode().height-100)/2 ));
  
  sf::Text  messageServeur;
  sf::Font font;
  if (!font.loadFromFile("../Fonts/DooM.ttf"))
    exit(-1);
  
  messageServeur.setFont(font);
  messageServeur.setString("Pseudo deja pris !");
  messageServeur.setCharacterSize(20);
  messageServeur.setColor(Black);
  messageServeur.setPosition(10,10);
  
  while (windowErr.isOpen())
    {
      sf::Event event;
      while (windowErr.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    {
	      windowErr.close();
	    }	  
	}

      windowErr.clear(White);
      
      windowErr.draw(messageServeur); 
      windowErr.display();
    }
}

void GameClient::runResult()
{
  sf::RenderWindow windowResult(sf::VideoMode(200, 200),"",sf::Style::Titlebar | sf::Style::Close);
  sf::Sprite spr_result;
  sf::Texture txt_result; 
  windowResult.setPosition(sf::Vector2i(
			 _window.getPosition().x+300,
			 _window.getPosition().y+200)
			   );
  
  if ( _client.getWinner() == 1 )
    {
      windowResult.setTitle("YOU WIN !");
      if (!txt_result.loadFromFile("../Textures/winner.png"))
	exit(-1);
    }
  else
    {
      windowResult.setTitle("YOU LOSE !");      
      if (!txt_result.loadFromFile("../Textures/loser.png"))
	exit(-1);
    }

  spr_result.setTexture(txt_result);
  spr_result.setPosition(0,0);
  
  while (windowResult.isOpen())
    {
      sf::Event event;
      while (windowResult.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    {
	      windowResult.close();
	    }	  
	}

      windowResult.clear(White);
      windowResult.draw(spr_result);
      windowResult.display();
    }
}

void GameClient::runRegles()
{
  sf::RenderWindow windowRegles(sf::VideoMode(400,400),"",sf::Style::Titlebar | sf::Style::Close);
  sf::Sprite spr_result;
  sf::Texture txt_result;
  sf::Text reglesTexte;
  sf::Font font;
  
  if (!font.loadFromFile("../Fonts/LinLibertine.ttf"))
    exit(-1);
    
  windowRegles.setPosition(sf::Vector2i(
			 _window.getPosition().x+200,
			 _window.getPosition().y+100)
			   );
  windowRegles.setTitle("Regles du jeu BattleShip !");

  reglesTexte.setFont(font);
  reglesTexte.setCharacterSize(15);
  reglesTexte.setColor(Black);
  reglesTexte.setPosition(5,5);
  reglesTexte.setString("Plateau de 10*10.\n2 joueurs en coup par coup\n\nDescription des navires par joueur :\n     1 porte avion de 5 cases\n     1 croiseur de 4 cases\n     2 sous-marins de 3 cases\n     1 torpilleur de 2 cases\n     1 annexe de 1 case\n\nPlacement des navires :\nEn horizontale et/ou verticale.\nCote a cote autorise\nImpossible de poser 2 navires sur la meme case.\nJoueur du premier tour aleatoire \n1 coup = choisir une coordonnee horizontale et verticale\nLe premier joueur qui a tous ses navires coules a perdu.\nLe dernier a conserver au moins un navire en fin de partie\n a gagne.\nIl y a obligatoirement un gagnant.");

  // reglesTexte.setString(temp);

  
  while (windowRegles.isOpen())
    {
      sf::Event event;
      while (windowRegles.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    {
	      windowRegles.close();
	    }	  
	}

      windowRegles.clear(Gray);
      windowRegles.draw(spr_result);
      windowRegles.draw(reglesTexte);
      windowRegles.display();
    }
}

void GameClient::run()
{
  std::string msg="";
  std::string bufferIP = "IP Adress";
  std::string bufferPseudo = "Pseudo";
  std::string bufferPort = "5500";
  std::string zoneSaisieTexte = "NothingForTheMoment";
  int lePort = 5500;

  sf::Text connectText,quitText, saisieIP, saisiePseudo,saisiePort,
           messageServeur, serverText;

  sf::Sprite spr_zoneIP,spr_zonePseudo,spr_zonePort;
  sf::Texture txt_typeZone;

  sf::Font font;
  sf::Music music;
  
  unsigned int fieldMaxSize = 15;
  // Si le chargement des fichiers echoue
  if (!music.openFromFile("../Audio/menu.ogg"))
    exit(-1);
  if (!font.loadFromFile("../Fonts/DooM.ttf"))
    exit(-1);
  if (!txt_typeZone.loadFromFile("../Textures/typezone_bg.png"))
    exit(-1);

  // Initialisation des sprites & autres bidules
  connectText.setFont(font);
  connectText.setString("Connect now !");
  connectText.setCharacterSize(20);
  connectText.setColor(Black);
  connectText.setPosition(50,350);
  
  quitText.setFont(font);
  quitText.setString("Quit the game");
  quitText.setCharacterSize(20);
  quitText.setColor(Black);
  quitText.setPosition(50,450);

  serverText.setFont(font);
  serverText.setString("See rules");
  serverText.setCharacterSize(20);
  serverText.setColor(Black);
  serverText.setPosition(50,400);

  saisiePseudo.setPosition(55, 205);
  saisiePseudo.setFont(font);
  saisiePseudo.setString(bufferPseudo);
  saisiePseudo.setCharacterSize(20);
  saisiePseudo.setColor(Gray);
  
  saisieIP.setPosition(55, 255);
  saisieIP.setFont(font);
  saisieIP.setString(bufferIP);
  saisieIP.setCharacterSize(20);
  saisieIP.setColor(Gray);

  saisiePort.setPosition(55, 305);
  saisiePort.setFont(font);
  saisiePort.setString(bufferIP);
  saisiePort.setCharacterSize(20);
  saisiePort.setColor(Gray);

  spr_zonePseudo.setTexture(txt_typeZone);
  spr_zoneIP.setTexture(txt_typeZone);
  spr_zonePort.setTexture(txt_typeZone);
  spr_zonePseudo.setPosition(50,200);  
  spr_zoneIP.setPosition(50,250);
  spr_zonePort.setPosition(50,300);

  messageServeur.setFont(font);
  messageServeur.setString(_client._messageServeur);
  messageServeur.setCharacterSize(20);
  messageServeur.setColor(White);
  messageServeur.setPosition(50,10);

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
		      _client.setShutDown(false);
		      if ( _client.connect(bufferIP,lePort) == sf::Socket::Done)
			{
			  music.stop();
			  if (_client.send(INITIAL_NAME_DATA, bufferPseudo)
			      == sf::Socket::Done )
			    {			      
			    if (_client.receive(msg) == sf::Socket::Done)
			      {
				messageServeur.setString(_client._messageServeur); 
			      } else {
			      _client.setJoueurIsActif(false);
			      runWaitingRoom();
			    }
			    
			  }
			}		     	  
		    }
		  if ( quitText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
		    {
		      _wantsToPlay=false;
		      _window.close();
		    }
		  // Start server by clicking here
		  if ( serverText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
		    {
		      runRegles();
		      //system("xterm ./BattleShipSrv.out &");
		    }
		  
		  if (spr_zonePseudo.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
		    {
		      saisiePseudo.setColor(DarkGray);
		      zoneSaisieTexte = "Pseudo";
		      saisieIP.setColor(Gray);
		      saisiePort.setColor(Gray);
		    }
		  if (spr_zoneIP.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
		    {
		      if ( bufferIP == "IP Adress" )
			bufferIP = "";
		      saisieIP.setColor(DarkGray);
		      zoneSaisieTexte = "IP";
		      saisiePseudo.setColor(Gray);
		      saisiePort.setColor(Gray);
		    }
		  if (spr_zonePort.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
		    {
		      saisiePort.setColor(DarkGray);
		      zoneSaisieTexte = "5500";
		      saisieIP.setColor(Gray);
		      saisiePseudo.setColor(Gray);
		    }
		}
	    }
	  if(event.type==sf::Event::TextEntered)
	    {
	      char code=static_cast<char>(event.text.unicode);
	      if (zoneSaisieTexte == "Pseudo")
		{ 
		  if( code != '\b' && bufferPseudo.size() < fieldMaxSize ) 
		    bufferPseudo.push_back(code);
		  else if( code == '\b' )
		    {
		      if(bufferPseudo.size() > 0) 
			bufferPseudo.pop_back();
		    }
		   
		} else if (zoneSaisieTexte == "IP")
		{if (isdigit(code) || code == '\b' || code == '.' ){	 
		    if( code != '\b' && bufferIP.size() < fieldMaxSize ) 
		      bufferIP.push_back(code);
		    else if( code == '\b')
		      {
			if(bufferIP.size()>0) 
			  bufferIP.pop_back();
		      }
		  }
		}  else if (zoneSaisieTexte == "5500")
		{
		  if (isdigit(code) || code == '\b' ){
		    if( code != '\b' && bufferPort.size() < fieldMaxSize ) { 
		      bufferPort.push_back(code);
		      lePort = std::stoi(bufferPort);
		    }
		    else if( code == '\b')
		      {
			if(bufferPort.size()>0) { 
			  bufferPort.pop_back();
			  lePort = std::stoi(bufferPort);
			}
		      }
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

	   if ( serverText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
	     serverText.setColor(RedWine);
	   if ( ! serverText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
	     serverText.setColor(Black);
	}

      // if (_client.receive(msg) == sf::Socket::Done)
      if (_client.getShutDown()){
	//	std::cout <<"passe here"<<std::endl;   
	messageServeur.setString("Serveur arrete !");
      }else  {messageServeur.setString(_client._messageServeur);}

      _window.clear(White);
      
      _window.draw(_sprBG);
      
      saisiePseudo.setString(bufferPseudo);
      saisieIP.setString(bufferIP);
      saisiePort.setString(bufferPort);
      
      _window.draw(spr_zoneIP);
      _window.draw(spr_zonePseudo);
      _window.draw(spr_zonePort);
      _window.draw(messageServeur);
      _window.draw(saisieIP);
      _window.draw(saisiePseudo);
      _window.draw(saisiePort);
      
      _window.draw(connectText);
      _window.draw(quitText);
      _window.draw(serverText);
      _window.display();
    }
}

/*
 * La deuxieme interface est la Waiting Room, le joueur
 * choisit sa flotte, et attend l'autre personne 
 * 
 * CF explications de run()
 *
 */

void GameClient::runWaitingRoom()
{
  std::string msg="";
  _window.setTitle("Battle Not Cheap - Let's place your ships captain !");
  sf::Sprite spr_grid, spr_wlist,spr_radis;
  sf::Texture txt_grid, txt_wlist,txt_radis;
  sf::Text randomPosText, wlistText;
  sf::Font font;
  sf::Clock clock;
  sf::Time dCLickTime = sf::milliseconds(350);

  // Recuperation du numero de bateau dans click
  // Utilisation dans released
  int boatNumber=-1;
  
  if (!font.loadFromFile("../Fonts/DooM.ttf"))
    exit(-1);
  if (!txt_grid.loadFromFile("../Textures/grid_bg.png"))
    exit(-1);
  if (!txt_wlist.loadFromFile("../Textures/waitinglist_bg.png"))
    exit(-1);
  if (!txt_radis.loadFromFile("../Textures/radis.png"))
    exit(-1);

  spr_grid.setTexture(txt_grid);
  spr_grid.setPosition(50,125);
  
  spr_wlist.setTexture(txt_wlist);
  spr_wlist.setPosition(450,200);

  spr_radis.setTexture(txt_radis);
  spr_radis.setPosition(700,525);

  randomPosText.setFont(font);
  randomPosText.setString("Generate random position");
  randomPosText.setCharacterSize(20);
  randomPosText.setColor(Gray);
  randomPosText.setPosition(50,500);


  wlistText.setFont(font);
  wlistText.setString("");
  wlistText.setCharacterSize(20);
  wlistText.setColor(Black);
  wlistText.setPosition(460,220);


  _client.setJRandFlotte();
  
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
		  // Gestion du double click souris
		  if ( clock.getElapsedTime() <= dCLickTime )
		    {
		      if ( spr_grid.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
			{
			  int xPosInGrid = (sf::Mouse::getPosition(_window).x - 50)/CELL_SIZE;
			  int yPosInGrid = (sf::Mouse::getPosition(_window).y - 125)/CELL_SIZE;
			  if ( _client.getJoueur().getFlotte().foundInFlotte(Position{xPosInGrid,yPosInGrid}) )
			    {
			      // Search the boat's number at (x,y)
			      int boatNum = _client.getJoueur().getFlotte().searchBoatAt(Position{xPosInGrid,yPosInGrid});
			      _client.turnJBoat(boatNum);
			    }		   
			}
		    }
		  else
		    {
		      clock.restart();

		      if ( spr_grid.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
			{
			  int xPosInGrid = (sf::Mouse::getPosition(_window).x - 50)/CELL_SIZE;
			  int yPosInGrid = (sf::Mouse::getPosition(_window).y - 125)/CELL_SIZE;
   
			  if ( _client.getJoueur().getFlotte().foundInFlotte(Position{xPosInGrid,yPosInGrid}) )
			    {
			      boatNumber = _client.getJoueur().getFlotte().searchBoatAt(Position{xPosInGrid,yPosInGrid});
			      
			      }	   
			}
		      if ( spr_radis.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
			{ 
			  std::ostringstream uneflotte;
			  uneflotte << _client.getJoueur().getFlotte();
			  if (_client.send(SEND_FLOTTE, uneflotte.str())
			      == sf::Socket::Done ) {
			    runBoards();}
			}
		      
		      if ( randomPosText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
			{
			  _client.setJRandFlotte();
			}
		    }
		}
	    }
	  // Utilisation du numero de bateau ici
	  if ( event.type == sf::Event::MouseButtonReleased )
	    {
	      if ( boatNumber != -1 )
		{
		  int xPosReleased = (sf::Mouse::getPosition(_window).x - 50)/CELL_SIZE;
		  int yPosReleased = (sf::Mouse::getPosition(_window).y - 125)/CELL_SIZE;
		  // Moove boat at xPosReleased,yPosReleased if valid
		  _client.mooveJBoat(boatNumber,Position{xPosReleased,yPosReleased}); 
		}
	    }
	  if ( randomPosText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
	    randomPosText.setColor(RedWine);
	  if ( ! randomPosText.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
	    randomPosText.setColor(Gray);
	  if ( spr_radis.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
	    spr_radis.setColor(DarkGray);
	  if ( !spr_radis.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
	    spr_radis.setColor(White);
	}
      if (_client.receive(msg) == sf::Socket::Done){
        wlistText.setString(_client._listeJoueurs);    
      }
      
      if( _client.getCloseRunWait()) {
	   runError();
	  _client.setCloseRunWait(false);
	  _window.close();
	}

      if (_client.getShutDown() ){
	_client._messageServeur = "le serveur s'arrette !";
        _window.close();
      }
      _window.clear(White);
      _window.draw(_sprBG);
      _window.draw(spr_radis);
      _window.draw(spr_wlist);
      _window.draw(wlistText);
      _window.draw(spr_grid);
      _window.draw(randomPosText);
      drawSpritesGrid(spr_grid.getPosition().x,spr_grid.getPosition().y);
      _window.display();
    }
  
}

/*
 * La troisieme interface est le jeu.
 *
 * CF explications de run()
 * 
 */

void GameClient::runBoards()
{
   std::string msg="";
  
  _window.setTitle("Battle Not Cheap - FIRE !");
  
  sf::Sprite spr_grid, spr_grid2,spr_infosZone;
  sf::Texture txt_grid,txt_infosZone;
  sf::Text  messageServeur,Txt_Actif,Txt_Non_Actif;

  sf::Font font;
  if (!font.loadFromFile("../Fonts/DooM.ttf"))
    exit(-1);
  
  if (!txt_grid.loadFromFile("../Textures/grid_bg.png"))
    exit(-1);
  if (!txt_infosZone.loadFromFile("../Textures/infoszone.png"))
    exit(-1);
  
  spr_grid.setTexture(txt_grid);
  spr_grid.setPosition(25,125);
  
  spr_grid2.setTexture(txt_grid);
  spr_grid2.setPosition(425,125);

  spr_infosZone.setTexture(txt_infosZone);
  spr_infosZone.setPosition(100,50);

  //ajout messages du serveur
  messageServeur.setFont(font);
  messageServeur.setString("");
  messageServeur.setCharacterSize(20);
  messageServeur.setColor(Black);
  messageServeur.setPosition(105,55);

  Txt_Actif.setFont(font);
  Txt_Actif.setString("A vous de jouer !");
  Txt_Actif.setCharacterSize(20);
  Txt_Actif.setColor(White);  
  Txt_Actif.setPosition(105,20);

  Txt_Non_Actif.setFont(font);
  Txt_Non_Actif.setString("Attente autre joueur !");
  Txt_Non_Actif.setCharacterSize(20);
  Txt_Non_Actif.setColor(White);
  Txt_Non_Actif.setPosition(105,20);

  while (_window.isOpen())
    {
      sf::Event event;
      while (_window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    //ERIC ici
	    _window.close();
	  if (event.type == sf::Event::MouseButtonPressed)
	    {
	      if (event.mouseButton.button == sf::Mouse::Left)
		{
		  if ( spr_grid2.getGlobalBounds().contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))) )
		    {
		      if (_client.getJoueurIsActif())
			{
			  int xPosInGrid2 = (sf::Mouse::getPosition(_window).x - 425)/CELL_SIZE;
			  int yPosInGrid2 = (sf::Mouse::getPosition(_window).y - 125)/CELL_SIZE;
			  sf::Packet packet;
			  packet<<SEND_COUP<<xPosInGrid2<<yPosInGrid2;

			  if (_client.send(packet) == sf::Socket::Done ) {/* Nothing to do  */}

			  
			}
		    }
		}
	    }
	}
      
      if (_client.receive(msg) == sf::Socket::Done){
       	messageServeur.setString(_client._messageServeur);
      }

      if (_client.getWinner() != 0)
	{
	  //afficher gagnant et tout fermer
	  runResult();
	  _window.close();
	}
      
      if (_client.getShutDown() ){
	_client._messageServeur = "le serveur s'arrette !";
        _window.close();
      }
      _window.clear(White);
      _window.draw(_sprBG);
      _window.draw(spr_grid);
      _window.draw(spr_grid2);
      _window.draw(spr_infosZone);
      if (_client.getJoueurIsActif()){
	_window.draw(Txt_Actif);
      }else _window.draw(Txt_Non_Actif);
      _window.draw(messageServeur);
      drawSpritesGrid(spr_grid.getPosition().x,spr_grid.getPosition().y);
      drawSpritesHits(spr_grid2.getPosition().x,spr_grid2.getPosition().y);
      _window.display();
    }
}

void GameClient::drawSpritesGrid(float posGridX, float posGridY)
{
  sf::Texture txt_intactCell,txt_sinkCell,txt_hitCell;
  if (!txt_intactCell.loadFromFile("../Textures/ship_intact.png"))
    exit(-1);
  if (!txt_sinkCell.loadFromFile("../Textures/sink_boat.png"))
    exit(-1);
  if (!txt_hitCell.loadFromFile("../Textures/ship_hit.png"))
    exit(-1);

  sf::Sprite spr_intactCell,spr_sinkCell,spr_hitCell;
  spr_intactCell.setTexture(txt_intactCell);
  spr_sinkCell.setTexture(txt_sinkCell);
  spr_hitCell.setTexture(txt_hitCell);
  for ( int i=0; i < 6 ; i ++ )
    {
      int sizeBoat=_client.getJoueur().getFlotte().getBoatAt(i).getTaille();
      for ( int j=0; j < sizeBoat ; j++ )
	{
	  int boatPosX=_client.getJoueur().getFlotte().getBoatAt(i).getPositionAt(j)._x;
	  int boatPosY=_client.getJoueur().getFlotte().getBoatAt(i).getPositionAt(j)._y;
	  if ( _client.getJoueur().getFlotte().getBoatAt(i).getCoule())
	    {
	      spr_sinkCell.setPosition((CELL_SIZE*boatPosX)+posGridX+2,(CELL_SIZE*boatPosY)+posGridY+2);
	      _window.draw(spr_sinkCell);
	    }
	  else 
	    {
	      if  ( _client.getJoueur().getFlotte().getBoatAt(i).getEtatAt(j))
		{
		  spr_hitCell.setPosition((CELL_SIZE*boatPosX)+posGridX+2,(CELL_SIZE*boatPosY)+posGridY+2);
		  _window.draw(spr_hitCell);
		}
	      else
		{
		  spr_intactCell.setPosition((CELL_SIZE*boatPosX)+posGridX+2,(CELL_SIZE*boatPosY)+posGridY+2);
		  _window.draw(spr_intactCell);
		}
	    }
	}
    }
}

void GameClient::drawSpritesHits(float posGridX, float posGridY)
{
  sf::Texture txt_missCell,txt_hitCell,txt_sinkCell;
  if (!txt_missCell.loadFromFile("../Textures/ship_miss.png"))
    exit(-1);
  if (!txt_hitCell.loadFromFile("../Textures/ship_hit.png"))
    exit(-1);
  if (!txt_sinkCell.loadFromFile("../Textures/sink_boat.png"))
    exit(-1);

  sf::Sprite spr_missCell,spr_hitCell,spr_sinkCell;
  spr_missCell.setTexture(txt_missCell);
  spr_hitCell.setTexture(txt_hitCell);
  spr_sinkCell.setTexture(txt_sinkCell);
  for ( int x=0 ; x < 10 ; x++ )
    {
      for ( int y=0 ; y < 10 ; y++)
	{
	  if ( _client.getJoueur().getHitAt(x,y) == MISS_CELL )
	    {
	      spr_missCell.setPosition((CELL_SIZE*x)+posGridX+2,(CELL_SIZE*y)+posGridY+2);
	      _window.draw(spr_missCell);
	    }
	  else if ( _client.getJoueur().getHitAt(x,y) == HIT_CELL )
	    {
	      spr_hitCell.setPosition((CELL_SIZE*x)+posGridX+2,(CELL_SIZE*y)+posGridY+2);
	      _window.draw(spr_hitCell);
	    }
	  else if ( _client.getJoueur().getHitAt(x,y) == BOAT_SINK )
	    {
	      spr_sinkCell.setPosition((CELL_SIZE*x)+posGridX+2,(CELL_SIZE*y)+posGridY+2);
	      _window.draw(spr_sinkCell);
	    }
	}
    }
}

bool GameClient::getWantsToPlay() { return _wantsToPlay; }
