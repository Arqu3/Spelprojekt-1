#ifndef INCLUDED_UI
#define INCLUDED_UI

#include "SFML\System.hpp"
#include "Button.h"
#include "Cursor.h"

class UI{
public:
	UI(ResourceHandler &handler);
	~UI();

	enum State
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
	void drawMainMenu(sf::RenderWindow &window);
	void drawExit(sf::RenderWindow &window);

	void checkCollision(sf::Vector2f point);

	void setState(State newState);
	void eventListen(sf::RenderWindow &window);

	State getState();
	sf::FloatRect getHatIconRect();
	sf::FloatRect getMenuIconRect();

	bool load();

private:
	State mState;
	bool mLoad;

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

	//Mouse position
	sf::Vector2i mPixelPos;
	sf::Vector2f mWorldPos;
	//Custom cursos
	Cursor* mCursor;

	//Help Rectangle
	sf::RectangleShape mHelpRectangle;

	//Sounds
	sf::Sound mMenuInventorySound;
	sf::Sound mMenuMainUISound;
	sf::Sound mMenuHatSound;
};

#endif