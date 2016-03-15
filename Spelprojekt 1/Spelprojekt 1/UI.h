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
		LEVELSELECT,
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
	void drawLevelSelect(sf::RenderWindow & window);
	void drawExit(sf::RenderWindow &window);

	void checkCollision(sf::Vector2f point);

	void setState(State newState);
	void eventListen(sf::RenderWindow &window);

	State getState();
	sf::FloatRect getInventoryIconRect();
	sf::FloatRect getCluesIconRect();
	sf::FloatRect getExitIconRect();

	void setUIPosition(sf::Vector2f viewCenter);

	void setActiveAnimation(std::string animation);
	std::string getActiveAnimation();

	bool getLevelStart();
	void setLevelStart(bool value);

	sf::FloatRect getInfoIconRect();
	bool getInfoBoxDisplay();
	void setInfoBoxDisplay(bool display);

	sf::FloatRect getInventoryRect();

	bool getLevelExit();
	void setLevelExit(bool value);

	int getSelectedLevel();
	void setSelectedLevel(int level);

private:
	State mState;
	bool mLevelStart;
	bool mLevelExit;
	bool mInfoBoxDisplay;

	//Buttons
	typedef std::vector<Button*> ButtonVector;
	ButtonVector mMainButtons;
	ButtonVector mExitButtons;
	ButtonVector mUIButtons;
	ButtonVector mLevelSelectButtons;
	sf::RectangleShape mBackground;

	//UI Sprites
	sf::Sprite mInventoryIcon;
	sf::Sprite mExitIcon;
	sf::Sprite mCluesIcon;
	sf::Sprite mInventoryMenu;
	sf::Sprite mInfoIcon;
	sf::Sprite mInfoBox;

	//UI Rects
	sf::FloatRect mInventoryRect;
	sf::FloatRect mCluesRect;
	sf::FloatRect mExitRect;

	//Mouse position
	sf::Vector2i mPixelPos;
	sf::Vector2f mWorldPos;
	//Custom cursor
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
	sf::Texture mInventoryGlow;
	sf::Texture mClueGlow;

	//Text
	sf::Font mFont;
	sf::Text mInfoText;

	bool mReset;
	int mSelectedLevel;
};

#endif