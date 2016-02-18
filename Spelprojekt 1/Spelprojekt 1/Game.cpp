#include "Game.h"

using namespace std;

Game::Game():
mRHandler(),
mLHandler(mRHandler),
mMenu(mRHandler)
{
	loadScreenTexture.loadFromFile("Resources/Textures/loadscreen.jpg");
	loadScreen.setTexture(loadScreenTexture);
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

	//window.setMouseCursorVisible(false);

	mLHandler.setActiveLevel(0, mRHandler, true);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Time elapsed = deltaClock.getElapsedTime();
		float deltaTime = elapsed.asSeconds();

		mMenu.update(deltaTime);

		if (mMenu.getState() != Menu::State::InGame)
		{
			mMenu.eventListen(window);
		}

		if (mMenu.getState() == Menu::State::InGame)
		{
			mLHandler.update(deltaTime, window, mRHandler);
			mLHandler.getActiveLevel()->eventListen(window, mMenu);
		}

		mLHandler.draw(window);
		mMenu.draw(window);

		deltaClock.restart();
		window.display();
	}
}