#include "Game.h"

using namespace std;

Game::Game():
mRHandler(),
mLHandler(mRHandler)
{
	loadScreen.setTexture(*mRHandler.getTexture("loadscreen.jpg"));
}

Game::~Game()
{
}

void Game::update()
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Hittaren Hilma");

	window.clear(sf::Color::Black);
	window.draw(loadScreen);
	window.display();

	window.setMouseCursorVisible(false);

	mLHandler.setActiveLevel(0, mRHandler);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Time elapsed = deltaClock.getElapsedTime();
		float deltaTime = elapsed.asSeconds();

		mLHandler.update(deltaTime, window, mRHandler);
		mLHandler.draw(window);
		mLHandler.getActiveLevel()->eventListen(window);

		deltaClock.restart();
		window.display();
	}
}