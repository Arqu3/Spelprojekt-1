#include "Game.h"

using namespace std;

Game::Game():
mRHandler(),
mLHandler(mRHandler),
mEventHandler(mLHandler)
{
	if (!test1.loadFromFile("concept_1.wav"))
	{
		cout << "could not load sound" << endl;
	}
	test.setBuffer(test1);

	if (!music.openFromFile("concept_1.wav"))
	{
		cout << "could not load music" << endl;
	}
	music.setLoop(true);
}

Game::~Game()
{
}

void Game::update()
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Hittaren Hilma");

	float dur = music.getDuration().asSeconds();
	cout << "Music duration as seconds: " << dur << endl;

	music.play();
	test.play();

	cout << test.getStatus() << endl;

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