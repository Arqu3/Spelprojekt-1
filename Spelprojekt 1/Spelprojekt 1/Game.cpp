#include "Game.h"


using namespace std;

Game::Game():
mEventHandler(mHandler)
{
}

Game::~Game()
{
}

void Game::update()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hittaren Hilma");

	//Resourcehandler test code
	sf::Sprite temp;
	temp.setPosition(400, 400);
	temp.setTexture(*mHandler.getTexture(0));

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Time elapsed = deltaClock.getElapsedTime();
		float deltaTime = elapsed.asSeconds();

		mEventHandler.eventDraw(window);
		mEventHandler.eventUpdate(deltaTime);
		mEventHandler.eventListen(window);
		//window.draw(temp);

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player->setPosition(10, 10);
		}*/

		deltaClock.restart();
		window.display();
	}
}