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

	window.setVerticalSyncEnabled(true);

	window.setMouseCursorVisible(false);
	mLHandler.setActiveLevel(0, mRHandler, true, window);

	float fpsTimer = 0;

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Time fpsTime = fpsClock.getElapsedTime();

		fpsTimer++;

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

		if (fpsTimer >= 60.0f)
		{
			cout << 1.0f / fpsTime.asSeconds() << endl;
			fpsTimer = 0.0f;
		}

		fpsClock.restart().asSeconds();

		deltaClock.restart();
		window.display();
	}
}