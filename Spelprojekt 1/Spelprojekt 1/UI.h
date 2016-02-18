#ifndef INCLUDED_UI
#define INCLUDED_UI

#include "SFML\System.hpp"
#include "Button.h"

class UI{
public:
	UI(ResourceHandler &handler);
	~UI();

	enum ActiveUI
	{
		HAT,
		MAINUI,
		MAINMENU,
		INVENTORY,
		CLUES,
		MEMORIES,
		SETTINGS,
		EXIT,
		INGAME
	};

	void update();
	void draw(sf::RenderWindow &window);

	void checkCollision(sf::Vector2f point);

	void setActiveUI(ActiveUI newUI);

	ActiveUI getActiveUI();
	sf::FloatRect getHatIconRect();
	sf::FloatRect getMenuIconRect();

private:
	ActiveUI ui;

	//Buttons
	typedef std::vector<Button*> ButtonVector;
	ButtonVector mMainButtons;
	ButtonVector mExitButtons;
	ButtonVector mUIButtons;
	sf::RectangleShape mBackground;

	//UI Sprites
	sf::Sprite mHatIcon;
	sf::Sprite mMenuIcon;
	sf::Sprite mHatMenu;
	sf::Sprite mMainMenu;
	sf::Sprite mInventoryMenu;

	//UI Rects
	sf::FloatRect mInventoryRect;
	sf::FloatRect mCluesRect;
	sf::FloatRect mMemoriesRect;
	sf::FloatRect mSettingsRect;
	sf::FloatRect mExitRect;

	//Help Rectangle
	sf::RectangleShape mHelpRectangle;
};

#endif