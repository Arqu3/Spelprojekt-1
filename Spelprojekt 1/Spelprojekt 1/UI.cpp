#include "UI.h"

using namespace std;

UI::UI(ResourceHandler &handler) :
mState(MAINMENU),
mCurrentFrame(0),
mCurrentTime(0),
mFrameTime(0.03f),
mFrameXOffset(0),
mFrameYOffset(0),
mActiveAnimation("None"),
mLevelStart(false),
mInfoBoxDisplay(true),
mReset(false)
{
	//Cursor
	mCursor = new Cursor(handler);

	//UI Icons
	//HatIcon
	handler.getTexture("InventoryIconGlow.png")->setSmooth(true);
	mInventoryIcon.setTexture(*handler.getTexture("InventoryIconGlow.png"));
	mInventoryIcon.setTextureRect(sf::IntRect(0, 0, 346, 346));
	mInventoryIcon.setPosition(sf::Vector2f(10, 470));
	mInventoryIcon.setScale(sf::Vector2f(0.65f, 0.65f));

	//CluesIcon
	handler.getTexture("CluesIconGlow.png")->setSmooth(true);
	mClueGlow = *handler.getTexture("CluesIconGlow.png");
	mCluesIcon.setTexture(mClueGlow);
	mCluesIcon.setTextureRect(sf::IntRect(0, 0, 346, 346));
	mCluesIcon.setScale(sf::Vector2f(0.6f, 0.6f));

	//ExitIcon
	handler.getTexture("ExitIconGlow.png")->setSmooth(true);
	mExitIcon.setTexture(*handler.getTexture("ExitIconGlow.png"));
	mExitIcon.setTextureRect(sf::IntRect(0, 0, 346, 346));
	mExitIcon.setPosition(sf::Vector2f(90, 510));
	mExitIcon.setScale(sf::Vector2f(0.60f, 0.60f));

	//UI Menus
	//Inventory Menu
	handler.getTexture("inventory.png")->setSmooth(true);
	mInventoryMenu.setTexture(*handler.getTexture("inventory.png"));
	mInventoryMenu.setPosition(sf::Vector2f(250, 50));
	mInventoryMenu.setScale(sf::Vector2f(0.6f, 0.6f));

	//UI Rects
	mInventoryRect = sf::FloatRect(sf::Vector2f(10, 470), sf::Vector2f(80, 85));
	mCluesRect = sf::FloatRect(sf::Vector2f(155, 365), sf::Vector2f(75, 80));
	mExitRect = sf::FloatRect(sf::Vector2f(90, 510), sf::Vector2f(75, 80));

	//Tutorial Info Icon
	handler.getTexture("InfoIcon.png")->setSmooth(true);
	mInfoIcon.setTexture(*handler.getTexture("InfoIcon.png"));
	mInfoIcon.setPosition(sf::Vector2f(500, 400));
	mInfoIcon.setScale(sf::Vector2f(0.5f, 0.5f));

	//Tutorial Info Box
	handler.getTexture("InfoBox.png")->setSmooth(true);
	mInfoBox.setTexture(*handler.getTexture("InfoBox.png"));
	mInfoBox.setPosition(sf::Vector2f(700, 300));
	mInfoBox.setScale(sf::Vector2f(0.7f, 0.3f));

	//Help Rectangle
	mHelpRectangle.setPosition(sf::Vector2f(180, 430));
	mHelpRectangle.setSize(sf::Vector2f(85, 80));

	//Exit buttons
	mExitButtons.push_back(new Button(200, 100, sf::Color::Red));
	mExitButtons.push_back(new Button(200, 100, sf::Color::Green));

	for (ButtonVector::size_type i = 0; i < mExitButtons.size(); i++)
	{
		mExitButtons[i]->setPosition(512.0f - mExitButtons[0]->getRect().width + (260.0f * i) - 45, 288 - mExitButtons[0]->getRect().height);
	}

	//Main menu stuff
	mBackground.setSize(sf::Vector2f(1024, 576));
	mBackground.setTexture(handler.getTexture("MainMenuBackground.png"));

	//Adds main menu buttons
	mMainButtons.push_back(new Button(handler, sf::RectangleShape(sf::Vector2f(287, 110)), "NewGame.png", "NewGameGLOW.png"));
	mMainButtons.push_back(new Button(handler, sf::RectangleShape(sf::Vector2f(287, 110)), "Continue.png", "ContinueGLOW.png"));
	mMainButtons.push_back(new Button(handler, sf::RectangleShape(sf::Vector2f(393, 120)), "Options.png", "OptionsGLOW.png"));
	mMainButtons.push_back(new Button(handler, sf::RectangleShape(sf::Vector2f(287, 110)), "Exit.png", "ExitGLOW.png"));

	for (ButtonVector::size_type i = 0; i < mMainButtons.size(); i++)
	{
		mMainButtons[i]->setPosition(240.0f - (mMainButtons[0]->getRect().width / 2), 80.0f + (120.0f * i));
	}

	//Sounds
	mMenuInventorySound.setBuffer(*handler.getSound("Menu_Inventory.ogg"));
	mMenuHatSound.setBuffer(*handler.getSound("Menu_Hat.ogg"));
	mMenuMainUISound.setBuffer(*handler.getSound("Menu_MainUI.ogg"));

	//Text
	mFont.loadFromFile("Resources/Fonts/Lora-Regular.ttf");
	mInfoText.setFont(mFont);
	mInfoText.setCharacterSize(18);
	mInfoText.setColor(sf::Color::Black);
	mInfoText.setPosition(400, 420);
	mInfoText.setString("Detta är din saksamling. \nHär hittar du alla föremål du \nsamlat på dig under spelet. \nOm du drar två föremål som \nkan kombineras till verkstaden \nkan du skapa nya föremål \nsom du kan använda.");
}

UI::~UI()
{
}

void UI::update(float deltaTime)
{
	switch (mState){
	case HAT:
		break;

	case MAINUI:
		break;

	case MAINMENU:
		break;

	case INVENTORY:
		break;

	case CLUES:
		break;

	case MEMORIES:
		break;

	case SETTINGS:
		break;

	case EXIT:
		break;

	case INGAME:
		break;

	default:
		break;
	}

	mCurrentTime += deltaTime;

	//Glow Animations
	if (mActiveAnimation != "None")
	{
		mReset = false;
		if (mCurrentTime >= mFrameTime)
		{
			if (mActiveAnimation == "InventoryIconGlow" || mActiveAnimation == "InventoryIconGlowOnce")
			{
				mInventoryIcon.setTextureRect(sf::IntRect(mFrameXOffset * 346, mFrameYOffset * 346, 346, 346));
			}
			else if (mActiveAnimation == "CluesIconGlow" || mActiveAnimation == "CluesIconGlowOnce")
			{
				mCluesIcon.setTextureRect(sf::IntRect(mFrameXOffset * 346, mFrameYOffset * 346, 346, 346));
			}
			else if (mActiveAnimation == "ExitIconGlow" || mActiveAnimation == "ExitIconGlowOnce")
			{
				mExitIcon.setTextureRect(sf::IntRect(mFrameXOffset * 346, mFrameYOffset * 346, 346, 346));
			}
			if (mCurrentFrame < 49)
			{
				mFrameXOffset += 1;
				if (mFrameXOffset % 12 == 11)
				{
					mFrameYOffset++;
				}
				if (mFrameXOffset >= 11)
				{
					mFrameXOffset = 0;
				}
				mCurrentFrame += 1;
			}
			else
			{
				mCurrentFrame = 0;
				mFrameXOffset = 0;
				mFrameYOffset = 0;
				if (mActiveAnimation == "InventoryIconGlowOnce" || mActiveAnimation == "CluesIconGlowOnce" || mActiveAnimation == "ExitIconGlowOnce")
				{
					mActiveAnimation = "None";
				}
			}
		mCurrentTime = 0;
		}
	}
	else
	{
		if (!mReset)
		{
			mInventoryIcon.setTextureRect(sf::IntRect(0, 0, 346, 346));
			mExitIcon.setTextureRect(sf::IntRect(0, 0, 346, 346));
			mCluesIcon.setTextureRect(sf::IntRect(0, 0, 346, 346));
			mReset = true;
		}	
	}
}

void UI::draw(sf::RenderWindow &window)
{
	switch (mState)
	{
	case HAT:
		break;

	case MAINUI:
		break;

	case MAINMENU:
		break;

	case INVENTORY:
		window.draw(mInventoryMenu);
		window.draw(mInfoIcon);
		if (mInfoBoxDisplay)
		{
			window.draw(mInfoBox);
			window.draw(mInfoText);
		}
		break;

	case CLUES:
		break;

	case MEMORIES:
		break;

	case SETTINGS:
		break;

	case EXIT:
		drawExit(window);
		break;

	case INGAME:
		break;

	default:
		break;
	}

	//window.draw(mHelpRectangle);

	window.draw(mInventoryIcon);
	window.draw(mCluesIcon);
	window.draw(mExitIcon);
}

void UI::drawMainMenu(sf::RenderWindow &window)
{
	window.draw(mBackground);
	for (ButtonVector::size_type i = 0; i < mMainButtons.size(); i++)
	{
		mMainButtons[i]->draw(window);
	}

	mCursor->update(window);
	mCursor->draw(window);
}

void UI::drawExit(sf::RenderWindow &window)
{
	for (ButtonVector::size_type i = 0; i < mExitButtons.size(); i++)
	{
		mExitButtons[i]->draw(window);
	}
}

void UI::eventListen(sf::RenderWindow &window)
{
	sf::Event event;

	// get the current mouse position in the window
	mPixelPos = sf::Mouse::getPosition(window);
	// convert it to world coordinates
	mWorldPos = window.mapPixelToCoords(mPixelPos);
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				switch (mState)
				{
				case MAINMENU:
					if (mMainButtons[0]->isPressed(window))
					{
						mLevelStart = true;
						setState(INGAME);
					}

					if (mMainButtons[2]->isPressed(window))
					{

					}

					if (mMainButtons[3]->isPressed(window))
					{
						window.close();
					}
					break;

				case EXIT:
					if (mExitButtons[0]->isPressed(window))
					{
						setState(INGAME);
					}
					
					if (mExitButtons[1]->isPressed(window))
					{
						setState(MAINMENU);
					}
					break;
				}
			}
			break;
		}
	}
}

void UI::checkCollision(sf::Vector2f point)
{
	if (getInventoryIconRect().contains(point))
	{
		mState = INVENTORY;
	}
	if (getCluesIconRect().contains(point))
	{
		mState = INGAME;
	}
	if (getExitIconRect().contains(point))
	{
		mState = EXIT;
	}
	//if (getHatIconRect().contains(point))
	//{
	//	if (mState != HAT)
	//	{
	//		mState = HAT;
	//		if (mActiveAnimation == "HatIconGlow" || mActiveAnimation == "HatIconGlowOnce")
	//		{
	//			setActiveAnimation("None");
	//		}
	//		mMenuHatSound.play();
	//	}
	//	else
	//	{
	//		mState = INGAME;
	//	}
	//}
	//if (getMenuIconRect().contains(point))
	//{
	//	if (mState != MAINUI)
	//	{
	//		mState = MAINUI;
	//		if (mActiveAnimation == "MenuIconGlow" || mActiveAnimation == "MenuIconGlowOnce")
	//		{
	//			setActiveAnimation("None");
	//		}
	//		mMenuMainUISound.play();
	//	}
	//	else
	//	{
	//		mState = INGAME;
	//	}
	//}

	////Check appropriate Rect collisions when Hat Menu is open
	//if (mState == HAT)
	//{
	//	if (mInventoryRect.contains(point))
	//	{
	//		setState(INVENTORY);
	//		if (mActiveAnimation == "InventoryIconGlow" || mActiveAnimation == "InventoryIconGlowAfterHat")
	//		{
	//			setActiveAnimation("None");
	//		}
	//		mMenuInventorySound.play();
	//	}
	//	if (mCluesRect.contains(point))
	//	{
	//		setState(CLUES);
	//		if (mActiveAnimation == "ClueIconGlow" || mActiveAnimation == "ClueIconGlowAfterHat")
	//		{
	//			setActiveAnimation("None");
	//		}
	//		cout << "CLUES MENU ENGAGED" << endl;
	//	}
	//	if (mMemoriesRect.contains(point))
	//	{
	//		setState(MEMORIES);
	//		cout << "MEMORIES OF THE DEAD" << endl;
	//	}
	//}

	////Check appropriate Rect collisions when "MainUI" Menu is open
	//if (mState == MAINUI)
	//{
	//	if (mSettingsRect.contains(point))
	//	{
	//		setState(SETTINGS);
	//		cout << "SETTINGS ALREADY PERFECT" << endl;
	//	}
	//	if (mExitRect.contains(point))
	//	{
	//		setState(EXIT);
	//		cout << "NOOOOOOOOOOOOOO" << endl;
	//	}
	//}
}

void UI::setState(State newState)
{
	mState = newState;
}

UI::State UI::getState()
{
	return mState;
}

sf::FloatRect UI::getInventoryIconRect()
{
	return mInventoryRect;
}

sf::FloatRect UI::getCluesIconRect()
{
	return mCluesRect;
}

sf::FloatRect UI::getExitIconRect()
{
	return mExitRect;
}

void UI::setUIPosition(sf::Vector2f viewCenter)
{
	//viewCenter.x - (512 - distance from left edge of screen)
	mInventoryIcon.setPosition(sf::Vector2f(viewCenter.x - 565, 400));
	mCluesIcon.setPosition(sf::Vector2f(viewCenter.x - 490, 420));
	mExitIcon.setPosition(sf::Vector2f(viewCenter.x - 438, 430));
	mInventoryMenu.setPosition(sf::Vector2f(viewCenter.x - 262, 50));

	mInventoryRect = sf::FloatRect(sf::Vector2f(viewCenter.x - 490, 480), sf::Vector2f(70, 70));
	mCluesRect = sf::FloatRect(sf::Vector2f(viewCenter.x - 408, 500), sf::Vector2f(45, 50));
	mExitRect = sf::FloatRect(sf::Vector2f(viewCenter.x - 354, 513), sf::Vector2f(35, 40));

	mInfoIcon.setPosition(sf::Vector2f(viewCenter.x + 160, 400));
	mInfoBox.setPosition(sf::Vector2f(viewCenter.x + 200, 350));
	mInfoText.setPosition(sf::Vector2f(viewCenter.x + 210, 360));

	/*mHelpRectangle.setPosition(sf::Vector2f(viewCenter.x - 354, 513));
	mHelpRectangle.setSize(sf::Vector2f(35, 40));*/

	for (ButtonVector::size_type i = 0; i < mExitButtons.size(); i++)
	{
		mExitButtons[i]->setPosition(viewCenter.x - mExitButtons[0]->getRect().width + (260.0f * i) - 45, 288 - mExitButtons[0]->getRect().height);
	}

	//TODO - Make this work with the new Main Menu Button positions
	/*for (ButtonVector::size_type i = 0; i < mMainButtons.size(); i++)
	{
		mMainButtons[i]->setPosition(viewCenter.x - (mMainButtons[0]->getRect().width / 2), 100.0f + (160.0f * i));
	}*/

	mBackground.setPosition(viewCenter.x - 512, 0);
}

void UI::setActiveAnimation(std::string animation)
{
	if (animation == "InventoryIconGlow")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
	}
	if (animation == "CluesIconGlow")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
	}
	if (animation == "ExitIconGlow")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
	}
	else
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
	}
	mActiveAnimation = animation;
}

std::string UI::getActiveAnimation()
{
	return mActiveAnimation;
}

bool UI::getLevelStart()
{
	return mLevelStart;
}

void UI::setLevelStart()
{
	mLevelStart = false;
}

sf::FloatRect UI::getInfoIconRect()
{
	return mInfoIcon.getGlobalBounds();
}

bool UI::getInfoBoxDisplay()
{
	return mInfoBoxDisplay;
}

void UI::setInfoBoxDisplay(bool display)
{
	mInfoBoxDisplay = display;
}
