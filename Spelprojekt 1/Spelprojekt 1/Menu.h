#ifndef INCLUDED_MENU
#define INCLUDED_MENU

#include "ResourceHandler.h"
#include "SFML\System.hpp"

class Menu{
public:
	Menu(ResourceHandler &handler);
	~Menu();

	enum ActiveMenu
	{
		HAT,
		MAIN,
		INVENTORY,
		CLUES,
		MEMORIES,
		SETTINGS,
		EXIT,
		NONE
	};

	void update();
	void draw(sf::RenderWindow &window);

	void checkCollision(sf::Vector2f point);

	void setActiveMenu(ActiveMenu newMode);

	ActiveMenu getActiveMenu();
	sf::FloatRect getHatIconRect();
	sf::FloatRect getMenuIconRect();

private:
	ActiveMenu menu;

	//Menu Sprites
	sf::Sprite mHatIcon;
	sf::Sprite mMenuIcon;
	sf::Sprite mHatMenu;
	sf::Sprite mMainMenu;
	sf::Sprite mInventoryMenu;

	//Menu Rects
	sf::FloatRect mInventoryRect;
	sf::FloatRect mCluesRect;
	sf::FloatRect mMemoriesRect;
	sf::FloatRect mSettingsRect;
	sf::FloatRect mExitRect;

	//Help Rectangle
	sf::RectangleShape mHelpRectangle;
};

#endif