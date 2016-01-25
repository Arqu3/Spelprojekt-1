#include "EventHandler.h"
#include <iostream>

EventHandler::EventHandler()
{

}

EventHandler::~EventHandler()
{

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
	//Kallar på kollisionsfunktion
	//if (checkCollision(mRectangle.rectangleBoundingBox(), point)) 
	//{
	//	mRectangle.randPos();
	//	std::cout << "HIT!";
	//}
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
			window.close();
			break;

			// we don't process other types of events
		default:
			break;
		}
	}
}