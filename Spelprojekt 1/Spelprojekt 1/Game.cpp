#include "Game.h"

using namespace std;

Game::Game():
mRHandler(),
<<<<<<< HEAD
mLHandler(mRHandler),
dSystem(mLHandler, mRHandler),
mEventHandler(mLHandler, dSystem)
=======
mLHandler(mRHandler)
>>>>>>> refs/remotes/origin/master
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

	mLHandler.setActiveLevel(0);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Time elapsed = deltaClock.getElapsedTime();
		float deltaTime = elapsed.asSeconds();

		mLHandler.update(deltaTime, window);
		mLHandler.draw(window);
		mLHandler.getActiveLevel()->eventListen(window);

		dSystem.update(deltaTime);
		dSystem.drawDialogue(window);

		deltaClock.restart();
		window.display();
	}
}