#include "EventHandler.h"
#include <iostream>

EventHandler::EventHandler(ResourceHandler &handler):
mHandler(&handler)
{
	player = new Player(handler, sf::Vector2f(400, 300));
}

EventHandler::~EventHandler()
{
	delete player;
}

//Kollisionsfunktion som checkar kollision
int EventHandler::checkCollision(sf::FloatRect &boundingBox, sf::Vector2f &point)
{
	if (boundingBox.contains(point))
	{	
		return 1;
	}
	return 0;
}

//Funktion för musklick
void EventHandler::mouseClick(sf::Event &event)
{
	std::cout << "Mouse Pressed" << std::endl;
	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	sf::Vector2f point (event.mouseButton.x, event.mouseButton.y);
	player->setPosition(point.x, point.y);
	//Kallar på kollisionsfunktion
	if (checkCollision(player->getRect(), point)) 
	{
		std::cout << "HIT!" << std::endl;
	}
}

//Ligger i bakgrunden i spelloopen och lyssnar efter events
void EventHandler::eventListen(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			// window closed
		case sf::Event::Closed:
			window.close();
			break;

			// mouse button pressed
		case sf::Event::MouseButtonPressed:
			mouseClick(event);
				break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			break;

			// we don't process other types of events
		default:
			break;
		}
	}
}

void EventHandler::eventDraw(sf::RenderWindow &window){
	player->draw(window);
}

void EventHandler::eventUpdate(float deltaTime) {
	player->update(deltaTime);
}