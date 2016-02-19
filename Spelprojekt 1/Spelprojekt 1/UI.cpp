#include "UI.h"

using namespace std;

UI::UI(ResourceHandler &handler) :
ui(INGAME)
{
	//UI Icons
	//HatIcon
	handler.getTexture("haticon.png")->setSmooth(true);
	mHatIcon.setTexture(*handler.getTexture("haticon.png"));
	mHatIcon.setPosition(sf::Vector2f(10, 470));
	mHatIcon.setScale(sf::Vector2f(0.3f, 0.3f));

	//mUIButtons.push_back(new Button(handler, 10.0f, 470.0f, "haticon.png"));
	//mUIButtons[0]->getSprite().setScale(sf::Vector2f(0.3f, 0.3f));

	//MenuIcon
	handler.getTexture("menuicon.png")->setSmooth(true);
	mMenuIcon.setTexture(*handler.getTexture("menuicon.png"));
	mMenuIcon.setPosition(sf::Vector2f(90, 510));
	mMenuIcon.setScale(sf::Vector2f(0.3f, 0.3f));

	//mUIButtons.push_back(new Button(handler, 90.0f, 510.0f, "menuicon.png"));
	//mUIButtons[0]->getSprite().setScale(sf::Vector2f(0.3f, 0.3f));

	//UI Menus
	//HatMenu
	handler.getTexture("hatmenu.png")->setSmooth(true);
	mHatMenu.setTexture(*handler.getTexture("hatmenu.png"));
	mHatMenu.setPosition(sf::Vector2f(0, 285));
	mHatMenu.setScale(sf::Vector2f(0.3f, 0.3f));
	//Menu
	handler.getTexture("menu.png")->setSmooth(true);
	mMainMenu.setTexture(*handler.getTexture("menu.png"));
	mMainMenu.setPosition(sf::Vector2f(0, 300));
	mMainMenu.setScale(sf::Vector2f(0.3f, 0.3f));
	//Inventory Menu
	handler.getTexture("inventory.png")->setSmooth(true);
	mInventoryMenu.setTexture(*handler.getTexture("inventory.png"));
	mInventoryMenu.setPosition(sf::Vector2f(250, 50));
	mInventoryMenu.setScale(sf::Vector2f(0.3f, 0.3f));

	//UI Rects
	mInventoryRect = sf::FloatRect(sf::Vector2f(30, 305), sf::Vector2f(80, 85));
	mCluesRect = sf::FloatRect(sf::Vector2f(155, 365), sf::Vector2f(75, 80));
	mMemoriesRect = sf::FloatRect(sf::Vector2f(195, 475), sf::Vector2f(75, 80));
	mSettingsRect = sf::FloatRect(sf::Vector2f(80, 320), sf::Vector2f(90, 90));
	mExitRect = sf::FloatRect(sf::Vector2f(180, 430), sf::Vector2f(85, 80));

	//Help Rectangle
	mHelpRectangle.setPosition(sf::Vector2f(180, 430));
	mHelpRectangle.setSize(sf::Vector2f(85, 80));

	//Exit buttons
	mExitButtons.push_back(new Button(200, 100, sf::Color::Red));
	mExitButtons.push_back(new Button(200, 100, sf::Color::Green));

	for (ButtonVector::size_type i = 0; i < mExitButtons.size(); i++)
	{
		mExitButtons[i]->setPosition(512.0f - mExitButtons[0]->getRect().width + (260.0f * i), 288);
	}
}

UI::~UI()
{
}

void UI::update()
{
	switch (ui){
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
}

void UI::draw(sf::RenderWindow &window)
{
	switch (ui)
	{
	case UI::HAT:
		window.draw(mHatMenu);
		break;

	case UI::MAINUI:
		window.draw(mMainMenu);
		break;

	case UI::MAINMENU:
		break;

	case UI::INVENTORY:
		window.draw(mHatMenu);
		window.draw(mInventoryMenu);
		break;

	case UI::CLUES:
		break;

	case UI::MEMORIES:
		break;

	case UI::SETTINGS:
		break;

	case UI::EXIT:
		break;

	case UI::INGAME:
		break;

	default:
		break;
	}

	window.draw(mHatIcon);
	window.draw(mMenuIcon);
}

void UI::checkCollision(sf::Vector2f point)
{
	if (getHatIconRect().contains(point))
	{
		if (ui != HAT)
		{
			ui = HAT;
		}
		else
		{
			ui = INGAME;
		}
	}
	if (getMenuIconRect().contains(point))
	{
		if (ui != MAINUI)
		{
			ui = MAINUI;
		}
		else
		{
			ui = INGAME;
		}
	}

	//Check appropriate Rect collisions when Hat Menu is open
	if (ui == HAT)
	{
		if (mInventoryRect.contains(point))
		{
			ui = INVENTORY;
		}
		if (mCluesRect.contains(point))
		{
			ui = CLUES;
			cout << "CLUES MENU ENGAGED" << endl;
		}
		if (mMemoriesRect.contains(point))
		{
			ui = MEMORIES;
			cout << "MEMORIES OF THE DEAD" << endl;
		}
	}

	//Check appropriate Rect collisions when "Main" Menu is open
	if (ui == MAINUI)
	{
		if (mSettingsRect.contains(point))
		{
			ui = SETTINGS;
			cout << "SETTINGS ALREADY PERFECT" << endl;
		}
		if (mExitRect.contains(point))
		{
			ui = EXIT;
			cout << "NOOOOOOOOOOOOOO" << endl;
		}
	}
}

void UI::setActiveUI(ActiveUI newUI)
{
	ui = newUI;
}

UI::ActiveUI UI::getActiveUI()
{
	return ui;
}

sf::FloatRect UI::getHatIconRect()
{
	return mHatIcon.getGlobalBounds();
}

sf::FloatRect UI::getMenuIconRect()
{
	return mMenuIcon.getGlobalBounds();
}