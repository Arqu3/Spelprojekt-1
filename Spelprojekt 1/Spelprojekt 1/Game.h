#ifndef INCLUDED_GAME
#define INCLUDED_GAME

#include "LevelHandler.h"
#include "DialogueSystem.h"
#include "ResourceHandler.h"
#include "UI.h"
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

	//Deltatime
	sf::Clock deltaClock;

	//Sound
	sf::Music music;

	//UI
	UI *mUI;
};

#endif