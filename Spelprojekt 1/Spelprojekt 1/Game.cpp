#include "Game.h"

using namespace std;

Game::Game():
mRHandler(),
mLHandler(mRHandler),
dSystem(),
mEventHandler(mLHandler, dSystem)
{
	music.openFromFile(mRHandler.getMusic("Level1Music.ogg"));
}

Game::~Game()
{
}

void Game::update()
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Hittaren Hilma");

	music.setLoop(true);
	music.play();

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Time elapsed = deltaClock.getElapsedTime();
		float deltaTime = elapsed.asSeconds();

		mLHandler.update(deltaTime);
		mLHandler.draw(window);
		mEventHandler.eventListen(window);

		dSystem.update(deltaTime);
		dSystem.drawDialogue(window);

		deltaClock.restart();
		window.display();
	}
}