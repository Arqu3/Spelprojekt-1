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
	ResourceHandler mRHandler;
	LevelHandler mLHandler;
	EventHandler mEventHandler;

	sf::Clock deltaClock;
};

#endif