#include "Game.h"

using namespace std;

Game::Game():
mLHandler(mRHandler),
mEventHandler(mLHandler)
{
}

Game::~Game()
{
}

void Game::update()
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Hittaren Hilma");

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Time elapsed = deltaClock.getElapsedTime();
		float deltaTime = elapsed.asSeconds();

		mLHandler.update(deltaTime);
		mLHandler.draw(window);
		mEventHandler.eventListen(window);

		deltaClock.restart();
		window.display();
	}
}