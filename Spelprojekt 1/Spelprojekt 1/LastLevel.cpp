#include "LastLevel.h"

LastLevel::LastLevel(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false)
{

	//Background Texture scene 1
	background.setSize(sf::Vector2f(1024,576));  
	background.setTexture(handler.getTexture("flickrum.png")); //Add correct texture

	//Playground Texture scene 1

	//Foreground Texture scene 1

	//Background Texture scene 2
	background2.setSize(sf::Vector2f(1536, 576));
	background2.setTexture(handler.getTexture("Barn hem.png")); //Add correct texture

	//Playground Texture scene 2

	//Foreground Texture scene 2

	//Background Texture scene 3
	background3.setSize(sf::Vector2f(1024, 576));
	background3.setTexture(handler.getTexture("Barnhem_Scene3.jpg")); //Add correct texture

	//Playground Texture scene 3

	//Foreground Texture scene 3

	//Add sound
	music.openFromFile("Level1Music.ogg");

	//Add HelpRect
	rectangle.setPosition(sf::Vector2f(1158, 2));
	rectangle.setSize(sf::Vector2f(70, 168));
	rectangle.setTexture(handler.getTexture("LastLevel_ItemTest1.png"));
	
	//Add items
	
	mMagicClam = new Item(handler, sf::Vector2f(0,0), "Magic Clam");
	mNeedle = new Item(handler, sf::Vector2f(271, 255), "Needle");
	mEarth = new Item(handler, sf::Vector2f(286, 122), "Earth");
	mFish = new Item(handler, sf::Vector2f(840, 37), "Fish");
	mGramophone = new Item(handler, sf::Vector2f(437, 108), "Gramophone");
	mHoolaHoop = new Item(handler, sf::Vector2f(0, 0), "Hoola Hoop");
	mBeigeBall = new Item(handler, sf::Vector2f(0, 0), "Beige Ball");
	mFruitbowl = new Item(handler, sf::Vector2f(674, 210), "Fruitbowl");
	mRedApple = new Item(handler, sf::Vector2f(0, 0), "Red Apple");
	mCat = new Item(handler, sf::Vector2f(250, 380), "Cat");
	

	//View
	mView.setSize(1024, 576);

	//Player
	mPlayer = new Player(handler, sf::Vector2f(400, 400));

	//Inventory
	mInventory = new Inventory();

	
}

LastLevel::~LastLevel()
{
	mRects.clear();
	mPlayRects.clear();
}


LastLevel::ItemVector LastLevel::getItems()
{
	return mItems;
}


void LastLevel::addItem(Item *item)
{
	mItems.push_back(item);
}


void LastLevel::removeItem(Item *item)
{
	if (mItems.size() > 1)
	{
		for (ItemVector::size_type i = 0; i < mItems.size(); i++)
		{
			if (item->getId() == mItems[i]->getId())
			{
				std::swap(mItems[i], mItems.back());
				mItems.pop_back();
				break;
			}
		}
	}
}

Player* LastLevel::getPlayer()
{
	return mPlayer;
}


void LastLevel::playBackgroundMusic()
{
	
	music.play();
}


void LastLevel::playAmbience()
{
	ambientSound.play();
}


void LastLevel::drawBackground(sf::RenderWindow &window)
{
	window.setView(mView);
	if (mActiveScene == 0)
	{
		mView.setCenter(512, 288);
		window.draw(background);

	}

	else if (mActiveScene == 1)
	{
		
		window.draw(background2);
	
		
	}
	else if (mActiveScene == 2)
	{
		mView.setCenter(512, 288);
		window.draw(background3);
	}
	//window.draw(rectangle);
	drawItems(mItems, window);
	
}

void LastLevel::drawForeground(sf::RenderWindow &window)
{
	if (mInventoryMode)
	{
		mInventory->draw(window);
	}
}


void LastLevel::drawItems(ItemVector items, sf::RenderWindow &window)
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		if (mItems[i]->getActive())
		{
			mItems[i]->draw(window);

		}
	}
}


void LastLevel::removeRect(int index)
{
	//std::swap(mRects[index], mRects.back()); 
}


const Level::rectVector LastLevel::getPlayRects()
{
	return mPlayRects;
}

void LastLevel::addRect(sf::FloatRect *rect)
{

}


void LastLevel::toggleActive()
{
	if (!mIsActive)
	{
		//Rectangles

		//Dollhouse
		mRects.push_back(createRect(193, 257, 150, 100));

		//Planets 1-9
		mRects.push_back(createRect(243, 44, 25, 25));
		mRects.push_back(createRect(317, 52, 40, 40));
		mRects.push_back(createRect(395, 47, 25, 25));
		mRects.push_back(createRect(458, 42, 23, 23));
		mRects.push_back(createRect(518, 38, 70, 70));
		mRects.push_back(createRect(620, 50, 30, 30));
		mRects.push_back(createRect(680, 55, 28, 28));
		mRects.push_back(createRect(742, 55, 28, 28));
		mRects.push_back(createRect(797, 56, 13, 13));

		//Door
		mRects.push_back(createRect(445, 186, 80, 50));

		//Stairs to scene 2
		mRects.push_back(createRect(0, 70, 108, 350));

		//Playground
		mPlayRects.push_back(createRect(108, 378, 610, 192));
		mPlayRects.push_back(createRect(347, 324, 370, 52));
		

		//Add items to itemVector
		addItem(mMagicClam);
		

	}

	mIsActive = !mIsActive;
}


bool LastLevel::isActive()
{
	return mIsActive;
}

sf::View LastLevel::getView()
{
	return mView;
}

void LastLevel::moveViewWithPlayer(float playerPos)
{
	mView.setCenter(playerPos, 288);
}

void LastLevel::clearScene()
{
	mRects.clear();
	mPlayRects.clear();
	mItems.clear();
}


void LastLevel::internalSwap(int num)
{
	if (num == 0)
	{
		mActiveScene = 0;

		//Walkable Area
		mPlayRects.push_back(createRect(108, 378, 610, 192));
		mPlayRects.push_back(createRect(347, 324, 370, 52));

		//Planets 1-9
		mRects.push_back(createRect(243, 44, 25, 25));
		mRects.push_back(createRect(317, 52, 40, 40));
		mRects.push_back(createRect(395, 47, 25, 25));
		mRects.push_back(createRect(458, 42, 23, 23));
		mRects.push_back(createRect(518, 38, 70, 70));
		mRects.push_back(createRect(620, 50, 30, 30));
		mRects.push_back(createRect(680, 55, 28, 28));
		mRects.push_back(createRect(742, 55, 28, 28));
		mRects.push_back(createRect(797, 56, 13, 13));

		//Dollhouse
		mRects.push_back(createRect(193, 257, 150, 100));

		//BalconyDoor
		mRects.push_back(createRect(445, 186, 80, 50));

		//Stairs to scene 2
		mRects.push_back(createRect(0, 70, 108, 350));

	}
	else if (num == 1)
	{

		mView.setCenter(1000, 288);
		//Scene 2
		mActiveScene = 1;

		//Walkable Area
		mPlayRects.push_back(createRect(100, 354, 944, 216));
		mPlayRects.push_back(createRect(1044, 440, 476, 132));

		//Door to scene 3
		mRects.push_back(createRect(0, 39, 70, 357));

		//Books
		mRects.push_back(createRect(261, 314, 82, 33));

		//Jewelry Box
		mRects.push_back(createRect(486, 314, 84, 36));

		//Crotch Rocket
		mRects.push_back(createRect(377, 249, 23, 49));


		//Mask
		mRects.push_back(createRect(1158, 2, 70, 168));

		//Stairs to scene 1
		mRects.push_back(createRect(1466, 246,44, 178));

		


		//Items Active
		mNeedle->toggleActive();
		mEarth->toggleActive();
		mGramophone->toggleActive();
		mFish->toggleActive();

		//Item Lookable
		mNeedle->toggleLookable();
		mEarth->toggleLookable();
		mFish->toggleLookable();

		//Items Pickupable
		mNeedle->togglePickupable();
		mEarth->togglePickupable();
		
		//Items Interactable
		mGramophone->toggleInteractable();

		//Add items to ItemVector
		addItem(mNeedle);
		addItem(mEarth);
		addItem(mFish);
		addItem(mGramophone);


	}
	else if (num == 2)
	{
		//Scene 3
		mActiveScene = 2;

		//Walkable Area
		mPlayRects.push_back(createRect(133, 379,799 , 189));

		//Refrigerator
		mRects.push_back(createRect(789, 105, 126, 269));

		//Catbowl
		mRects.push_back(createRect(714, 396, 54, 24));

		//Hole
		mRects.push_back(createRect(183, 346, 45, 31));

		//Tap
		mRects.push_back(createRect(352, 167, 32, 67));

		//Door
		mRects.push_back(createRect(941, 93, 83, 302));

		


		//Items active
		mCat->toggleActive();
		mFruitbowl->toggleActive();

		//Items Lookable
		mFruitbowl->toggleLookable();
		mCat->toggleLookable();

		//Items Interactable
		mFruitbowl->toggleInteractable();
		mCat->toggleInteractable();

		//Add Items to vector
		addItem(mHoolaHoop);
		addItem(mBeigeBall);
		addItem(mRedApple);
		addItem(mCat);
		addItem(mFruitbowl);
	}
}


void LastLevel::changeScene(int num)
{
	clearScene();
	internalSwap(num);
}


int LastLevel::getActiveScene()
{
	return mActiveScene;
}


LastLevel::rectVector LastLevel::getRects()
{
	return mRects;
}


sf::FloatRect* LastLevel::createRect(int positionX, int positionY, int sizeX, int sizeY)
{
	sf::FloatRect* floatRect = new sf::FloatRect((float)positionX, (float)positionY, (float)sizeX, (float)sizeY);
	return floatRect;
}

//Check collision between a single rectangle and a point
int LastLevel::checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point)
{
	if (boundingBox.contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a single rectangle and a point
int LastLevel::checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point)
{
	if (boundingBox->contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a point
int LastLevel::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point)
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


void LastLevel::eventListen(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// get the current mouse position in the window
		mPixelPos = sf::Mouse::getPosition(window);
		// convert it to world coordinates
		mWorldPos = window.mapPixelToCoords(mPixelPos);
		switch (event.type)
		{
			//window closed
		case sf::Event::Closed:
			window.close();
			break;

			//mouse button pressed
		case sf::Event::MouseButtonPressed:
			//if Inventory Mode is enabled, only check for collisions with Items in Inventory
			if (mInventoryMode)
			{
				mInventory->checkCollision(mInventory->getItems(), mWorldPos);
			}
			else if (!mDisableClick)
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
				mPlayer->togglePlayer();
			}
			break;

		default:
			break;
		}
	}
}


void LastLevel::mouseClick(sf::Event &event)
{
	std::cout << "Mouse Pressed" << std::endl;
	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	std::cout << "mouse y: " << event.mouseButton.y << std::endl;

	std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
	std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;

	sf::Vector2f point(mWorldPos.x, mWorldPos.y);

	//Check if playrect collision
	if (checkCollision(getPlayRects(), point))
	{
		mPlayer->setActiveAnimation("Walk");
		mPlayer->moveToPosition(point.x, point.y);
		mItemInteraction = false;
	}

	//Check Item collision
	//Loop through all Items in active level
	for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
	{
		//Check if mouse collided with Item
		if (checkCollision(getItems()[i]->getRectangle(), point))
		{
			//Check if Item is Active
			if (getItems()[i]->getActive())
			{
				mPlayer->setActiveAnimation("Walk");
				//Check Id of that Item
				if (getItems()[i]->getId() == "Gramophone")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(477, 366);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
				   std::cout << "Klickade på grammofon";

				}

				if (getItems()[i]->getId() == "Earth")
				{
					mPlayer->moveToPosition(323, 368);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på jordglob";
				}

				if (getItems()[i]->getId() == "Fish")
				{
					mPlayer->moveToPosition(930, 365);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på fisk";
				}

				if (getItems()[i]->getId() == "Needle")
				{
					
					mPlayer->moveToPosition(323, 368);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på nål";
				
				}

				if (getItems()[i]->getId() == "Astronaut")
				{
					if (getActiveScene() == 0)
					{
						mPlayer->moveToPosition(560, 365);
					}
					else
					{
						mPlayer->moveToPosition(490, 500);
					}
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				if (getItems()[i]->getId() == "String")
				{
					mPlayer->moveToPosition(340, 370);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				if (getItems()[i]->getId() == "Star")
				{
					mPlayer->moveToPosition(480, 450);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
			}
		}
	}

	//Check Rect Collisions
	//Separate for each level, getLevel(1) is LastLevel
	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], point))
		{
			mPlayer->setActiveAnimation("Walk");
			// i == 0 is Dollhouse if ActiveScene is 0, or Door if ActiveScene is 1, or Refrigerator if ActiveScene is 2.
			if (i == 0)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Dollhouse!";
					mPlayer->moveToPosition(348, 382);
				}
				else if (getActiveScene() == 1)
				{
					std::cout << "Door to scene 3!";
					//Make Player get into position for Scene change
					mPlayer->moveToPosition(70, 370);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(70, 370), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = false;
					//Set starting position of Player in new Scene
					mSceneChangePlayerPos = sf::Vector2f(950, 480);
					//Set which Scene will be the new Scene
					mNewScene = 2;
				}
				else
				{
					std::cout << "Refrigerator!";
					mPlayer->moveToPosition(870, 349);
				}
			}

			// i == 1 is Planet 1 if ActiveScene is 0, Books if ActiveLevel is 1, Catbowl if ActiveScene is 2
			else if (i == 1)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Planet 1!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1)
				{
					std::cout << "Books!";
					mPlayer->moveToPosition(356, 377);

				}
				else
				{
					std::cout << "Catbowl!";
					mPlayer->moveToPosition(816, 422);
				}

			}

			// i == 2 is Planet 2 if ActiveScene is 0, Jewelry Box if ActiveScene is 1, Hole if ActiveSCene is 2
			else if (i == 2)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Planet 2!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1)
				{
					std::cout << "Jewelry Box!";
					mPlayer->moveToPosition(591, 391);
				}
				else
				{
					std::cout << "Hole!";
					mPlayer->moveToPosition(248, 386);
				}
			}

			// i == 3 is Planet 3 if ActiveScene is 0, Yarn Basket if ActiveScene is 1, Tap if ActiveScene is 2
			else if (i == 3)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Planet 3!";
				    mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1)
				{
					std::cout << "Crotch Rocket!";
					mPlayer->moveToPosition(452, 379);
				}
				else
				{
					std::cout << "Tap!";
					mPlayer->moveToPosition(419, 388);
				}
			}

			// i == 4 is Planet 4 if ActiveScene is 0, Crotch Rocket if ActiveScene is 1, Door scene 3
			else if (i == 4)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Planet 4!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1)
				{
					std::cout << "Mask!";
					mPlayer->moveToPosition(1263, 458);
				}
				else
				{
					std::cout << "Door to scene 2!";
					//Make Player get into position for Scene change
					mPlayer->moveToPosition(950, 480);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(950, 480), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = false;
					//Set starting position of Player in new Scene
					mSceneChangePlayerPos = sf::Vector2f(70, 370);
					//Set which Scene will be the new Scene
					mNewScene = 1;
				}
			}

			// i == 5 is Planet 5 if ActiveScene is 0, Gramophone if ActiveScene is 1
			else if (i == 5)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Planet 5!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1)
				{
					std::cout << "Stairs to Scene 1!";
					//Make Player get into position for Scene change
					mPlayer->moveToPosition(1470, 450);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(1470, 450), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = false;
					//Set starting position of Player in new Scene
					mSceneChangePlayerPos = sf::Vector2f(101, 349);
					//Set which Scene will be the new Scene
					mNewScene = 0;
				}
				else
				{

				}
			}

			// i == 6 is Planet 6 if ActiveScene is 0, Mask if ActiveScene is 1
			else if (i == 6)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Planet 6!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1)
				{
					
				}
				else
				{

				}
			}

			// i == 7 is Planet 7 if ActiveScene is 0, Stairs if ActiveScene is 1
			else if (i == 7)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Planet 7!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1)
				{
					

				}
			}

			// i == 8 is Planet 8 if ActiveScene is 0, 
			else if (i == 8)
			{
				std::cout << "Planet 8!";
				mPlayer->moveToPosition(535, 437);
			}

			// i == 9 is Planet 9 if ActiveScene is 0,
			else if (i == 9)
			{
				std::cout << "Planet 9!";
				mPlayer->moveToPosition(535, 437);
			}

			// i == 10 is Door if ActiveScene is 0,
			else if (i == 10)
			{
				std::cout << "BalconyDoor!";
				mPlayer->moveToPosition(496, 334);
			}

			// i == 11 is Stairs if ActiveScene is 0,
			else if (i == 11)
			{
				if (getActiveScene() == 0)
				{

					//Make Player get into position for Scene change
					mPlayer->moveToPosition(101, 349);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(101, 349), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = false;
					//Set starting position of Player in new Scene
					mSceneChangePlayerPos = sf::Vector2f(1437, 440);
					//Set which Scene will be the new Scene
					mNewScene = 1;
					std::cout << "Stairs to scene 2!";
				}

			
			}
		}
	}
	}



void LastLevel::update(sf::RenderWindow &window, float deltaTime)
{

	//Only do this if the level needs moving camera
	//mLHandler->getLevel(1) is currently LastLevel, change as necessary
	
		//Scene 1 is the big, second room in LastLevel, change as necessary
		if (getActiveScene() == 1)
		{
			//520 is the distance the Player has to be from the left side of the level before the camera starts scrolling, change as necessary
			//1000 is the distance the Player has to be from the right side of the level before the camera starts scrolling, change as necessary
			//In this case the camera scrolls while the Player is between 520 and 1000.
			if (mPlayer->getPosition().x > 520 && mPlayer->getPosition().x < 1000)
			{
				//Make camera follow Player position
				moveViewWithPlayer(mPlayer->getPosition().x);
			}
		}
	


	//Check if Player is in position to change Scene
	if (mPlayer->getRect().intersects(mSceneChangeRect))
	{
		//Toggle Player if the new Scene needs it
		if (mPlayerToggle)
		{
			mPlayer->togglePlayer();
		}
		//Set Player position to the starting position of the new Scene
		mPlayer->setPosition(mSceneChangePlayerPos.x, mSceneChangePlayerPos.y);
		mPlayer->moveToPosition(mSceneChangePlayerPos.x, mSceneChangePlayerPos.y);
		//Change to the new Scene
		changeScene(mNewScene);
	}

	//Check if Item interaction is enabled, which it only is when an Item is clicked
	if (mItemInteraction)
	{
		//Check if any part of the Player intersects with the Item
		if (mPlayer->getGlobalRect().intersects(mTargetItem->getRectangle()))
		{
			//Check if Item has already been looked at
			if (!mTargetItem->isLookedAt())
			{
				mTargetItem->toggleIsLookedAt(); //Fixa dialoger i funktion
				mItemInteraction = false;
			}
			//Check if Item can be picked up
			else if (mTargetItem->getPickupable())
			{
				//Make Item inactive when it is picked up
				mTargetItem->toggleActive();

				if (mTargetItem->getId() == "Magic Clam")         //Ska den va här?
				{
					mInventory->addItem(mTargetItem);
					std::cout << "Musslaaaa!";
				}
				if (mTargetItem->getId() == "Earth")
				{
					mInventory->addItem(mTargetItem);
					std::cout << "Jordglob";
				}
				if (mTargetItem->getId() == "Needle")       
				{
					mInventory->addItem(mTargetItem);
					std::cout << "Nål i garnkorg!";
				}
				if (mTargetItem->getId() == "Fish")
				{
					mInventory->addItem(mTargetItem);

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
						mDisableClick = true;

						mPlayer->setSpeed(50.0f);
						mTargetItem->setSpeed(50.0f);

						mPlayer->setActiveAnimation("Push");
						mPlayer->moveToPosition(615, 500);

						mTargetItem->moveToPosition(860, 315);
						mTargetItem->toggleInteracted();

						//Find Astronaut in ItemVector and make it active
						for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
						{
							if (getItems()[i]->getId() == "Astronaut")
							{
								getItems()[i]->toggleActive();
							}
						}

						std::cout << "Knuffade Klossen";
					}

					if (mTargetItem->getId() == "Star")
					{
						mTargetItem->setPosition(900, 190);
						std::cout << "Satte stjärnan på väggen";
					}

					if (mTargetItem->getId() == "Gramophone")
					{
						
						//Play sound! Fixa ordning senare
						for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
						{
							if (getItems()[i]->getId() == "Fish")
							{
								getItems()[i]->togglePickupable();
								getItems()[i]->moveToPosition(0, 0);

							}
						}

						std::cout << "Spelar ljud, fisk ramlar ner";
					}

				}
			}
			//Disable Item interaction when done
			mItemInteraction = false;
		}
	}
	

	////If Player is moving to the left (getDirection.x < 0) and isn't already facing left, flip Player
	//if (mPlayer->getDirection().x < 0 && !mPlayer->isFacingLeft())
	//{
	//	mPlayer->flipPlayer();
	//}
	////If Player is moving to the right (getDirection.x > 0) and is facing left, flip Player
	//if (mPlayer->getDirection().x > 0 && mPlayer->isFacingLeft())
	//{
	//	mPlayer->flipPlayer();
	//}

	//Inventory
	mInventory->update(window);

	//Only update currently "Targeted" Item to avoid having to loop through and update all Items
	if (mTargetItem != NULL)
	{
		mTargetItem->update(deltaTime);
		//Put everything back to normal after the "Pushing cutscene"
		if (mTargetItem->getIsOnPosition())
		{
			if (mDisableClick)
			{
				mDisableClick = false;
				mPlayer->setActiveAnimation("Idle");
				mPlayer->setSpeed(100.0f);
				mTargetItem->setSpeed(100.0f);
			}
		}
	}
}
}



