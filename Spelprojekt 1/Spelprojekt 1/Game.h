#ifndef INCLUDED_GAME
#define INCLUDED_GAME

#include "EventHandler.h"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"

class Game
{
public:
	Game();
	~Game();

	void update();

private:
	//Handlers
	ResourceHandler mRHandler;
	LevelHandler mLHandler;
	EventHandler mEventHandler;

	//Deltatime
	sf::Clock deltaClock;

	//Sound
	sf::Music music;

};

#endif