#include "Game.h"

using namespace std;

Game::Game():
mRHandler(),
mLHandler(mRHandler),
mEventHandler(mLHandler)
{
	sound.setBuffer(*mRHandler.getSound("Test_Music.ogg"));
	music.openFromFile(mRHandler.getMusic("Test_3.ogg"));
}

Game::~Game()
{
}

void Game::update()
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Hittaren Hilma");

	//float dur = music.getDuration().asSeconds();
	//cout << "Music duration as seconds: " << dur << endl;

	music.play();
	//sound.play();

	//cout << sound.getStatus() << endl;

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