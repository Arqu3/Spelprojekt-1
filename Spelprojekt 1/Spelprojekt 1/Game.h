#ifndef INCLUDED_GAME
#define INCLUDED_GAME

#include "Player.h"
#include "ResourceHandler.h"
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
	ResourceHandler mHandler;
	EventHandler mEventHandler;
	Player *player;

	sf::Clock deltaClock;
};

#endif