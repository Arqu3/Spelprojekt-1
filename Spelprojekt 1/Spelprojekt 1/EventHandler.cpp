#include "EventHandler.h"
#include <iostream>

EventHandler::EventHandler(LevelHandler &lHandler):
mLHandler(&lHandler)
{
	mLHandler->setActiveLevel(0); //Change back!
	mInventory = new Inventory();
	mItemInteraction = false;
	mInventoryMode = false;
}

EventHandler::~EventHandler()
{
}

//Check collision between single rectangle and point
int EventHandler::checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point)
{
	if (boundingBox.contains(point))
	{	
		return 1;
	}
	return 0;
}

//Check collision between single rectangle pointer and point
int EventHandler::checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point)
{
	if (boundingBox->contains(point))
	{
		return 1;
	}
	return 0;
}

//Check collision between a vector of rectangles and a point
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

	//Check if playrect collision
	if (checkCollision(mLHandler->getActiveLevel()->getPlayRects(), point))
	{
		mLHandler->getPlayer()->moveToPosition(point.x, point.y);
		mItemInteraction = false;
	}

	//Check Item collision
	//Loop through all Items in active level
	for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveItems().size(); i++)
	{
		//Check if mouse collided with Item
		if (checkCollision(mLHandler->getActiveItems()[i]->getRectangle(), point))
		{
			//Check if Item is Active
			if (mLHandler->getActiveItems()[i]->getActive())
			{
				//Check Id of that Item
				if (mLHandler->getActiveItems()[i]->getId() == "Cube")
				{
					//Move Player to the closest point that is still inside the playrect
					mLHandler->getPlayer()->moveToPosition(340, 370);
					//Set the Item as "Target Item"
					mTargetItem = mLHandler->getActiveItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
				}
				if (mLHandler->getActiveItems()[i]->getId() == "Magnet")
				{
					mLHandler->getPlayer()->moveToPosition(340, 370);
					mTargetItem = mLHandler->getActiveItems()[i];
					mItemInteraction = true;
				}
				if (mLHandler->getActiveItems()[i]->getId() == "Bowl")
				{
					mLHandler->getPlayer()->moveToPosition(340, 370);
					mTargetItem = mLHandler->getActiveItems()[i];
					mItemInteraction = true;
				}
				if (mLHandler->getActiveItems()[i]->getId() == "Block")
				{
					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
					{
						mLHandler->getPlayer()->moveToPosition(560, 365);
					}
					else
					{
						mLHandler->getPlayer()->moveToPosition(490, 500);
					}
					mTargetItem = mLHandler->getActiveItems()[i];
					mItemInteraction = true;
				}
				if (mLHandler->getActiveItems()[i]->getId() == "Astronaut")
				{
					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
					{
						mLHandler->getPlayer()->moveToPosition(560, 365);
					}
					else
					{
						mLHandler->getPlayer()->moveToPosition(490, 500);
					}
					mTargetItem = mLHandler->getActiveItems()[i];
					mItemInteraction = true;
				}
				if (mLHandler->getActiveItems()[i]->getId() == "String")
				{
					mLHandler->getPlayer()->moveToPosition(340, 370);
					mTargetItem = mLHandler->getActiveItems()[i];
					mItemInteraction = true;
				}
				if (mLHandler->getActiveItems()[i]->getId() == "Star")
				{
					mLHandler->getPlayer()->moveToPosition(480, 450);
					mTargetItem = mLHandler->getActiveItems()[i];
					mItemInteraction = true;
				}
			}
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
						//Make Player get into position for Scene change
						mLHandler->getPlayer()->moveToPosition(400, 370);
						//Set Collision Rect to Scene change position
						mSceneChangeRect = sf::FloatRect(sf::Vector2f(400, 370), sf::Vector2f(10, 10));
						//Set if Player should toggle on Scene Change
						mPlayerToggle = true;
						//Set starting position of Player in new Scene
						mSceneChangePlayerPos = sf::Vector2f(150, 480);
						//Set which Scene will be the new Scene
						mNewScene = 1;
					}
					else
					{
						//Make Player get into position for Scene change
						mLHandler->getPlayer()->moveToPosition(150, 480);
						//Set Collision Rect to Scene change position
						mSceneChangeRect = sf::FloatRect(sf::Vector2f(150, 480), sf::Vector2f(10, 10));
						//Set if Player should toggle on Scene Change
						mPlayerToggle = true;
						//Set starting position of Player in new Scene
						mSceneChangePlayerPos = sf::Vector2f(400, 370);
						//Set which Scene will be the new Scene
						mNewScene = 0;
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
			//if Inventory Mode is enabled, only check for collisions with Items in Inventory
			if (mInventoryMode)
			{
				mInventory->checkCollision(mInventory->getItems(), mWorldPos);
			}
			else
			{
				mouseClick(event);
			}
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
			if (event.key.code == sf::Keyboard::M)
			{
				mInventoryMode = !mInventoryMode;
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

void EventHandler::update(sf::RenderWindow &window)
{
	//Only do this if the level needs moving camera
	//mLHandler->getLevel(1) is currently LastLevel, change as necessary
	if (mLHandler->getActiveLevel() == mLHandler->getLevel(1))
	{
		//Scene 1 is the big, second room in LastLevel, change as necessary
		if (mLHandler->getActiveLevel()->getActiveScene() == 1)
		{
			//520 is the distance the Player has to be from the left side of the level before the camera starts scrolling, change as necessary
			//1000 is the distance the Player has to be from the right side of the level before the camera starts scrolling, change as necessary
			//In this case the camera scrolls while the Player is between 520 and 1000.
			if (mLHandler->getPlayer()->getPosition().x > 520 && mLHandler->getPlayer()->getPosition().x < 1000)
			{
				//Make camera follow Player position
				mLHandler->getActiveLevel()->moveViewWithPlayer(mLHandler->getPlayer()->getPosition().x);
			}
		}
	}


	//Check if Player is in position to change Scene
	if (mLHandler->getPlayer()->getRect().intersects(mSceneChangeRect))
	{
		//Toggle Player if the new Scene needs it
		if (mPlayerToggle)
		{
			mLHandler->togglePlayer();
		}
		//Set Player position to the starting position of the new Scene
		mLHandler->getPlayer()->setPosition(mSceneChangePlayerPos.x, mSceneChangePlayerPos.y);
		//Change to the new Scene
		mLHandler->getActiveLevel()->changeScene(mNewScene);
	}


	//Check if Item interaction is enabled, which it only is when an Item is clicked
	if (mItemInteraction)
	{
		//Check if any part of the Player intersects with the Item
		if (mLHandler->getPlayer()->getGlobalRect().intersects(mTargetItem->getRectangle()))
		{
			//Check if Item has already been looked at
			if (!mTargetItem->isLookedAt())
			{
				mTargetItem->toggleIsLookedAt();
				if (mTargetItem->getId() == "Cube")
				{
					mDialogueSystem->displayRubicCubeDialogue();
				}
				if (mTargetItem->getId() == "Magnet")
				{
					//mDialogueSystem->displayMagnetDialogue();
					std::cout << "Effin' magnets, how do they work!?";
				}
				if (mTargetItem->getId() == "Bowl")
				{
					//mDialogueSystem->displayBowlDialogue();
					std::cout << "Skål!";
				}
				if (mTargetItem->getId() == "Block")
				{
					//mDialogueSystem->displayBlockDialogue();
					std::cout << "En kloss framför akvariet, undrar om det finns en astronaut bakom?";
				}
				if (mTargetItem->getId() == "Astronaut")
				{
					//mDialogueSystem->displayAstronautDialogue();
					std::cout << "Nämen titta, en astronaut.";
				}
				if (mTargetItem->getId() == "String")
				{
					//mDialogueSystem->displayStringDialogue();
					std::cout << "En tråd på golvet.";
				}
				if (mTargetItem->getId() == "Star")
				{
					//mDialogueSystem->displayStarDialogue();
					std::cout << "Stjärnklart!";
				}
			}
			//Check if Item can be picked up
			else if (mTargetItem->getPickupable())
			{
				//Make Item inactive when it is picked up
				mTargetItem->toggleActive();
				if (mTargetItem->getId() == "Magnet")
				{
					mInventory->addItem(mTargetItem);
					std::cout << "Plockade upp magnet";
				}
				if (mTargetItem->getId() == "String")
				{
					mInventory->addItem(mTargetItem);
					std::cout << "Plockade upp tråd";
				}
			}
			//Check if Item can be interacted with
			else if (mTargetItem->getInteractable())
			{
				//Check if Item has already been interacted with
				if (!mTargetItem->isInteracted())
				{
					mTargetItem->toggleInteractable();
					if (mTargetItem->getId() == "Block")
					{
						//Move Block, TODO - change to smooth movement, set Animation to "Push" and move Player
						mTargetItem->setPosition(630, 315);
						mTargetItem->toggleInteracted();

						//Find Astronaut in ItemVector and make it active
						for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveItems().size(); i++)
							{
							if (mLHandler->getActiveItems()[i]->getId() == "Astronaut")
							{
								mLHandler->getActiveItems()[i]->toggleActive();
							}
						}

						std::cout << "Knuffade Klossen";
					}
					if (mTargetItem->getId() == "Star")
					{
						mTargetItem->setPosition(900, 190);
						std::cout << "Satte stjärnan på väggen";
					}
				}
			}
			//Disable Item interaction when done
			mItemInteraction = false;
		}
	}


	//If Player is moving to the left (getDirection.x < 0) and isn't already facing left, flip Player
	if (mLHandler->getPlayer()->getDirection().x < 0 && !mLHandler->getPlayer()->isFacingLeft())
	{
		mLHandler->getPlayer()->flipPlayer();
	}
	//If Player is moving to the right (getDirection.x > 0) and is facing left, flip Player
	if (mLHandler->getPlayer()->getDirection().x > 0 && mLHandler->getPlayer()->isFacingLeft())
	{
		mLHandler->getPlayer()->flipPlayer();
	}


	//Inventory
	mInventory->update(window);
	if (mInventoryMode)
	{
		mInventory->draw(window);
	}
}