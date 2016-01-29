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

//Mouseclick function
void EventHandler::mouseClick(sf::Event &event)
{
	std::cout << "Mouse Pressed" << std::endl;
	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	std::cout << "mouse y: " << event.mouseButton.y << std::endl;

	std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
	std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;

	//sf::Vector2f point ((float) event.mouseButton.x, (float) event.mouseButton.y);
	sf::Vector2f point(mWorldPos.x, mWorldPos.y);

	//Check collision
	if (checkCollision(mLHandler->getPlayer()->getRect(), point)) 
	{
		std::cout << "HIT!" << std::endl;
	}

	//Check if playrect collision
	if (checkCollision(mLHandler->getActiveLevel()->getPlayRects(), point))
	{
		mLHandler->getPlayer()->moveToPosition(point.x, point.y);
	}

	//TODO - Only if active level is 1
	if (checkCollision(mLHandler->getActiveLevel()->getRects(), point))
	{
		if (mLHandler->getActiveLevel()->getActiveScene() == 0)
		{
			mLHandler->getPlayer()->setPosition(150, 480);
			mLHandler->getActiveLevel()->changeScene(1);
		}
		else
		{
			mLHandler->getActiveLevel()->changeScene(0);
		}
	}
}

//Waits in background and listens for mouseclicks
void EventHandler::eventListen(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			//window closed
		case sf::Event::Closed:
			window.close();
			break;

			//mouse button pressed
		case sf::Event::MouseButtonPressed:
			// get the current mouse position in the window
			mPixelPos = sf::Mouse::getPosition(window);
			// convert it to world coordinates
			mWorldPos = window.mapPixelToCoords(mPixelPos);
			mouseClick(event);
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			break;

		default:
			break;
		}
	}
}