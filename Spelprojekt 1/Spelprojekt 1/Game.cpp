#include "Game.h"


using namespace std;

Game::Game()
{
	player = new Player(mHandler, sf::Vector2f(400, 300));
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
		mEventHandler.eventListen(window);

		window.clear(sf::Color::Black);

		sf::Time elapsed = deltaClock.getElapsedTime();
		float deltaTime = elapsed.asSeconds();
		//window.draw(temp);

		player->draw(window);
		player->update(deltaTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player->setPosition(10, 10);
		}

		deltaClock.restart();
		window.display();
	}
}