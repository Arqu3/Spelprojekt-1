#include "EventHandler.h"
#include <iostream>

EventHandler::EventHandler(LevelHandler &lHandler):
mLHandler(&lHandler)
{
	mLHandler->setActiveLevel(0);
}

EventHandler::~EventHandler()
{
}

//Check collision with single rectangle
int EventHandler::checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point)
{
	if (boundingBox.contains(point))
	{	
		return 1;
	}
	return 0;
}

//Check collision with multiple rectangles
int EventHandler::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point)
{
	for (std::vector<sf::FloatRect*>::size_type i = 0; i < RectVector.size(); i++)
	{
		if (RectVector[i]->contains(point))
		{
			return 1;
		}
	}
	return 0;
}

//Funktion f�r musklick
void EventHandler::mouseClick(sf::Event &event)
{
	std::cout << "Mouse Pressed" << std::endl;
	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	sf::Vector2f point (event.mouseButton.x, event.mouseButton.y);
	//Kallar p� kollisionsfunktion
	if (checkCollision(mLHandler->getPlayer()->getRect(), point)) 
	{
		std::cout << "HIT!" << std::endl;
	}

	//Check if playrect collision
	if (checkCollision(mLHandler->getActiveLevel()->getPlayRects(), point))
	{
		mLHandler->getPlayer()->setPosition(point.x, point.y);
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

//NOT NEEDED, REMOVE LATER
void EventHandler::eventDraw(sf::RenderWindow &window){
	mLHandler->draw(window);
}

void EventHandler::eventUpdate(float deltaTime) {
	mLHandler->update(deltaTime);
}