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

	mRHandler.loadGeneral(window);
	mUI = new UI(mRHandler);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Time elapsed = deltaClock.getElapsedTime();
		float deltaTime = elapsed.asSeconds();

		if (mUI->getState() == UI::MAINMENU)
		{
			mUI->eventListen(window);
			mUI->drawMainMenu(window);
			if (mUI->getLevelStart())
			{
				mLHandler.setActiveLevel(mUI->getSelectedLevel(), mRHandler, true, window, mUI);
				mUI->setLevelStart(false);
			}
		}
		else if (mUI->getState() == UI::LEVELSELECT)
		{
			mUI->eventListen(window);
			mUI->drawLevelSelect(window);
			if (mUI->getLevelStart())
			{
				mLHandler.setActiveLevel(mUI->getSelectedLevel(), mRHandler, true, window, mUI);
				mUI->setLevelStart(false);
			}
		}
		else if (mUI->getState() != UI::MAINMENU)
		{
			mLHandler.update(deltaTime, window, mRHandler, mUI);
			if (mUI->getState() != UI::EXIT)
			{
				mLHandler.getActiveLevel()->eventListen(window);
			}
			else
			{
				mUI->eventListen(window);
				if (mUI->getLevelExit())
				{
					mLHandler.getActiveLevel()->toggleActive(mRHandler, window, mUI);
					mUI->setLevelExit(false);
				}
			}
			mLHandler.draw(window);
		}

		deltaClock.restart();
		window.display();
	}
}