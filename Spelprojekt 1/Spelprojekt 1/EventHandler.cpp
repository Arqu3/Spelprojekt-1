#include "EventHandler.h"
#include <iostream>

EventHandler::EventHandler(LevelHandler &lHandler):
mLHandler(&lHandler)
{
	mLHandler->setActiveLevel(1); //Change back!
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

//Check collision with single rectangle
int EventHandler::checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point)
{
	if (boundingBox->contains(point))
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

	sf::Vector2f point(mWorldPos.x, mWorldPos.y);

	//Check collision with Player
	if (checkCollision(mLHandler->getPlayer()->getRect(), point)) 
	{
		std::cout << "HIT!" << std::endl;
	}

	//Check Item collision
	//Loop through all Items in active level
	//Check if mouse collided with Item
	//Check Id of that Item
	//Check if Item is looked at, if not, look at it and display dialogue
	//If Item is looked at, check if it is pickupable and if so toggle Active and add to inventory
	for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveLevel()->getItems().size(); i++)
	{
		if (checkCollision(mLHandler->getActiveLevel()->getItems()[i]->getRectangle(), point))
		{
			if (!mLHandler->getActiveLevel()->getItems()[i]->isLookedAt())
			{
				mLHandler->getActiveLevel()->getItems()[i]->toggleIsLookedAt();
				if (mLHandler->getActiveLevel()->getItems()[i]->getId() == "Cube")
				{
					mDialogueSystem->displayRubicCubeDialogue();
				}
				if (mLHandler->getActiveLevel()->getItems()[i]->getId() == "Magnet")
				{
					//mDialogueSystem->displayMagnetDialogue();
					std::cout << "Effin' magnets, how do they work!?";
				}
			}
			else if (mLHandler->getActiveLevel()->getItems()[i]->getPickupable())
			{
				mLHandler->getActiveLevel()->getItems()[i]->toggleActive(); //Change to not be a toggle?
				if (mLHandler->getActiveLevel()->getItems()[i]->getId() == "Magnet")
				{
					//TODO - Add to inventory
					std::cout << "Plockade upp magnet";
				}
			}
		}
	}

	//Check if playrect collision
	if (checkCollision(mLHandler->getActiveLevel()->getPlayRects(), point))
	{
		mLHandler->getPlayer()->moveToPosition(point.x, point.y);
	}

	//Separate for each level?
	//Check Rect Collisions
	for (Level::rectVector::size_type i = 0; i < mLHandler->getActiveLevel()->getRects().size(); i++)
	{
		if (checkCollision(mLHandler->getActiveLevel()->getRects()[i], point))
		{
			// i == 0 is the fishtankplace
			if (i == 0)
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
			// i == 1 is books in the bookcase
			else if (i == 1)
			{
				//mDialogueSystem->displayBookDialogue();
				std::cout << "Böcker!";
			}
			else if (i == 2)
			{
				std::cout << "Lampa!";
			}
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