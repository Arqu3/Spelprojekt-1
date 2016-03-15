#include "Level3.h"


Level3::Level3(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false),
handler(handler),
mLevelComplete(false)
{
}

Level3::~Level3()
{
	mRects.clear();
	mPlayRects.clear();
}


Level3::ItemVector Level3::getItems()
{
	return mItems;
}


void Level3::addItem(Item *item)
{
	mItems.push_back(item);
}


void Level3::removeItem(Item *item)
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

Player* Level3::getPlayer()
{
	return mPlayer;
}


void Level3::playBackgroundMusic()
{

	music.play();
}


void Level3::playAmbience()
{
	ambientSound.play();
}


void Level3::drawBackground(sf::RenderWindow &window)
{
	window.setView(mView);
	if (mActiveScene == 0)
	{
		
		window.draw(background);
		//window.draw(playground);

	}

	else if (mActiveScene == 1)
	{

		window.draw(background2);
		window.draw(playground2);


	}

	else if (mActiveScene == 2)
	{
		window.draw(background3);
		window.draw(playground3);
	}

	window.draw(rectangle);
	window.draw(rectangle2);
	window.draw(rectangle3);
	window.draw(rectangle4);
	window.draw(rectangle5);
	window.draw(rectangle6);
	window.draw(rectangle7);
	window.draw(rectangle8);
	window.draw(rectangle9);
	window.draw(rectangle10);
	window.draw(rectangle11);
	window.draw(rectangle12);
	window.draw(rectangle12);
	window.draw(rectangle13);
	window.draw(rectangle14);
	window.draw(rectangle15);
	window.draw(rectangle16);
	window.draw(rectangle17);

	drawItems(mItems, window);

}

void Level3::drawForeground(sf::RenderWindow &window)
{
	if (mActiveScene == 0)
	{
		window.draw(foreground);

	}

	else if (mActiveScene == 1)
	{
		window.draw(foreground2);
	}
	else if (mActiveScene == 2)
	{
		window.draw(foreground3);
	}

	if (mInventoryMode)
	{
		mInventory->draw(window);
	}
}

void Level3::drawUI(sf::RenderWindow &window)
{
	mUI->draw(window);

	if (mUI->getState() == UI::INVENTORY)
	{
		mInventory->draw(window);
	}
	if (mCursor->getMode() == Cursor::DIALOGUE)
	{
		mDialogueSystem->drawDialogue(window);
	}

	mCursor->draw(window);
}


void Level3::drawItems(ItemVector items, sf::RenderWindow &window)
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		if (mItems[i]->getActive())
		{
			mItems[i]->draw(window);

		}
	}
}


void Level3::removeRect(int index)
{
	//std::swap(mRects[index], mRects.back()); 
}


const Level::rectVector Level3::getPlayRects()
{
	return mPlayRects;
}

void Level3::addRect(sf::FloatRect *rect)
{

}


void Level3::toggleActive(ResourceHandler &handler, sf::RenderWindow &window)
{
	if (!mIsActive)
	{
		handler.loadLevel3(window);

		//Background Texture scene 1
		background.setSize(sf::Vector2f(2048, 576));
		background.setTexture(handler.getTexture("Garden.png"));

		//Foreground Texture scene 1
		foreground.setSize(sf::Vector2f(2048, 576));
		foreground.setTexture(handler.getTexture("GardenForeground.png")); 

		//Background 2
		background2.setSize(sf::Vector2f(1511, 576));
		background2.setTexture(handler.getTexture("CabinBackground.png"));

		//Foreground 2
		foreground2.setSize(sf::Vector2f(1511, 576));
		foreground2.setTexture(handler.getTexture("CabinForeground.png"));

		//Playground 2
		playground2.setSize(sf::Vector2f(1511, 576));
		playground2.setTexture(handler.getTexture("CabinPlayground.png"));

		//Background 3
		background3.setSize(sf::Vector2f(2560, 576));
		background3.setTexture(handler.getTexture("MagicWorld.png"));


		//Add sound
		music.openFromFile("Level1Music.ogg");

		//Add HelpRect
		rectangle.setPosition(sf::Vector2f(1973, 123));
		rectangle.setSize(sf::Vector2f(73, 278));
		rectangle.setTexture(handler.getTexture("LastLevel_ItemTest1.png"));

		//Add items
		mTrimmer = new Item(handler, sf::Vector2f(341, 367), "Trimmer");
		mStick = new Item(handler, sf::Vector2f(381, 220), "Stick");
		mFlowers = new Item(handler, sf::Vector2f(156, 525), "Flowers");
		mLeash = new Item(handler, sf::Vector2f(615, 303), "Leash");
		mDog = new Item(handler, sf::Vector2f(730, 370), "Dog");
		mFlagpole = new Item(handler, sf::Vector2f(1386, 195), "Flagpole");
		mSingleFlower = new Item(handler, sf::Vector2f(1390, 265), "Singleflower");
		mLady = new Item(handler, sf::Vector2f(565, 87), "Lady");

		mClover = new Item(handler, sf::Vector2f(241, 234), "Clover");
		mSawdust = new Item(handler, sf::Vector2f(831, 254), "Sawdust");
		mNail = new Item(handler, sf::Vector2f(285, 80), "Nail"); //Plockas upp
		mFjun = new Item(handler, sf::Vector2f(1192, 52), "Fjun");
		mFeatherball = new Item(handler, sf::Vector2f(200, 343), "Featherball");
		mJack = new Item(handler, sf::Vector2f(1226, 157), "Jack");
		mCloth = new Item(handler, sf::Vector2f(169, 481), "Cloth");

		//View
		mView.setSize(1024, 576);
		mView.setCenter(512, 288);
		//Player
		mPlayer = new Player(handler, sf::Vector2f(400, 400));


		//Inventory
		mInventory = new Inventory(handler);
		mInventory->setCraftableItems(handler, 1);

		//Cursor
		mCursor = new Cursor(handler);

		//UI
		mUI = new UI(handler);



		//Rectangles
		mRects.push_back(createRect(1806, 96, 62, 74));
		mRects.push_back(createRect(1973, 123, 73, 278));

		
		//Playground
		mPlayRects.push_back(createRect(0, 360, 683, 160));

		//Item Active
		mTrimmer->toggleActive();
		mTrimmer->toggleLookable();
		mTrimmer->togglePickupable();

		mStick->toggleActive();
		mStick->toggleLookable();
		mStick->togglePickupable();

		mFlowers->toggleActive();
		mFlowers->togglePickupable();
		
		mSingleFlower->toggleInteractable();
		

		mLeash->toggleActive();
		mLeash->toggleLookable();
		mLeash->toggleInteractable();

		mDog->toggleActive();
		mDog->toggleLookable();
		mDog->toggleInteractable();

		mFlagpole->toggleActive();
		mFlagpole->toggleLookable();
		mFlagpole->toggleInteractable();

		mLady->toggleActive();
		mLady->setActiveAnimation("GardenLady");

		mClover->toggleActive();
		mClover->toggleLookable();
		mClover->togglePickupable();

		mSawdust->toggleActive();
		mSawdust->toggleLookable();
		mSawdust->togglePickupable();

		mFjun->toggleActive();
		mFjun->toggleLookable();
		mFjun->togglePickupable();

		mFeatherball->toggleActive();
		mFeatherball->toggleLookable();
		mFeatherball->togglePickupable();

		mJack->toggleActive();
		mJack->toggleLookable();
		mJack->toggleInteractable();

		mNail->toggleActive();
		mNail->toggleLookable();
		mNail->togglePickupable();

		mCloth->toggleActive();
		mCloth->toggleLookable();
		mCloth->togglePickupable();

		//Add to Itemvector
		addItem(mTrimmer);
		addItem(mStick);
		addItem(mFlowers);
		addItem(mLeash);
		addItem(mDog);
		addItem(mFlagpole);
		addItem(mSingleFlower);
		addItem(mLady);
		

		
		
		changeScene(1);
	}

	mIsActive = !mIsActive;
}


bool Level3::isActive()
{
	return mIsActive;
}

sf::View Level3::getView()
{
	return mView;
}

void Level3::moveViewWithPlayer(float playerPos)
{
	mView.setCenter(playerPos, 288);
}

void Level3::clearScene()
{
	mRects.clear();
	mPlayRects.clear();
	mItems.clear();
}


void Level3::internalSwap(int num)
{
	if (num == 0)
	{
		//Scene 1
		mActiveScene = 0;

		//Walkable Area

		//Rectangles

	}

	else if (num == 1)
	{

		mView.setCenter(524, 288);
	
		mPlayer->togglePlayer();
		mPlayer->setScale(sf::Vector2f(0.4f, 0.4f));

		//Scene 2
		mActiveScene = 1;

		//Walkable Area
		mPlayRects.push_back(createRect(96, 287, 286, 38));
		mPlayRects.push_back(createRect(382, 249, 418, 323));
		mPlayRects.push_back(createRect(800, 354, 624, 77));



		//Rectangles

		//D�rr till tr�dg�rd
		mRects.push_back(createRect(72, 106, 70, 160));

		//n�sta rum
		mRects.push_back(createRect(1432, 146, 76, 210));

		//Dialogrespons Rymdraket
		mRects.push_back(createRect(900, 67, 162, 169));

		//Dialogrespons Pensel
		mRects.push_back(createRect(1053, 423, 215, 102));

		////Knekt ?
		//mRects.push_back(createRect(1226, 157, 100, 200));


		if (mClover->getActive())
		{
			addItem(mClover);
		}
		if (mSawdust->getActive())
		{
			addItem(mSawdust);
		}
		if (mFjun->getActive())
		{
			addItem(mFjun);
		}
		if (mFeatherball->getActive())
		{
			addItem(mFeatherball);
		}
		if (mJack->getActive())
		{
			addItem(mJack);
		}
		if (mNail->getActive())
		{
			addItem(mNail);
		}
		if (mCloth->getActive())
		{
			addItem(mCloth);
		}

		mInventory->addItem(mTrimmer);

	}
	else if (num == 2)
	{
		//Scene 3
		mActiveScene = 2;

		//Walkable Area
		mPlayRects.push_back(createRect(0,0, 2048, 576));
		
		//Rectangles - (om inget annat anges: dialogrespons p� alla rektanglar)

		//Anv�nd magnetfiskare. L�gger "guldmynt" i inventory
		rectangle.setSize(sf::Vector2f(156, 78));
		rectangle.setPosition(133, 416);

		//Spelar melodi och �ndrar sprite. (se: musikpussel)
		rectangle2.setSize(sf::Vector2f(73, 85));
		rectangle2.setPosition(740, 158);

		//Spelar melodi och �ndrar sprite. Ingen dialogrespons (se: musikpussel)
		rectangle3.setSize(sf::Vector2f(47, 37));
		rectangle3.setPosition(709, 56);

		//Spelar melodi och �ndrar sprite. Ingen dialogrespons (se: musikpussel)
		rectangle4.setSize(sf::Vector2f(41, 36));
		rectangle4.setPosition(758, 30);

		//Spelar melodi och �ndrar sprite. Ingen dialogrespons (se: musikpussel)
		rectangle5.setSize(sf::Vector2f(44, 37));
		rectangle5.setPosition(804, 57);

		//Spelar melodi och �ndrar sprite. Ingen dialogrespons (se: musikpussel)
		rectangle6.setSize(sf::Vector2f(45, 34));
		rectangle6.setPosition(759, 97);

		//(kurrag�mmapussel - prata med design)
		rectangle7.setSize(sf::Vector2f(82, 42));
		rectangle7.setPosition(1067, 297);

		//(kurrag�mmapussel - prata med design)
		rectangle8.setSize(sf::Vector2f(115, 31));
		rectangle8.setPosition(1831, 257);

		//(kurrag�mmapussel - prata med design)
		rectangle9.setSize(sf::Vector2f(141, 60));
		rectangle9.setPosition(2059, 216);

		//(kurrag�mmapussel - prata med design)
		rectangle10.setSize(sf::Vector2f(108, 24));
		rectangle10.setPosition(1604, 194);

		//om pussel avklarade > klara banan. Else: dialogrespons
		rectangle11.setSize(sf::Vector2f(122, 168));
		rectangle11.setPosition(322, 102);

		//triggers various dialogs
		rectangle12.setSize(sf::Vector2f(47, 96));
		rectangle12.setPosition(2423, 232);

		//endast dialogrespons
		rectangle13.setSize(sf::Vector2f(58, 83));
		rectangle13.setPosition(611, 415);

		//triggers various dialogs
		rectangle14.setSize(sf::Vector2f(63, 85));
		rectangle14.setPosition(1495, 333);

		//endast dialogrespons
		rectangle15.setSize(sf::Vector2f(160, 232));
		rectangle15.setPosition(25, 49);

		//endast dialogrespons
		rectangle16.setSize(sf::Vector2f(129, 173));
		rectangle16.setPosition(1342, 90);

		//endast dialogrespons
		rectangle17.setSize(sf::Vector2f(173, 92));
		rectangle17.setPosition(2337, 474);

		//Real rects
		mRects.push_back(createRect(133, 416, 156, 78));
		mRects.push_back(createRect(745, 160, 73, 85));
		mRects.push_back(createRect(709, 56, 47, 37));
		mRects.push_back(createRect(753, 30, 41, 31));
		mRects.push_back(createRect(804, 57, 44, 37));
		mRects.push_back(createRect(759, 97, 45, 34));
		mRects.push_back(createRect(1067, 297, 82, 42));
		mRects.push_back(createRect(1831, 257, 115, 31));
		mRects.push_back(createRect(2059, 216, 141, 60));
		mRects.push_back(createRect(1604, 194, 108, 24));
		mRects.push_back(createRect(322, 102, 122, 168));
		mRects.push_back(createRect(2423, 232, 47, 96));
		mRects.push_back(createRect(611, 415, 58, 83));
		mRects.push_back(createRect(1495, 333, 63, 85));
		mRects.push_back(createRect(25, 49, 160, 232));
		mRects.push_back(createRect(1342, 90, 129, 175));
		mRects.push_back(createRect(2337, 474, 173, 92));
	}
}


void Level3::changeScene(int num)
{
	clearScene();
	internalSwap(num);
}


int Level3::getActiveScene()
{
	return mActiveScene;
}


Level3::rectVector Level3::getRects()
{
	return mRects;
}


sf::FloatRect* Level3::createRect(int positionX, int positionY, int sizeX, int sizeY)
{
	sf::FloatRect* floatRect = new sf::FloatRect((float)positionX, (float)positionY, (float)sizeX, (float)sizeY);
	return floatRect;
}

//Check collision between a single rectangle and a point
int Level3::checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point)
{
	if (boundingBox.contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a single rectangle and a point
int Level3::checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point)
{
	if (boundingBox->contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a point
int Level3::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point)
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

//Check collision between two rectangles
int Level3::checkCollision(sf::FloatRect* boundingBox, sf::FloatRect &rect)
{
	if (boundingBox->intersects(rect))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a rectangle
int Level3::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::FloatRect &rect)
{
	for (std::vector<sf::FloatRect*>::size_type i = 0; i < RectVector.size(); i++)
	{
		if (RectVector[i]->intersects(rect))
		{
			return 1;
		}
	}
	return 0;
}



void Level3::eventListen(sf::RenderWindow &window)
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
			if (mUI->getState() == UI::INVENTORY)
			{

				mInventory->setCraftPos(mInventory->getSelectedItem());

				if (mInventory->craftCheck())
				{
					mInventory->craftItem(mInventory->getCraftSelect1(), mInventory->getCraftSelect2());
				}

				mInventory->checkCollision(mInventory->getItems(), mWorldPos, *mUI);

			}
			else if (mCursor->getMode() == Cursor::DIALOGUE)
			{
				mDialogueSystem->setState();
			}
			else if (mUI->getState() != UI::INGAME)
			{
				mUI->checkCollision(mWorldPos);
			}
			else if (mCursor->getMode() != Cursor::DISABLED)
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
				if (mUI->getState() == UI::INVENTORY)
				{
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::NORMAL);
				}
				else
				{
					mUI->setState(UI::INVENTORY);
					mCursor->setMode(Cursor::INVENTORY);
				}
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


void Level3::mouseClick(sf::Event &event)
{
	std::cout << "Mouse Pressed" << std::endl;
	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	std::cout << "mouse y: " << event.mouseButton.y << std::endl;

	std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
	std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;

	sf::Vector2f point(mWorldPos.x, mWorldPos.y);

	//Check if Hat Icon is clicked
	if (checkCollision(mUI->getHatIconRect(), point))
	{
		mCursor->setMode(Cursor::MENU);
		mUI->setState(UI::HAT);
	}

	//Check if Menu Icon is clicked
	if (checkCollision(mUI->getMenuIconRect(), point))
	{
		mCursor->setMode(Cursor::MENU);
		mUI->setState(UI::MAINUI);
	}


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


				if (getItems()[i]->getId() == "Trimmer")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(310, 375);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� h�cksax!";

				}

				if (getItems()[i]->getId() == "Stick")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(349, 346);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� h�cksax!";

				}

				if (getItems()[i]->getId() == "Leash")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(588, 380);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� koppel!";

				}

				if (getItems()[i]->getId() == "Dog")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(666, 416);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� hunden!";

				}

				if (getItems()[i]->getId() == "Flowers")
				{
					
						//Move Player to the closest point that is still inside the playrect
						mPlayer->moveToPosition(466, 522);
						//Set the Item as "Target Item"
						mTargetItem = getItems()[i];
						//Enable Item interaction
						mItemInteraction = true;
						std::cout << "Klickade p� blommor!";
					
				}

				if (getItems()[i]->getId() == "Flagpole")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(1354, 374);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� flaggst�ng!";

				}

				if (getItems()[i]->getId() == "Singleflower")
				{
					//Move Player to the closest point that is still inside the playrect
					//mPlayer->moveToPosition(1354, 374);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� blomma!";

				}

				if (getItems()[i]->getId() == "Clover")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(338, 316);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� kl�ver!";

				}

				if (getItems()[i]->getId() == "Sawdust")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(819, 301);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� s�gsp�n!";

				}

				if (getItems()[i]->getId() == "Fjun")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(1200, 370);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� fjun!";

				}

				if (getItems()[i]->getId() == "Nail")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(424, 300);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� spik!";

				}

				if (getItems()[i]->getId() == "Featherball")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(463, 415);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� fj�derboll!";

				}

				if (getItems()[i]->getId() == "Jack")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(1250, 370);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� knekt!";

				}

				if (getItems()[i]->getId() == "Cloth")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(386, 543);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade p� knekt!";

				}

			}
		}
	}

	//Check Rect Collisions

	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], point))
		{
			mPlayer->setActiveAnimation("Walk");

			// i == 0 Bees, Door to garden, 

			if (i == 0)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Bikupa! Bzzz";
					
				}
				else if (getActiveScene() == 1)
				{
					std::cout << "Door to scene 1!";
					//Make Player get into position for Scene change
					mPlayer->moveToPosition(70, 370);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(70, 370), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = true;
					//Set starting position of Player in new Scene           FIXA!!!
					mSceneChangePlayerPos = sf::Vector2f(950, 480);
					//Set which Scene will be the new Scene
					mNewScene = 0;
					mLastScene = 1;
				}
				else
				{
					std::cout << "Refrigerator!";
					mPlayer->moveToPosition(870, 349);
				}
			}

			// Door shed, magic world
			if (i == 1)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "D�rr!";                  //Detta ska vara en annan rektangel sedan!!! OBS
					
					//Make Player get into position for Scene change
					mPlayer->moveToPosition(1973, 370);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(1973, 370), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = false;
					//Set starting position of Player in new Scene           
					mSceneChangePlayerPos = sf::Vector2f(148, 276);
					//Set which Scene will be the new Scene
					mNewScene = 1;
					mLastScene = 0;
				}
				else if (getActiveScene() == 1)
				{

				}
			}


			//Rocket
			if (i == 2)
			{
				if (getActiveScene() == 1)
				{

				}
			}

			//Brush
			if (i == 3)
			{
				if (getActiveScene() == 1)
				{

				}
			}

			
		}
	}
}



void Level3::update(sf::RenderWindow &window, float deltaTime)
{
	//Only do this if the level needs moving camera
	//mLHandler->getLevel(1) is currently LastLevel, change as necessary

	//Make sure UI is in correct position at all times
	mUI->setUIPosition(mView.getCenter());
	mInventory->setGridPosition(mView.getCenter());

	//Scene 1 is the big, second room in LastLevel, change as necessary
	if (getActiveScene() == 0)
	{
		//520 is the distance the Player has to be from the left side of the level before the camera starts scrolling, change as necessary
		//1000 is the distance the Player has to be from the right side of the level before the camera starts scrolling, change as necessary
		//In this case the camera scrolls while the Player is between 520 and 1000.
		if (mPlayer->getPosition().x > 520 && mPlayer->getPosition().x < 1530)
		{
			//Make camera follow Player position
			moveViewWithPlayer(mPlayer->getPosition().x);
		}
	}

	if (getActiveScene() == 1)
	{
		if (mPlayer->getPosition().x > 520 && mPlayer->getPosition().x < 1000)
		{
			moveViewWithPlayer(mPlayer->getPosition().x);
		}
	}

	if (getActiveScene() == 2)
	{
		if (mPlayer->getPosition().x > 520 && mPlayer->getPosition().x < 2000)
		{
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
		if (mPlayer->getIsOnPosition())
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


				if (mTargetItem->getId() == "Trimmer")
				{
					mInventory->addItem(mTargetItem);
					mTargetItem->changeTexture(handler, "TrimmerIcon.png");
					std::cout << "Plockade upp h�cksax!";

				}

				if (mTargetItem->getId() == "Flowers")
				{
					mInventory->addItem(mTargetItem);
					std::cout << "Plockade upp blomma!";

				}

				if (mTargetItem->getId() == "Stick")
				{
					if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Trimmer")
					{
						mInventory->addItem(mTargetItem);
						mTargetItem->changeTexture(handler, "StickIcon.png");
						std::cout << "Plockade upp Pinne!";

					}
					else
					{
						mTargetItem->toggleActive();
						mTargetItem->toggleInteractable();
					}

				}

				if (mTargetItem->getId() == "Clover")
				{
					if (mItemPicked == false)
					{
						mInventory->addItem(mTargetItem);
						mItemPicked = true;
						std::cout << "Plockade upp kl�ver!";
					}
					else
					{
						mTargetItem->toggleActive();
					}
				}

				if (mTargetItem->getId() == "Sawdust")
				{
					if (mItemPicked == false)
					{
						mInventory->addItem(mTargetItem);
						mItemPicked = true;
						std::cout << "Plockade upp s�gsp�n!";
					}
					else
					{
						mTargetItem->toggleActive();
					}
				}

				if (mTargetItem->getId() == "Fjun")
				{
					if (mItemPicked == false)
					{
						mInventory->addItem(mTargetItem);
						mItemPicked = true;
						std::cout << "Plockade upp fjun!";
					}
					else
					{
						mTargetItem->toggleActive();
					}
				}

				if (mTargetItem->getId() == "Featherball")
				{
					if (mItemPicked == false)
					{
						mInventory->addItem(mTargetItem);
						mItemPicked = true;
						std::cout << "Plockade upp fj�derboll!";
					}
					else
					{
						mTargetItem->toggleActive();
					}
				}

				if (mTargetItem->getId() == "Nail")
				{
					if (mItemPicked == false)
					{
						mInventory->addItem(mTargetItem);
						mItemPicked = true;
						std::cout << "Plockade upp spik!";
					}
					else
					{
						mTargetItem->toggleActive();
					}
				}

				if (mTargetItem->getId() == "Cloth")
				{
					if (mItemPicked == false)
					{
						mInventory->addItem(mTargetItem);
						mItemPicked = true;
						std::cout << "Plockade upp tygbit!";
					}
					else
					{
						mTargetItem->toggleActive();
					}
				}


			}


			//Check if Item can be interacted with
			else if (mTargetItem->getInteractable())
			{
				//Check if Item has already been interacted with
				if (!mTargetItem->isInteracted())
				{
					mTargetItem->toggleInteractable();

					//Koppel
					if (mTargetItem->getId() == "Leash")
					{


						if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Trimmer")
						{
							mTargetItem->changeTexture(handler, "transparent.png"); //Add correct texture!
							mUnleashed = true;
							std::cout << "Klipper kopplet!";
						}
						else
						{
							mTargetItem->toggleInteractable();
						}

						
					}

					//Hund
					if (mTargetItem->getId() == "Dog")
					{
						if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Stick" && mUnleashed == true)
						{
							mInventory->removeItem(mInventory->getSelectedItem());

							mTargetItem->moveToPosition(1272, 500);
							std::cout << "Kastade pinnen!";
							mCursor->setMode(Cursor::DISABLED);
							mTargetItem->setActiveAnimation("Dog");
							mDogRunning = true;


							mPlayRects.push_back(createRect(683, 360, 673, 160));
						}
						else
						{
							mTargetItem->toggleInteractable();
						}


					}

					//Flaggst�ng
					if (mTargetItem->getId() == "Flagpole")
					{
						if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Flowers")
						{
							mInventory->removeItem(mInventory->getSelectedItem());
							mPlayRects.push_back(createRect(1356, 360, 500, 160));

							for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
							{
								if (getItems()[i]->getId() == "Singleflower")
								{
									getItems()[i]->toggleActive();
								}
							}

						}

						else
						{
					
							mTargetItem->toggleInteractable();
						}

					}

					//Knippe blommor
					if (mTargetItem->getId() == "Singleflower")
					{
						mTargetItem->moveToPosition(1390, 121);
					}

					//KNEKTEN 
					if (mTargetItem->getId() == "Jack")
					{
						if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() != "Screwdevice")
						{
							if (mInventory->selectedItem()->getId() == "Clover" || mInventory->selectedItem()->getId() == "Nail" || mInventory->selectedItem()->getId() == "Featherball" || mInventory->selectedItem()->getId() == "Fjun" || mInventory->selectedItem()->getId() == "Sawdust" || mInventory->selectedItem()->getId() == "Cloth")
							{
								mInventory->removeItem(mInventory->getSelectedItem());
								mItemPicked = false;
								mTargetItem->toggleInteractable();

								//OBSOBS vad mer ska h�nda?
							}
							else
							{
								mTargetItem->toggleInteractable();
							}
						}
						else
						{
							mTargetItem->toggleInteractable();
						}
					}
				}
			}
			//Disable Item interaction when done
			mItemInteraction = false;
		}
	}

	//Animation updates
	mDog->update(deltaTime);
	mLady->update(deltaTime);

	//Inventory
	mInventory->update(window);

	//Only update currently "Targeted" Item to avoid having to loop through and update all Items
	if (mTargetItem != NULL)
	{
		mTargetItem->update(deltaTime);
		//Put everything back to normal after the "Pushing cutscene"
		if (mTargetItem->getIsOnPosition())
		{

			if (mDogRunning)
			{
				mDogRunning = false;
				mCursor->setMode(Cursor::NORMAL);
				mTargetItem->toggleActive();
			}

		}
	}

	mCursor->setPosition(sf::Vector2f(mWorldPos));
	mCursor->update(window);

	if (mCursor->getMode() != Cursor::DIALOGUE && mCursor->getMode() != Cursor::INVENTORY && mCursor->getMode() != Cursor::DISABLED && mCursor->getMode() != Cursor::MENU && mUpdateTime > 0)
	{
		mouseHover();
		mUpdateTime = 0;
	}
	else
	{
		mUpdateTime++;
	}

	//Make sure UI is in correct place at all times
	mUI->setUIPosition(mView.getCenter());
	mInventory->setGridPosition(mView.getCenter());

}

void Level3::mouseHover()
{
	mCursor->setMode(Cursor::NORMAL);

	//Check if playrect collision
	if (checkCollision(getPlayRects(), mCursor->getRect()))
	{
		mCursor->setMode(Cursor::NORMAL); // TODO - Add walk cursor maybe?
	}

	//Check Item collision
	//Loop through all Items in active level
	for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
	{
		//Check if mouse collided with Item
		if (getItems()[i]->getRectangle().intersects(mCursor->getRect()))
		{
			//Check if Item is Active
			if (getItems()[i]->getActive())
			{
				if (!getItems()[i]->isLookedAt())
				{
					mCursor->setMode(Cursor::EYE);
				}
				//Check if Item can be picked up
				else if (getItems()[i]->getPickupable())
				{
					mCursor->setMode(Cursor::OPENHAND);
				}
				//Check if Item can be interacted with
				else if (getItems()[i]->getInteractable())
				{
					//Check if Item has already been interacted with
					if (!getItems()[i]->isInteracted())
					{
						mCursor->setMode(Cursor::OPENHAND);
					}
				}
			}
		}
	}

	//Check Rect Collisions
	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], mCursor->getRect()))
		{
			//// i == 10 is stairs in scene 1
			//if (i == 10)
			//{
			//	if (mActiveScene == 0)
			//	{
			//		mCursor->setMode(Cursor::NORMAL);
			//	}
			//	else
			//	{
			//		mCursor->setMode(Cursor::EYE);
			//	}
			//}

			//// i == 5 is stairs in scene 2
			//else if (i == 5)
			//{
			//	if (mActiveScene == 1)
			//	{
			//		mCursor->setMode(Cursor::NORMAL);
			//	}
			//	else
			//	{
			//		mCursor->setMode(Cursor::EYE);
			//	}
			//}

			//// i == 0 is door in scene 2
			//else if (i == 0)
			//{
			//	if (mActiveScene == 1)
			//	{
			//		mCursor->setMode(Cursor::NORMAL);
			//	}
			//}

			////i == 2 is door in scene 3
			//else if (i == 2)
			//{
			//	if (mActiveScene == 2)
			//	{
			//		mCursor->setMode(Cursor::NORMAL);
			//	}
			//	else
			//	{
			//		mCursor->setMode(Cursor::NORMAL);
			//	}
			//}

			//else
			//{
				mCursor->setMode(Cursor::EYE);
			//}
		}
	}

	if (mInventory->selectedItem() != NULL)
	{
		mCursor->setMode(Cursor::CLOSEDHAND);
	}
}

bool Level3::isLevelComplete()
{
	return mLevelComplete;
}

UI* Level3::getUI()
{
	return mUI;
	//TODO - add ui stuff here
}