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
	for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveItems().size(); i++)
	{
		if (checkCollision(mLHandler->getActiveItems()[i]->getRectangle(), point))
		{
			if (mLHandler->getActiveItems()[i]->getActive())
			{
				if (!mLHandler->getActiveItems()[i]->isLookedAt())
				{
					mLHandler->getActiveItems()[i]->toggleIsLookedAt();
					if (mLHandler->getActiveItems()[i]->getId() == "Cube")
					{
						mDialogueSystem->displayRubicCubeDialogue();
					}
					if (mLHandler->getActiveItems()[i]->getId() == "Magnet")
					{
						//mDialogueSystem->displayMagnetDialogue();
						std::cout << "Effin' magnets, how do they work!?";
					}
					if (mLHandler->getActiveItems()[i]->getId() == "Bowl")
					{
						//mDialogueSystem->displayBowlDialogue();
						std::cout << "Skål!";
					}
					if (mLHandler->getActiveItems()[i]->getId() == "Block")
					{
						//mDialogueSystem->displayBlockDialogue();
						std::cout << "En kloss framför akvariet, undrar om det finns en astronaut bakom?";
					}
					if (mLHandler->getActiveItems()[i]->getId() == "Astronaut")
					{
						//mDialogueSystem->displayAstronautDialogue();
						std::cout << "Nämen titta, en astronaut.";
					}
					if (mLHandler->getActiveItems()[i]->getId() == "String")
					{
						//mDialogueSystem->displayStringDialogue();
						std::cout << "En tråd på golvet.";
					}
					if (mLHandler->getActiveItems()[i]->getId() == "Star")
					{
						//mDialogueSystem->displayStarDialogue();
						std::cout << "Stjärnklart!";
					}
				}
				else if (mLHandler->getActiveItems()[i]->getPickupable())
				{
					mLHandler->getActiveItems()[i]->toggleActive();
					if (mLHandler->getActiveItems()[i]->getId() == "Magnet")
					{
						//TODO - Add to inventory
						mInventory->addItem(mLHandler->getActiveItems()[i]);
						std::cout << "Plockade upp magnet";
					}
					if (mLHandler->getActiveItems()[i]->getId() == "Tråd")
					{
						//TODO - Add to inventory
						std::cout << "Plockade upp tråd";
					}
				}
				else if (mLHandler->getActiveItems()[i]->getInteractable())
				{
					mLHandler->getActiveItems()[i]->toggleInteractable();
					if (mLHandler->getActiveItems()[i]->getId() == "Block")
					{
						//TODO - toggleActive() on Astronaut to make it active
						//TODO - Move Block
						std::cout << "Knuffade Klossen";
					}
					if (mLHandler->getActiveItems()[i]->getId() == "Star")
					{
						mLHandler->getActiveItems()[i]->setPosition(900,190);
						std::cout << "Satte stjärnan på väggen";
					}
				}
			}
		}
	}

	//Check if playrect collision
	if (checkCollision(mLHandler->getActiveLevel()->getPlayRects(), point))
	{
		mLHandler->getPlayer()->moveToPosition(point.x, point.y);
	}

	//Check Rect Collisions
	//Separate for each level, getLevel(0) is Level1
	if (mLHandler->getActiveLevel() == mLHandler->getLevel(0))
	{
		for (Level::rectVector::size_type i = 0; i < mLHandler->getActiveLevel()->getRects().size(); i++)
		{
			if (checkCollision(mLHandler->getActiveLevel()->getRects()[i], point))
			{
				// i == 0 is the fishtankplace, or Thomas Room if in fishtankplace
				if (i == 0)
				{
					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
					{
						//TODO - Make player walk to (400, 370) before
						mLHandler->togglePlayer();
						mLHandler->getPlayer()->setPosition(150, 480);
						mLHandler->getActiveLevel()->changeScene(1);
					}
					else
					{
						//TODO - Make player walk to (150, 480) before
						mLHandler->togglePlayer();
						mLHandler->getPlayer()->setPosition(400, 370);
						mLHandler->getActiveLevel()->changeScene(0);
					}
				}
				// i == 1 is books in the bookcase
				else if (i == 1)
				{
					//mDialogueSystem->displayBookDialogue();
					std::cout << "Böcker!";
				}
				// i == 2 is lamp on table
				else if (i == 2)
				{
					//mDialogueSystem->displayLampDialogue();
					std::cout << "Lampa!";
				}
				// i == 3 is radio on table
				else if (i == 3)
				{
					//mDialogueSystem->displayRadioDialogue();
					std::cout << "Radio!";
				}
				// i == 4 is posters on wall
				else if (i == 4)
				{
					//mDialogueSystem->displayPostersDialogue();
					std::cout << "Affischer!";
				}
				// i == 5 is backpack near bed
				else if (i == 5)
				{
					//mDialogueSystem->displayBackpackDialogue();
					std::cout << "Ryggsäck! Ryggsäck!";
				}
			}
		}
	}

	/* Template for Rect check in other levels */
	else if (mLHandler->getActiveLevel() == mLHandler->getLevel(1))
	{
		for (Level::rectVector::size_type i = 0; i < mLHandler->getActiveLevel()->getRects().size(); i++)
		{
			if (checkCollision(mLHandler->getActiveLevel()->getRects()[i], point))
			{
				// i == 0 is Dollhouse if ActiveScene is 0, or ___ if ActiveScene is 1, etc.
				if (i == 0)
				{
					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
					{
						std::cout << "Dollhouse!";
					}
					else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
					{
						//Do stuff here
					}
					else
					{
						//Do stuff here
					}
				}
				// i == 1 is Planet 1 if ActiveScene is 0, 
				else if (i == 1)
				{
					std::cout << "Planet 1!";
				}
				// i == 2 is Planet 2 if ActiveScene is 0, 
				else if (i == 2)
				{
					std::cout << "Planet 2!";
				}
				// i == 3 is Planet 3 if ActiveScene is 0,
				else if (i == 3)
				{
					std::cout << "Planet 3!";
				}
				// i == 4 is Planet 4 if ActiveScene is 0,
				else if (i == 4)
				{
					std::cout << "Planet 4!";
				}
				// i == 5 is Planet 5 if ActiveScene is 0,
				else if (i == 5)
				{
					std::cout << "Planet 5!";
				}
				// i == 6 is Planet 6 if ActiveScene is 0,
				else if (i == 6)
				{
					std::cout << "Planet 6!";
				}
				// i == 7 is Planet 7 if ActiveScene is 0, 
				else if (i == 7)
				{
					std::cout << "Planet 7!";
				}
				// i == 8 is Planet 8 if ActiveScene is 0,
				else if (i == 8)
				{
					std::cout << "Planet 8!";
				}
				// i == 9 is Planet 9 if ActiveScene is 0,
				else if (i == 9)
				{
					std::cout << "Planet 9!";
				}
				// i == 10 is Door if ActiveScene is 0,
				else if (i == 10)
				{
					std::cout << "Door!";
				}
				// i == 11 is Stairs if ActiveScene is 0,
				else if (i == 11)
				{
					std::cout << "Stairs to scene 2!";
				}
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
			{
				window.close();
			}
			/*if (event.key.code == sf::Keyboard::I)
			{
				std::cout << mInventory->getItemId(0);
			}*/
			if (event.key.code == sf::Keyboard::P)
			{
				mLHandler->togglePlayer();
			}
			break;

		default:
			break;
		}
	}
}