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
	sf::SoundBuffer test1;
	sf::Music music;
	sf::Sound test;

};

#endif