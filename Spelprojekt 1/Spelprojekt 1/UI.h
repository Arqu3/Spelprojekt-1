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

	void update(float deltaTime);
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

	void setUIPosition(sf::Vector2f viewCenter);

	void setActiveAnimation(std::string animation);
	std::string getActiveAnimation();

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
	sf::Sprite mMainUI;
	sf::Sprite mInventoryMenu;

	//UI Rects
	sf::FloatRect mHatRect;
	sf::FloatRect mMenuRect;
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

	//Animations
	std::string mActiveAnimation;
	float mFrameTime;
	float mCurrentTime;
	int mCurrentFrame;
	int mFrameXOffset;
	int mFrameYOffset;
	
	//Spritesheets
	
};

#endif