#include "EventHandler.h"
#include <iostream>

EventHandler::EventHandler(LevelHandler &lHandler):
mLHandler(&lHandler),
mInventory()
{
	mLHandler->setActiveLevel(0); //Change back!
	mInventory = new Inventory();
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
						//mViewMoveTo = sf::Vector2f(20, 0);
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
						mInventory->addItem(mLHandler->getActiveItems()[i]);
						std::cout << "Plockade upp magnet";
					}
					if (mLHandler->getActiveItems()[i]->getId() == "String")
					{
						mInventory->addItem(mLHandler->getActiveItems()[i]);
						std::cout << "Plockade upp tråd";
					}
				}
				else if (mLHandler->getActiveItems()[i]->getInteractable())
				{
					if (!mLHandler->getActiveItems()[i]->isInteracted())
					{
						mLHandler->getActiveItems()[i]->toggleInteractable();
						if (mLHandler->getActiveItems()[i]->getId() == "Block")
						{
							//Move Block, TODO - change to smooth movement
							mLHandler->getActiveItems()[i]->setPosition(630, 315);
							mLHandler->getActiveItems()[i]->toggleInteracted();
							//Toggle Astronaut Active, i + 1 is Astronaut currently, might be problematic?
							mLHandler->getActiveItems()[i + 1]->toggleActive();

							//This for-loop might be better?
							/*for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveItems().size(); i++)
							{
								std::cout << mLHandler->getActiveItems()[i]->getId();
								if (mLHandler->getActiveItems()[i]->getId() == "Astronaut")
								{
									mLHandler->getActiveItems()[i]->toggleActive();
								}
							}*/

							std::cout << "Knuffade Klossen";
						}
						if (mLHandler->getActiveItems()[i]->getId() == "Star")
						{
							mLHandler->getActiveItems()[i]->setPosition(900, 190);
							std::cout << "Satte stjärnan på väggen";
						}
					}
				}
			}
		}
	}

	//Check if playrect collision
	if (checkCollision(mLHandler->getActiveLevel()->getPlayRects(), point))
	{
		mLHandler->getPlayer()->moveToPosition(point.x, point.y);
		if (mLHandler->getPlayer()->getDirection().x < 0 && !mLHandler->getPlayer()->isFacingLeft())
		{
			mLHandler->getPlayer()->flipPlayer();
		}
		if (mLHandler->getPlayer()->getDirection().x > 0 && mLHandler->getPlayer()->isFacingLeft())
		{
			mLHandler->getPlayer()->flipPlayer();
		}
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
	//else if (mLHandler->getActiveLevel() == mLHandler->getLevel(1))
	//{
	//	for (Level::rectVector::size_type i = 0; i < mLHandler->getActiveLevel()->getRects().size(); i++)
	//	{
	//		if (checkCollision(mLHandler->getActiveLevel()->getRects()[i], point))
	//		{
	//			// i == 0 is ____ if ActiveScene is 0, or ___ if ActiveScene is 1, etc.
	//			if (i == 0)
	//			{
	//				if (mLHandler->getActiveLevel()->getActiveScene() == 0)
	//				{
	//					//Do stuff here
	//				}
	//				else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
	//				{
	//					//Do stuff here
	//				}
	//				else
	//				{
	//					//Do stuff here
	//				}
	//			}
	//			// i == 1 is ____
	//			else if (i == 1)
	//			{
	//				std::cout << "Insert stuff here";
	//			}
	//			// i == 2 is ____
	//			else if (i == 2)
	//			{
	//				std::cout << "Insert stuff here";
	//			}
	//			// i == 3 is ____
	//			else if (i == 3)
	//			{
	//				std::cout << "Insert stuff here";
	//			}
	//			// i == 4 is ____
	//			else if (i == 4)
	//			{
	//				std::cout << "Insert stuff here";
	//			}
	//			// i == 5 is ____
	//			else if (i == 5)
	//			{
	//				std::cout << "Insert stuff here";
	//			}
	//		}
	//	}
	//}
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
			if (event.key.code == sf::Keyboard::I)
			{
				for (Level::ItemVector::size_type i = 0; i < mInventory->getItems().size(); i++)
				{
					std::cout << mInventory->getItemId(i) << " ";
				}
			}
			if (event.key.code == sf::Keyboard::C)
			{
				for (Level::ItemVector::size_type i = 0; i < mInventory->getItems().size(); i++)
				{
					std::cout << mInventory->getItemId(i) << " ";
				}
			}
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

void EventHandler::update()
{
	std::cout << mLHandler->getActiveLevel() << std::endl;
	std::cout << mLHandler->getActiveLevel()->getActiveScene() << std::endl;
	//Only do this if the level needs moving camera
	if (mLHandler->getActiveLevel() == 0)
	{
		if (mLHandler->getActiveLevel()->getActiveScene() == 0)
		{
			if (mLHandler->getPlayer()->getPosition().x > 250)
			{
				mLHandler->getActiveLevel()->moveViewWithPlayer(mLHandler->getPlayer()->getPosition().x);
			}
		}
	}
}