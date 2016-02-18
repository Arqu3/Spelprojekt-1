#ifndef INCLUDED_UI
#define INCLUDED_UI

#include "SFML\System.hpp"
#include "Menu.h"

class UI{
public:
	UI(ResourceHandler &handler);
	~UI();

	enum ActiveUI
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

	void update(Menu &menu);
	void draw(sf::RenderWindow &window);

	void checkCollision(sf::Vector2f point);

	void setActiveUI(ActiveUI newUI);

	ActiveUI getActiveUI();
	sf::FloatRect getHatIconRect();
	sf::FloatRect getMenuIconRect();

private:
	ActiveUI ui;

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