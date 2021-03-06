<<<<<<< HEAD

#include "EventHandler.h"
#include <iostream>

EventHandler::EventHandler(LevelHandler &lHandler):
mLHandler(&lHandler)
{

	mLHandler->setActiveLevel(1); //Change back!
	//mLHandler->setActiveLevel(0); //Change back!
=======
<<<<<<< HEAD
#include "EventHandler.h"
#include <iostream>

using namespace std;

EventHandler::EventHandler(LevelHandler &lHandler):
mLHandler(&lHandler)
{
	mLHandler->setActiveLevel(0); //Change back!
>>>>>>> refs/remotes/origin/master
	mInventory = new Inventory();
	mItemInteraction = false;
	mInventoryMode = false;

<<<<<<< HEAD
=======
	if (!mBuffer.loadFromFile("Resources/Sounds/ItemPickup.ogg"))
	{
		cout << "Could not load Item pikcup sound" << endl;
	}
	mPickupItemSound.setBuffer(mBuffer);
>>>>>>> refs/remotes/origin/master
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
	//std::cout << "Mouse Pressed" << std::endl;
	//std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	//std::cout << "mouse y: " << event.mouseButton.y << std::endl;

	//std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
	//std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;

	//sf::Vector2f point(mWorldPos.x, mWorldPos.y);

	////Check if playrect collision
	//if (checkCollision(mLHandler->getActiveLevel()->getPlayRects(), point))
	//{
	//	mLHandler->getPlayer()->moveToPosition(point.x, point.y);
	//	mItemInteraction = false;
	//}

	////Check Item collision
	////Loop through all Items in active level
	//for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveItems().size(); i++)
	//{
	//	//Check if mouse collided with Item
	//	if (checkCollision(mLHandler->getActiveItems()[i]->getRectangle(), point))
	//	{
	//		//Check if Item is Active
	//		if (mLHandler->getActiveItems()[i]->getActive())
	//		{
	//			//Check Id of that Item
	//			if (mLHandler->getActiveItems()[i]->getId() == "Cube")
	//			{
	//				//Move Player to the closest point that is still inside the playrect
	//				mLHandler->getPlayer()->moveToPosition(340, 370);
	//				//Set the Item as "Target Item"
	//				mTargetItem = mLHandler->getActiveItems()[i];
	//				//Enable Item interaction
	//				mItemInteraction = true;
	//			}
	//			if (mLHandler->getActiveItems()[i]->getId() == "Magnet")
	//			{
	//				mLHandler->getPlayer()->moveToPosition(340, 370);
	//				mTargetItem = mLHandler->getActiveItems()[i];
	//				mItemInteraction = true;
	//			}
	//			if (mLHandler->getActiveItems()[i]->getId() == "Bowl")
	//			{
	//				mLHandler->getPlayer()->moveToPosition(340, 370);
	//				mTargetItem = mLHandler->getActiveItems()[i];
	//				mItemInteraction = true;
	//			}
	//			if (mLHandler->getActiveItems()[i]->getId() == "Block")
	//			{
	//				if (mLHandler->getActiveLevel()->getActiveScene() == 0)
	//				{
	//					mLHandler->getPlayer()->moveToPosition(560, 365);
	//				}
	//				else
	//				{
	//					mLHandler->getPlayer()->moveToPosition(490, 500);
	//				}
	//				mTargetItem = mLHandler->getActiveItems()[i];
	//				mItemInteraction = true;
	//			}
	//			if (mLHandler->getActiveItems()[i]->getId() == "Astronaut")
	//			{
	//				if (mLHandler->getActiveLevel()->getActiveScene() == 0)
	//				{
	//					mLHandler->getPlayer()->moveToPosition(560, 365);
	//				}
	//				else
	//				{
	//					mLHandler->getPlayer()->moveToPosition(490, 500);
	//				}
	//				mTargetItem = mLHandler->getActiveItems()[i];
	//				mItemInteraction = true;
	//			}
	//			if (mLHandler->getActiveItems()[i]->getId() == "String")
	//			{
	//				mLHandler->getPlayer()->moveToPosition(340, 370);
	//				mTargetItem = mLHandler->getActiveItems()[i];
	//				mItemInteraction = true;
	//			}
	//			if (mLHandler->getActiveItems()[i]->getId() == "Star")
	//			{
	//				mLHandler->getPlayer()->moveToPosition(480, 450);
	//				mTargetItem = mLHandler->getActiveItems()[i];
	//				mItemInteraction = true;
	//			}
	//		}
	//	}
	//}

	////Check Rect Collisions
	////Separate for each level, getLevel(0) is Level1
	//if (mLHandler->getActiveLevel() == mLHandler->getLevel(0))
	//{
	//	for (Level::rectVector::size_type i = 0; i < mLHandler->getActiveLevel()->getRects().size(); i++)
	//	{
	//		if (checkCollision(mLHandler->getActiveLevel()->getRects()[i], point))
	//		{
	//			// i == 0 is the fishtankplace, or Thomas Room if in fishtankplace
	//			if (i == 0)
	//			{
	//				if (mLHandler->getActiveLevel()->getActiveScene() == 0)
	//				{
	//					//Make Player get into position for Scene change
	//					mLHandler->getPlayer()->moveToPosition(400, 370);
	//					//Set Collision Rect to Scene change position
	//					mSceneChangeRect = sf::FloatRect(sf::Vector2f(400, 370), sf::Vector2f(10, 10));
	//					//Set if Player should toggle on Scene Change
	//					mPlayerToggle = true;
	//					//Set starting position of Player in new Scene
	//					mSceneChangePlayerPos = sf::Vector2f(150, 480);
	//					//Set which Scene will be the new Scene
	//					mNewScene = 1;
	//				}
	//				else
	//				{
	//					//Make Player get into position for Scene change
	//					mLHandler->getPlayer()->moveToPosition(150, 480);
	//					//Set Collision Rect to Scene change position
	//					mSceneChangeRect = sf::FloatRect(sf::Vector2f(150, 480), sf::Vector2f(10, 10));
	//					//Set if Player should toggle on Scene Change
	//					mPlayerToggle = true;
	//					//Set starting position of Player in new Scene
	//					mSceneChangePlayerPos = sf::Vector2f(400, 370);
	//					//Set which Scene will be the new Scene
	//					mNewScene = 0;
	//				}
	//			}
	//			// i == 1 is books in the bookcase
	//			else if (i == 1)
	//			{
	//				//mDialogueSystem->displayBookDialogue();
	//				std::cout << "B�cker!";
	//			}
	//			// i == 2 is lamp on table
	//			else if (i == 2)
	//			{
	//				//mDialogueSystem->displayLampDialogue();
	//				std::cout << "Lampa!";
	//			}
	//			// i == 3 is radio on table
	//			else if (i == 3)
	//			{
	//				//mDialogueSystem->displayRadioDialogue();
	//				std::cout << "Radio!";
	//			}
	//			// i == 4 is posters on wall
	//			else if (i == 4)
	//			{
	//				//mDialogueSystem->displayPostersDialogue();
	//				std::cout << "Affischer!";
	//			}
	//			// i == 5 is backpack near bed
	//			else if (i == 5)
	//			{
	//				//mDialogueSystem->displayBackpackDialogue();
	//				std::cout << "Ryggs�ck! Ryggs�ck!";
	//			}
	//		}
	//	}
	//}
}

<<<<<<< HEAD
//void EventHandler::mouseClickLevel1(sf::Event &event)
=======
void EventHandler::mouseClickLevel1(sf::Event &event)
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
					std::cout << "B�cker!";
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
					std::cout << "Ryggs�ck! Ryggs�ck!";
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
				mouseClickLevel1(event);
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
					std::cout << "Sk�l!";
				}
				if (mTargetItem->getId() == "Block")
				{
					//mDialogueSystem->displayBlockDialogue();
					std::cout << "En kloss framf�r akvariet, undrar om det finns en astronaut bakom?";
				}
				if (mTargetItem->getId() == "Astronaut")
				{
					//mDialogueSystem->displayAstronautDialogue();
					std::cout << "N�men titta, en astronaut.";
				}
				if (mTargetItem->getId() == "String")
				{
					//mDialogueSystem->displayStringDialogue();
					std::cout << "En tr�d p� golvet.";
				}
				if (mTargetItem->getId() == "Star")
				{
					//mDialogueSystem->displayStarDialogue();
					std::cout << "Stj�rnklart!";
				}
			}
			//Check if Item can be picked up
			else if (mTargetItem->getPickupable())
			{
				//Make Item inactive when it is picked up
				mTargetItem->toggleActive();
				if (mTargetItem->getId() == "Magnet")
				{
					mPickupItemSound.play();
					mInventory->addItem(mTargetItem);
					std::cout << "Plockade upp magnet";
				}
				if (mTargetItem->getId() == "String")
				{
					mPickupItemSound.play();
					mInventory->addItem(mTargetItem);
					std::cout << "Plockade upp tr�d";
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
						std::cout << "Satte stj�rnan p� v�ggen";
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
=======
//#include "EventHandler.h"
//#include <iostream>
//
//EventHandler::EventHandler(LevelHandler &lHandler, DialogueSystem &dSystem):
//mLHandler(&lHandler),
//mDialogueSystem(&dSystem)
//{
//	mLHandler->setActiveLevel(0);
//}
//
//EventHandler::~EventHandler()
//{
//}
//
////Check collision with single rectangle
//int EventHandler::checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point)
//{
//	if (boundingBox.contains(point))
//	{	
//		return 1;
//	}
//	return 0;
//}
//
////Check collision with single rectangle
//int EventHandler::checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point)
//{
//	if (boundingBox->contains(point))
//	{
//		return 1;
//	}
//	return 0;
//}
//
////Check collision with multiple rectangles
//int EventHandler::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point)
//{
//	for (std::vector<sf::FloatRect*>::size_type i = 0; i < RectVector.size(); i++)
//	{
//		if (RectVector[i]->contains(point))
//		{
//			return 1;
//		}
//	}
//	return 0;
//}
//
////Mouseclick function
//void EventHandler::mouseClick(sf::Event &event)
>>>>>>> refs/remotes/origin/master
//{
//	std::cout << "Mouse Pressed" << std::endl;
//	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
//	std::cout << "mouse y: " << event.mouseButton.y << std::endl;
//
//	std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
//	std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;
//
//	sf::Vector2f point(mWorldPos.x, mWorldPos.y);
//
<<<<<<< HEAD
//	//Check if playrect collision
//	if (checkCollision(mLHandler->getActiveLevel()->getPlayRects(), point))
//	{
//		mLHandler->getPlayer()->moveToPosition(point.x, point.y);
//		mItemInteraction = false;
=======
//	//Test function. Should be used within a arrow-box (an arrow you click to continue in a dialogue)
//	mDialogueSystem->setState();
//
//	//Check collision with Player
//	if (checkCollision(mLHandler->getPlayer()->getRect(), point)) 
//	{
//		std::cout << "HIT!" << std::endl;
>>>>>>> refs/remotes/origin/master
//	}
//
//	//Check Item collision
//	//Loop through all Items in active level
<<<<<<< HEAD
//	for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveItems().size(); i++)
//	{
//		//Check if mouse collided with Item
//		if (checkCollision(mLHandler->getActiveItems()[i]->getRectangle(), point))
//		{
//			//Check if Item is Active
//			if (mLHandler->getActiveItems()[i]->getActive())
//			{
//				//Check Id of that Item
//				if (mLHandler->getActiveItems()[i]->getId() == "Cube")
//				{
//
//					//Move Player to the closest point that is still inside the playrect
//					mLHandler->getPlayer()->moveToPosition(340, 370);
//					//Set the Item as "Target Item"
//					mTargetItem = mLHandler->getActiveItems()[i];
//					//Enable Item interaction
//					mItemInteraction = true;
//
//				}
//
//				if (mLHandler->getActiveItems()[i]->getId() == "Magnet")
//				{
//					mLHandler->getPlayer()->moveToPosition(340, 370);
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//				}
//
//				if (mLHandler->getActiveItems()[i]->getId() == "Bowl")
//				{
//					mLHandler->getPlayer()->moveToPosition(340, 370);
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//				}
//
//				if (mLHandler->getActiveItems()[i]->getId() == "Block")
//
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						mLHandler->getPlayer()->moveToPosition(560, 365);
//					}
//					else
//					{
//						mLHandler->getPlayer()->moveToPosition(490, 500);
//					}
//
//
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//
//				}
//
//				if (mLHandler->getActiveItems()[i]->getId() == "Astronaut")
//
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						mLHandler->getPlayer()->moveToPosition(560, 365);
//					}
//					else
//					{
//						mLHandler->getPlayer()->moveToPosition(490, 500);
//					}
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//				}
//
//				if (mLHandler->getActiveItems()[i]->getId() == "String")
//				{
//					mLHandler->getPlayer()->moveToPosition(340, 370);
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//				}
//
//				if (mLHandler->getActiveItems()[i]->getId() == "Star")
//				{
//					mLHandler->getPlayer()->moveToPosition(480, 450);
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
=======
//	//Check if mouse collided with Item
//	//Check Id of that Item
//	//Check if Item is looked at, if not, look at it and display dialogue
//	//If Item is looked at, check if it is pickupable and if so toggle Active and add to inventory
//	for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveLevel()->getItems().size(); i++)
//	{
//		if (checkCollision(mLHandler->getActiveLevel()->getItems()[i]->getRectangle(), point))
//		{
//			if (!mLHandler->getActiveLevel()->getItems()[i]->isLookedAt())
//			{
//				//mLHandler->getActiveLevel()->getItems()[i]->toggleIsLookedAt();
//				if (mLHandler->getActiveLevel()->getItems()[i]->getId() == "Cube")
//				{
//					mDialogueSystem->reset();
//					mDialogueSystem->hasClicked("rubicCube");
//				}
//				if (mLHandler->getActiveLevel()->getItems()[i]->getId() == "Magnet")
//				{
//					mDialogueSystem->reset();
//					mDialogueSystem->hasClicked("magnet");
//				}
//			}
//			else if (mLHandler->getActiveLevel()->getItems()[i]->getPickupable())
//			{
//				mLHandler->getActiveLevel()->getItems()[i]->toggleActive(); //Change to not be a toggle?
//				if (mLHandler->getActiveLevel()->getItems()[i]->getId() == "Magnet")
//				{
//					//TODO - Add to inventory
//					std::cout << "Plockade upp magnet";
>>>>>>> refs/remotes/origin/master
//				}
//			}
//		}
//	}
<<<<<<< HEAD
//	
//
//	//Check Rect Collisions
//	//Separate for each level, getLevel(0) is Level1
//	if (mLHandler->getActiveLevel() == mLHandler->getLevel(0))
//	{
//		for (Level::rectVector::size_type i = 0; i < mLHandler->getActiveLevel()->getRects().size(); i++)
//		{
//			if (checkCollision(mLHandler->getActiveLevel()->getRects()[i], point))
//			{
//				// i == 0 is the fishtankplace, or Thomas Room if in fishtankplace
//				if (i == 0)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						//Make Player get into position for Scene change
//						mLHandler->getPlayer()->moveToPosition(400, 370);
//						//Set Collision Rect to Scene change position
//						mSceneChangeRect = sf::FloatRect(sf::Vector2f(400, 370), sf::Vector2f(10, 10));
//						//Set if Player should toggle on Scene Change
//						mPlayerToggle = true;
//						//Set starting position of Player in new Scene
//						mSceneChangePlayerPos = sf::Vector2f(150, 480);
//						//Set which Scene will be the new Scene
//						mNewScene = 1;
//					}
//					else
//					{
//						//Make Player get into position for Scene change
//						mLHandler->getPlayer()->moveToPosition(150, 480);
//						//Set Collision Rect to Scene change position
//						mSceneChangeRect = sf::FloatRect(sf::Vector2f(150, 480), sf::Vector2f(10, 10));
//						//Set if Player should toggle on Scene Change
//						mPlayerToggle = true;
//						//Set starting position of Player in new Scene
//						mSceneChangePlayerPos = sf::Vector2f(400, 370);
//						//Set which Scene will be the new Scene
//						mNewScene = 0;
//					}
//				}
//				// i == 1 is books in the bookcase
//				else if (i == 1)
//				{
//					//mDialogueSystem->displayBookDialogue();
//					std::cout << "B�cker!";
//				}
//				// i == 2 is lamp on table
//				else if (i == 2)
//				{
//					//mDialogueSystem->displayLampDialogue();
//					std::cout << "Lampa!";
//				}
//				// i == 3 is radio on table
//				else if (i == 3)
//				{
//					//mDialogueSystem->displayRadioDialogue();
//					std::cout << "Radio!";
//				}
//				// i == 4 is posters on wall
//				else if (i == 4)
//				{
//					//mDialogueSystem->displayPostersDialogue();
//					std::cout << "Affischer!";
//				}
//				// i == 5 is backpack near bed
//				else if (i == 5)
//				{
//					//mDialogueSystem->displayBackpackDialogue();
//					std::cout << "Ryggs�ck! Ryggs�ck!";
//				}
//			}
//		}
//	}
//
//	/* Template for Rect check in other levels */
//	else if (mLHandler->getActiveLevel() == mLHandler->getLevel(1))
//	{
//		for (Level::rectVector::size_type i = 0; i < mLHandler->getActiveLevel()->getRects().size(); i++)
//		{
//			if (checkCollision(mLHandler->getActiveLevel()->getRects()[i], point))
////			{
//				// i == 0 is Dollhouse if ActiveScene is 0, or Door if ActiveScene is 1, or Refrigerator if ActiveScene is 2.
//				if (i == 0)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						std::cout << "Dollhouse!";
//					}
//					else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
//					{
//						std::cout << "Door!";
//						//Make Player get into position for Scene change
//						mLHandler->getPlayer()->moveToPosition(70, 370);
//						//Set Collision Rect to Scene change position
//						mSceneChangeRect = sf::FloatRect(sf::Vector2f(70, 370), sf::Vector2f(10, 10));
//						//Set if Player should toggle on Scene Change
//						mPlayerToggle = false;
//						//Set starting position of Player in new Scene
//						mSceneChangePlayerPos = sf::Vector2f(150, 480);
//						//Set which Scene will be the new Scene
//						mNewScene = 0;
//					}
//					else
//					{
//						std::cout << "Refrigerator!";
//					}
//				}
//
//				// i == 1 is Planet 1 if ActiveScene is 0, Books if ActiveLevel is 1, Catbowl if ActiveScene is 2
//				else if (i == 1)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						std::cout << "Planet 1!";
//					}
//					else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
//					{
//						std::cout << "Books!";
//						
//					}
//					else
//					{
//						std::cout << "Catbowl!";
//					}
//					
//				}
//
//				// i == 2 is Planet 2 if ActiveScene is 0, Jewelry Box if ActiveScene is 1, Hole if ActiveSCene is 2
//				else if (i == 2)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						std::cout << "Planet 2!";
//					}
//					else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
//					{
//						std::cout << "Jewelry Box!";
//					}
//					else
//					{
//						std::cout << "Hole!";
//					}
//				}
//
//				// i == 3 is Planet 3 if ActiveScene is 0, Yarn Basket if ActiveScene is 1, Tap if ActiveScene is 2
//				else if (i == 3)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						std::cout << "Planet 3!";
//					}
//					else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
//					{
//						std::cout << "Yarn Basket!";
//					}
//					else
//					{
//						std::cout << "Tap!";
//					}
//				}
//
//				// i == 4 is Planet 4 if ActiveScene is 0, Crotch Rocket if ActiveScene is 1
//				else if (i == 4)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						std::cout << "Planet 4!";
//					}
//					else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
//					{
//						std::cout << "Crotch Rocket!";
//					}
//					else
//					{
//
//					}
//				}
//
//				// i == 5 is Planet 5 if ActiveScene is 0, Gramophone if ActiveScene is 1
//				else if (i == 5)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						std::cout << "Planet 5!";
//					}
//					else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
//					{
//						//TODO - Make the gramophone play music so the fish can fall down
//						std::cout << "Gramophone!";
//					}
//					else
//					{
//
//					}
//				}
//
//				// i == 6 is Planet 6 if ActiveScene is 0, Mask if ActiveScene is 1
//				else if (i == 6)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						std::cout << "Planet 6!";
//					}
//					else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
//					{
//						std::cout << "Mask!";
//					}
//					else
//					{
//
//					}
//				}
//
//				// i == 7 is Planet 7 if ActiveScene is 0, Stairs if ActiveScene is 1
//				else if (i == 7)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						std::cout << "Planet 7!";
//
//					}
//					else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
//					{
//						std::cout << "Stairs to Scene 3!";
//						//Make Player get into position for Scene change
//						mLHandler->getPlayer()->moveToPosition(1470, 450);
//						//Set Collision Rect to Scene change position
//						mSceneChangeRect = sf::FloatRect(sf::Vector2f(1470, 450), sf::Vector2f(10, 10));
//						//Set if Player should toggle on Scene Change
//						mPlayerToggle = false;
//						//Set starting position of Player in new Scene
//						mSceneChangePlayerPos = sf::Vector2f(920,420);
//						//Set which Scene will be the new Scene
//						mNewScene = 2;
//						
//					}
//				}
//
//				// i == 8 is Planet 8 if ActiveScene is 0, 
//				else if (i == 8)
//				{
//					std::cout << "Planet 8!";
//				}
//
//				// i == 9 is Planet 9 if ActiveScene is 0,
//				else if (i == 9)
//				{
//					std::cout << "Planet 9!";
//				}
//
//				// i == 10 is Door if ActiveScene is 0,
//				else if (i == 10)
//				{
//					std::cout << "Door!";
//				}
//
//				// i == 11 is Stairs if ActiveScene is 0,
//				else if (i == 11)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						
//						//Make Player get into position for Scene change
//						mLHandler->getPlayer()->moveToPosition(101, 349);
//						//Set Collision Rect to Scene change position
//						mSceneChangeRect = sf::FloatRect(sf::Vector2f(101, 349), sf::Vector2f(10, 10));
//						//Set if Player should toggle on Scene Change
//						mPlayerToggle = false;
//						//Set starting position of Player in new Scene
//						mSceneChangePlayerPos = sf::Vector2f(100, 400);
//						//Set which Scene will be the new Scene
//						mNewScene = 1;
//							std::cout << "Stairs to scene 2!";
//					}
//				}
//			}
=======
//
//	//Check if playrect collision
//	if (checkCollision(mLHandler->getActiveLevel()->getPlayRects(), point))
//	{
//		mLHandler->getPlayer()->moveToPosition(point.x, point.y);
//	}
//
//	//Separate for each level?
//	//Check Rect Collisions
//	for (Level::rectVector::size_type i = 0; i < mLHandler->getActiveLevel()->getRects().size(); i++)
//	{
//		if (checkCollision(mLHandler->getActiveLevel()->getRects()[i], point))
//		{
//			// i == 0 is the fishtankplace
//			if (i == 0)
//			{
//				if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//				{
//					mLHandler->getPlayer()->setPosition(150, 480);
//					mLHandler->getActiveLevel()->changeScene(1);
//				}
//				else
//				{
//					mLHandler->getActiveLevel()->changeScene(0);
//				}
//			}
//			// i == 1 is books in the bookcase
//			else if (i == 1)
//			{
//				//mDialogueSystem->displayBookDialogue();
//				std::cout << "B�cker!";
//			}
//			else if (i == 2)
//			{
//				std::cout << "Lampa!";
//			}
>>>>>>> refs/remotes/origin/master
//		}
//	}
//}
//
////Waits in background and listens for mouseclicks
//void EventHandler::eventListen(sf::RenderWindow &window)
//{
//	sf::Event event;
//	while (window.pollEvent(event))
//	{
//		switch (event.type)
//		{
//			//window closed
//		case sf::Event::Closed:
//			window.close();
//			break;
//
//			//mouse button pressed
//		case sf::Event::MouseButtonPressed:
//			// get the current mouse position in the window
//			mPixelPos = sf::Mouse::getPosition(window);
//			// convert it to world coordinates
//			mWorldPos = window.mapPixelToCoords(mPixelPos);
<<<<<<< HEAD
//			//if Inventory Mode is enabled, only check for collisions with Items in Inventory
//			if (mInventoryMode)
//			{
//				mInventory->checkCollision(mInventory->getItems(), mWorldPos);
//			}
//			else
//			{
//				mouseClickLevel1(event);
//			}
=======
//			mouseClick(event);
>>>>>>> refs/remotes/origin/master
//			break;
//
//		case sf::Event::KeyPressed:
//			if (event.key.code == sf::Keyboard::Escape)
<<<<<<< HEAD
//			{
//				window.close();
//			}
//			if (event.key.code == sf::Keyboard::I)
//			{
//				for (Level::ItemVector::size_type i = 0; i < mInventory->getItems().size(); i++)
//				{
//					std::cout << mInventory->getItemId(i) << " ";
//				}
//			}
//			if (event.key.code == sf::Keyboard::M)
//			{
//				mInventoryMode = !mInventoryMode;
//			}
//			if (event.key.code == sf::Keyboard::P)
//			{
//				mLHandler->togglePlayer();
//			}
=======
//				window.close();
>>>>>>> refs/remotes/origin/master
//			break;
//
//		default:
//			break;
//		}
//	}
//}
<<<<<<< HEAD
//
//void EventHandler::update(sf::RenderWindow &window)
//{
//	//Only do this if the level needs moving camera
//	//mLHandler->getLevel(1) is currently LastLevel, change as necessary
//	if (mLHandler->getActiveLevel() == mLHandler->getLevel(1))
//	{
//		//Scene 1 is the big, second room in LastLevel, change as necessary
//		if (mLHandler->getActiveLevel()->getActiveScene() ==1)
//		{
//			//520 is the distance the Player has to be from the left side of the level before the camera starts scrolling, change as necessary
//			//1000 is the distance the Player has to be from the right side of the level before the camera starts scrolling, change as necessary
//			//In this case the camera scrolls while the Player is between 520 and 1000.
//			if (mLHandler->getPlayer()->getPosition().x > 520 && mLHandler->getPlayer()->getPosition().x < 1000) //OBSOSBOSBOSBOSOBSO
//			{
//				//Make camera follow Player position
//				mLHandler->getActiveLevel()->moveViewWithPlayer(mLHandler->getPlayer()->getPosition().x);
//			}
//		}
//	}
//
//
//	//Check if Player is in position to change Scene
//	if (mLHandler->getPlayer()->getRect().intersects(mSceneChangeRect))
//	{
//		//Toggle Player if the new Scene needs it
//		if (mPlayerToggle)
//		{
//			mLHandler->togglePlayer();
//		}
//		//Set Player position to the starting position of the new Scene
//		mLHandler->getPlayer()->setPosition(mSceneChangePlayerPos.x, mSceneChangePlayerPos.y);
//		//Change to the new Scene
//		mLHandler->getActiveLevel()->changeScene(mNewScene);
//	}
//
//
//	//Check if Item interaction is enabled, which it only is when an Item is clicked
//	if (mItemInteraction)
//	{
//		//Check if any part of the Player intersects with the Item
//		if (mLHandler->getPlayer()->getGlobalRect().intersects(mTargetItem->getRectangle()))
//		{
//			//Check if Item has already been looked at
//			if (!mTargetItem->isLookedAt())
//			{
//				mTargetItem->toggleIsLookedAt();
//				if (mTargetItem->getId() == "Cube")
//				{
//					mDialogueSystem->displayRubicCubeDialogue();
//				}
//				if (mTargetItem->getId() == "Magnet")
//				{
//					//mDialogueSystem->displayMagnetDialogue();
//					std::cout << "Effin' magnets, how do they work!?";
//				}
//				if (mTargetItem->getId() == "Bowl")
//				{
//					//mDialogueSystem->displayBowlDialogue();
//					std::cout << "Sk�l!";
//				}
//				if (mTargetItem->getId() == "Block")
//				{
//					//mDialogueSystem->displayBlockDialogue();
//					std::cout << "En kloss framf�r akvariet, undrar om det finns en astronaut bakom?";
//				}
//				if (mTargetItem->getId() == "Astronaut")
//				{
//					//mDialogueSystem->displayAstronautDialogue();
//					std::cout << "N�men titta, en astronaut.";
//				}
//				if (mTargetItem->getId() == "String")
//				{
//					//mDialogueSystem->displayStringDialogue();
//					std::cout << "En tr�d p� golvet.";
//				}
//				if (mTargetItem->getId() == "Star")
//				{
//					//mDialogueSystem->displayStarDialogue();
//					std::cout << "Stj�rnklart!";
//				}
//				if (mTargetItem->getId() == "Magic Clam")
//				{
//					//mDialogueSystem->displayMagicClamDialogue();
//					std::cout << "Musslaaaa!";
//				}
//				if (mTargetItem->getId() == "Earth")
//				{
//					//mDialogueSystem->displayEarthDialogue();
//					std::cout << "Jordglob";
//				}
//				if (mTargetItem->getId() == "Needle")
//				{
//					//mDialogueSystem->displayNeedleDialogue();
//					std::cout << "N�l i garnkorg!";
//				}
//				if (mTargetItem->getId() == "Fish")
//				{
//					//mDialogueSystem->displayFishDialogue();
//					std::cout << "Fisk p� v�ggen!";
//				}
//			}
//			//Check if Item can be picked up
//			else if (mTargetItem->getPickupable())
//			{
//				//Make Item inactive when it is picked up
//				mTargetItem->toggleActive();
//				if (mTargetItem->getId() == "Magnet")
//				{
//					mInventory->addItem(mTargetItem);
//					std::cout << "Plockade upp magnet";
//				}
//				if (mTargetItem->getId() == "String")
//				{
//					mInventory->addItem(mTargetItem);
//					std::cout << "Plockade upp tr�d";
//				}
//				if (mTargetItem->getId() == "Earth")
//				{
//					mInventory->addItem(mTargetItem);
//					std::cout << "Plockade upp jordglob";
//				}
//				if (mTargetItem->getId() == "Needle")
//				{
//					mInventory->addItem(mTargetItem);
//					std::cout << "Plockade upp n�l";
//				}
//				if (mTargetItem->getId() == "Fish")
//				{
//					//TODO - Make the fish fall from the wall first
//					mInventory->addItem(mTargetItem);
//					std::cout << "Plockade upp fisk";
//				}
//			}
//			//Check if Item can be interacted with
//			else if (mTargetItem->getInteractable())
//			{
//				//Check if Item has already been interacted with
//				if (!mTargetItem->isInteracted())
//				{
//					mTargetItem->toggleInteractable();
//					if (mTargetItem->getId() == "Block")
//					{
//						//Move Block, TODO - change to smooth movement, set Animation to "Push" and move Player
//						mTargetItem->setPosition(630, 315);
//						mTargetItem->toggleInteracted();
//
//						//Find Astronaut in ItemVector and make it active
//						for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveItems().size(); i++)
//							{
//							if (mLHandler->getActiveItems()[i]->getId() == "Astronaut")
//							{
//								mLHandler->getActiveItems()[i]->toggleActive();
//							}
//						}
//
//						std::cout << "Knuffade Klossen";
//					}
//					if (mTargetItem->getId() == "Star")
//					{
//						mTargetItem->setPosition(900, 190);
//						std::cout << "Satte stj�rnan p� v�ggen";
//					}
//				}
//			}
//			//Disable Item interaction when done
//			mItemInteraction = false;
//		}
//	}
//
//
//	//If Player is moving to the left (getDirection.x < 0) and isn't already facing left, flip Player
//	if (mLHandler->getPlayer()->getDirection().x < 0 && !mLHandler->getPlayer()->isFacingLeft())
//	{
//		mLHandler->getPlayer()->flipPlayer();
//	}
//	//If Player is moving to the right (getDirection.x > 0) and is facing left, flip Player
//	if (mLHandler->getPlayer()->getDirection().x > 0 && mLHandler->getPlayer()->isFacingLeft())
//	{
//		mLHandler->getPlayer()->flipPlayer();
//	}
//
//
//	//Inventory
//	mInventory->update(window);
//	if (mInventoryMode)
//	{
//		mInventory->draw(window);
//	}
//}
//=======
=======

>>>>>>> refs/remotes/origin/master
//#include "EventHandler.h"
//#include <iostream>
//
//EventHandler::EventHandler(LevelHandler &lHandler):
//mLHandler(&lHandler)
//{
//	mLHandler->setActiveLevel(0); //Change back!
//	mInventory = new Inventory();
//	mItemInteraction = false;
//	mInventoryMode = false;
//}
//
//EventHandler::~EventHandler()
//{
//}
//
////Check collision between single rectangle and point
//int EventHandler::checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point)
//{
//	if (boundingBox.contains(point))
//	{	
//		return 1;
//	}
//	return 0;
//}
//
////Check collision between single rectangle pointer and point
//int EventHandler::checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point)
//{
//	if (boundingBox->contains(point))
//	{
//		return 1;
//	}
//	return 0;
//}
//
////Check collision between a vector of rectangles and a point
//int EventHandler::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point)
//{
//	for (std::vector<sf::FloatRect*>::size_type i = 0; i < RectVector.size(); i++)
//	{
//		if (RectVector[i]->contains(point))
//		{
//			return 1;
//		}
//	}
//	return 0;
//}
//
////Mouseclick function
//void EventHandler::mouseClick(sf::Event &event)
//{
//	std::cout << "Mouse Pressed" << std::endl;
//	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
//	std::cout << "mouse y: " << event.mouseButton.y << std::endl;
//
//	std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
//	std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;
//
//	sf::Vector2f point(mWorldPos.x, mWorldPos.y);
//
//	//Check if playrect collision
//	if (checkCollision(mLHandler->getActiveLevel()->getPlayRects(), point))
//	{
//		mLHandler->getPlayer()->moveToPosition(point.x, point.y);
//		mItemInteraction = false;
//	}
//
//	//Check Item collision
//	//Loop through all Items in active level
//	for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveItems().size(); i++)
//	{
//		//Check if mouse collided with Item
//		if (checkCollision(mLHandler->getActiveItems()[i]->getRectangle(), point))
//		{
//			//Check if Item is Active
//			if (mLHandler->getActiveItems()[i]->getActive())
//			{
//				//Check Id of that Item
//				if (mLHandler->getActiveItems()[i]->getId() == "Cube")
//				{
//					//Move Player to the closest point that is still inside the playrect
//					mLHandler->getPlayer()->moveToPosition(340, 370);
//					//Set the Item as "Target Item"
//					mTargetItem = mLHandler->getActiveItems()[i];
//					//Enable Item interaction
//					mItemInteraction = true;
//				}
//				if (mLHandler->getActiveItems()[i]->getId() == "Magnet")
//				{
//					mLHandler->getPlayer()->moveToPosition(340, 370);
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//				}
//				if (mLHandler->getActiveItems()[i]->getId() == "Bowl")
//				{
//					mLHandler->getPlayer()->moveToPosition(340, 370);
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//				}
//				if (mLHandler->getActiveItems()[i]->getId() == "Block")
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						mLHandler->getPlayer()->moveToPosition(560, 365);
//					}
//					else
//					{
//						mLHandler->getPlayer()->moveToPosition(490, 500);
//					}
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//				}
//				if (mLHandler->getActiveItems()[i]->getId() == "Astronaut")
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						mLHandler->getPlayer()->moveToPosition(560, 365);
//					}
//					else
//					{
//						mLHandler->getPlayer()->moveToPosition(490, 500);
//					}
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//				}
//				if (mLHandler->getActiveItems()[i]->getId() == "String")
//				{
//					mLHandler->getPlayer()->moveToPosition(340, 370);
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//				}
//				if (mLHandler->getActiveItems()[i]->getId() == "Star")
//				{
//					mLHandler->getPlayer()->moveToPosition(480, 450);
//					mTargetItem = mLHandler->getActiveItems()[i];
//					mItemInteraction = true;
//				}
//			}
//		}
//	}
//
//	//Check Rect Collisions
//	//Separate for each level, getLevel(0) is Level1
//	if (mLHandler->getActiveLevel() == mLHandler->getLevel(0))
//	{
//		for (Level::rectVector::size_type i = 0; i < mLHandler->getActiveLevel()->getRects().size(); i++)
//		{
//			if (checkCollision(mLHandler->getActiveLevel()->getRects()[i], point))
//			{
//				// i == 0 is the fishtankplace, or Thomas Room if in fishtankplace
//				if (i == 0)
//				{
//					if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//					{
//						//Make Player get into position for Scene change
//						mLHandler->getPlayer()->moveToPosition(400, 370);
//						//Set Collision Rect to Scene change position
//						mSceneChangeRect = sf::FloatRect(sf::Vector2f(400, 370), sf::Vector2f(10, 10));
//						//Set if Player should toggle on Scene Change
//						mPlayerToggle = true;
//						//Set starting position of Player in new Scene
//						mSceneChangePlayerPos = sf::Vector2f(150, 480);
//						//Set which Scene will be the new Scene
//						mNewScene = 1;
//					}
//					else
//					{
//						//Make Player get into position for Scene change
//						mLHandler->getPlayer()->moveToPosition(150, 480);
//						//Set Collision Rect to Scene change position
//						mSceneChangeRect = sf::FloatRect(sf::Vector2f(150, 480), sf::Vector2f(10, 10));
//						//Set if Player should toggle on Scene Change
//						mPlayerToggle = true;
//						//Set starting position of Player in new Scene
//						mSceneChangePlayerPos = sf::Vector2f(400, 370);
//						//Set which Scene will be the new Scene
//						mNewScene = 0;
//					}
//				}
//				// i == 1 is books in the bookcase
//				else if (i == 1)
//				{
//					//mDialogueSystem->displayBookDialogue();
//					std::cout << "B�cker!";
//				}
//				// i == 2 is lamp on table
//				else if (i == 2)
//				{
//					//mDialogueSystem->displayLampDialogue();
//					std::cout << "Lampa!";
//				}
//				// i == 3 is radio on table
//				else if (i == 3)
//				{
//					//mDialogueSystem->displayRadioDialogue();
//					std::cout << "Radio!";
//				}
//				// i == 4 is posters on wall
//				else if (i == 4)
//				{
//					//mDialogueSystem->displayPostersDialogue();
//					std::cout << "Affischer!";
//				}
//				// i == 5 is backpack near bed
//				else if (i == 5)
//				{
//					//mDialogueSystem->displayBackpackDialogue();
//					std::cout << "Ryggs�ck! Ryggs�ck!";
//				}
//			}
//		}
//	}
//
//	/* Template for Rect check in other levels */
//	//else if (mLHandler->getActiveLevel() == mLHandler->getLevel(1))
//	//{
//	//	for (Level::rectVector::size_type i = 0; i < mLHandler->getActiveLevel()->getRects().size(); i++)
//	//	{
//	//		if (checkCollision(mLHandler->getActiveLevel()->getRects()[i], point))
//	//		{
//	//			// i == 0 is ____ if ActiveScene is 0, or ___ if ActiveScene is 1, etc.
//	//			if (i == 0)
//	//			{
//	//				if (mLHandler->getActiveLevel()->getActiveScene() == 0)
//	//				{
//	//					//Do stuff here
//	//				}
//	//				else if (mLHandler->getActiveLevel()->getActiveScene() == 1)
//	//				{
//	//					//Do stuff here
//	//				}
//	//				else
//	//				{
//	//					//Do stuff here
//	//				}
//	//			}
//	//			// i == 1 is ____
//	//			else if (i == 1)
//	//			{
//	//				std::cout << "Insert stuff here";
//	//			}
//	//			// i == 2 is ____
//	//			else if (i == 2)
//	//			{
//	//				std::cout << "Insert stuff here";
//	//			}
//	//			// i == 3 is ____
//	//			else if (i == 3)
//	//			{
//	//				std::cout << "Insert stuff here";
//	//			}
//	//			// i == 4 is ____
//	//			else if (i == 4)
//	//			{
//	//				std::cout << "Insert stuff here";
//	//			}
//	//			// i == 5 is ____
//	//			else if (i == 5)
//	//			{
//	//				std::cout << "Insert stuff here";
//	//			}
//	//		}
//	//	}
//	//}
//}
//
////Waits in background and listens for mouseclicks
//void EventHandler::eventListen(sf::RenderWindow &window)
//{
//	sf::Event event;
//	while (window.pollEvent(event))
//	{
//		switch (event.type)
//		{
//			//window closed
//		case sf::Event::Closed:
//			window.close();
//			break;
//
//			//mouse button pressed
//		case sf::Event::MouseButtonPressed:
//			// get the current mouse position in the window
//			mPixelPos = sf::Mouse::getPosition(window);
//			// convert it to world coordinates
//			mWorldPos = window.mapPixelToCoords(mPixelPos);
//			//if Inventory Mode is enabled, only check for collisions with Items in Inventory
//			if (mInventoryMode)
//			{
//				mInventory->checkCollision(mInventory->getItems(), mWorldPos);
//			}
//			else
//			{
//				mouseClick(event);
//			}
//			break;
//
//		case sf::Event::KeyPressed:
//			if (event.key.code == sf::Keyboard::Escape)
//			{
//				window.close();
//			}
//			if (event.key.code == sf::Keyboard::I)
//			{
//				for (Level::ItemVector::size_type i = 0; i < mInventory->getItems().size(); i++)
//				{
//					std::cout << mInventory->getItemId(i) << " ";
//				}
//			}
//			if (event.key.code == sf::Keyboard::M)
//			{
//				mInventoryMode = !mInventoryMode;
//			}
//			if (event.key.code == sf::Keyboard::P)
//			{
//				mLHandler->togglePlayer();
//			}
//			break;
//
//		default:
//			break;
//		}
//	}
//}
//
//void EventHandler::update(sf::RenderWindow &window)
//{
	////Only do this if the level needs moving camera
	////mLHandler->getLevel(1) is currently LastLevel, change as necessary
	//if (mLHandler->getActiveLevel() == mLHandler->getLevel(1))
	//{
	//	//Scene 1 is the big, second room in LastLevel, change as necessary
	//	if (mLHandler->getActiveLevel()->getActiveScene() == 1)
	//	{
	//		//520 is the distance the Player has to be from the left side of the level before the camera starts scrolling, change as necessary
	//		//1000 is the distance the Player has to be from the right side of the level before the camera starts scrolling, change as necessary
	//		//In this case the camera scrolls while the Player is between 520 and 1000.
	//		if (mLHandler->getPlayer()->getPosition().x > 520 && mLHandler->getPlayer()->getPosition().x < 1000)
	//		{
	//			//Make camera follow Player position
	//			mLHandler->getActiveLevel()->moveViewWithPlayer(mLHandler->getPlayer()->getPosition().x);
	//		}
	//	}
	//}

//
//	//Check if Player is in position to change Scene
//	if (mLHandler->getPlayer()->getRect().intersects(mSceneChangeRect))
//	{
//		//Toggle Player if the new Scene needs it
//		if (mPlayerToggle)
//		{
//			mLHandler->togglePlayer();
//		}
//		//Set Player position to the starting position of the new Scene
//		mLHandler->getPlayer()->setPosition(mSceneChangePlayerPos.x, mSceneChangePlayerPos.y);
//		//Change to the new Scene
//		mLHandler->getActiveLevel()->changeScene(mNewScene);
//	}
//
//
//	//Check if Item interaction is enabled, which it only is when an Item is clicked
//	if (mItemInteraction)
//	{
//		//Check if any part of the Player intersects with the Item
//		if (mLHandler->getPlayer()->getGlobalRect().intersects(mTargetItem->getRectangle()))
//		{
//			//Check if Item has already been looked at
//			if (!mTargetItem->isLookedAt())
//			{
//				mTargetItem->toggleIsLookedAt();
//				if (mTargetItem->getId() == "Cube")
//				{
//					mDialogueSystem->displayRubicCubeDialogue();
//				}
//				if (mTargetItem->getId() == "Magnet")
//				{
//					//mDialogueSystem->displayMagnetDialogue();
//					std::cout << "Effin' magnets, how do they work!?";
//				}
//				if (mTargetItem->getId() == "Bowl")
//				{
//					//mDialogueSystem->displayBowlDialogue();
//					std::cout << "Sk�l!";
//				}
//				if (mTargetItem->getId() == "Block")
//				{
//					//mDialogueSystem->displayBlockDialogue();
//					std::cout << "En kloss framf�r akvariet, undrar om det finns en astronaut bakom?";
//				}
//				if (mTargetItem->getId() == "Astronaut")
//				{
//					//mDialogueSystem->displayAstronautDialogue();
//					std::cout << "N�men titta, en astronaut.";
//				}
//				if (mTargetItem->getId() == "String")
//				{
//					//mDialogueSystem->displayStringDialogue();
//					std::cout << "En tr�d p� golvet.";
//				}
//				if (mTargetItem->getId() == "Star")
//				{
//					//mDialogueSystem->displayStarDialogue();
//					std::cout << "Stj�rnklart!";
//				}
//			}
//			//Check if Item can be picked up
//			else if (mTargetItem->getPickupable())
//			{
//				//Make Item inactive when it is picked up
//				mTargetItem->toggleActive();
//				if (mTargetItem->getId() == "Magnet")
//				{
//					mInventory->addItem(mTargetItem);
//					std::cout << "Plockade upp magnet";
//				}
//				if (mTargetItem->getId() == "String")
//				{
//					mInventory->addItem(mTargetItem);
//					std::cout << "Plockade upp tr�d";
//				}
//			}
//			//Check if Item can be interacted with
//			else if (mTargetItem->getInteractable())
//			{
//				//Check if Item has already been interacted with
//				if (!mTargetItem->isInteracted())
//				{
//					mTargetItem->toggleInteractable();
//					if (mTargetItem->getId() == "Block")
//					{
//						//Move Block, TODO - change to smooth movement, set Animation to "Push" and move Player
//						mTargetItem->setPosition(630, 315);
//						mTargetItem->toggleInteracted();
//
//						//Find Astronaut in ItemVector and make it active
//						for (Level::ItemVector::size_type i = 0; i < mLHandler->getActiveItems().size(); i++)
//							{
//							if (mLHandler->getActiveItems()[i]->getId() == "Astronaut")
//							{
//								mLHandler->getActiveItems()[i]->toggleActive();
//							}
//						}
//
//						std::cout << "Knuffade Klossen";
//					}
//					if (mTargetItem->getId() == "Star")
//					{
//						mTargetItem->setPosition(900, 190);
//						std::cout << "Satte stj�rnan p� v�ggen";
//					}
//				}
//			}
//			//Disable Item interaction when done
//			mItemInteraction = false;
//		}
//	}
//
//
//	//If Player is moving to the left (getDirection.x < 0) and isn't already facing left, flip Player
//	if (mLHandler->getPlayer()->getDirection().x < 0 && !mLHandler->getPlayer()->isFacingLeft())
//	{
//		mLHandler->getPlayer()->flipPlayer();
//	}
//	//If Player is moving to the right (getDirection.x > 0) and is facing left, flip Player
//	if (mLHandler->getPlayer()->getDirection().x > 0 && mLHandler->getPlayer()->isFacingLeft())
//	{
//		mLHandler->getPlayer()->flipPlayer();
//	}
//
//
//	//Inventory
//	mInventory->update(window);
//	if (mInventoryMode)
//	{
//		mInventory->draw(window);
//	}
//}
<<<<<<< HEAD
=======
>>>>>>> refs/remotes/origin/master
>>>>>>> refs/remotes/origin/master
