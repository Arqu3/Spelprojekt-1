#include "Game.h"

using namespace std;

Game::Game():
mRHandler(),
mLHandler(mRHandler)
{
}

Game::~Game()
{
}

void Game::update()
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Hittaren Hilma");

	window.setMouseCursorVisible(false);
	mLHandler.setActiveLevel(1, mRHandler, true, window);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Time elapsed = deltaClock.getElapsedTime();
		float deltaTime = elapsed.asSeconds();

		if (mLHandler.getActiveLevel()->getUI()->getState() == UI::MAINMENU)
		{
			mLHandler.getActiveLevel()->getUI()->eventListen(window);
			mLHandler.getActiveLevel()->getUI()->drawMainMenu(window);
		}
		else if (mLHandler.getActiveLevel()->getUI()->getState() != UI::MAINMENU)
		{
			mLHandler.update(deltaTime, window, mRHandler);
			if (mLHandler.getActiveLevel()->getUI()->getState() != UI::EXIT)
			{
				mLHandler.getActiveLevel()->eventListen(window);
			}
			else
			{
				mLHandler.getActiveLevel()->getUI()->eventListen(window);
			}
			mLHandler.draw(window);
		}

		deltaClock.restart();
		window.display();
	}
}