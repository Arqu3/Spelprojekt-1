#include "Game.h"

using namespace std;

Game::Game():
mRHandler(),
mLHandler(mRHandler)
{
	music.openFromFile(mRHandler.getMusic("Level1Music.ogg"));
}

Game::~Game()
{
}

void Game::update()
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Hittaren Hilma");

	window.setMouseCursorVisible(false);

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

		deltaClock.restart();
		window.display();
	}
}