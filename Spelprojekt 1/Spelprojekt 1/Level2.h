#ifndef INCLUDED_LEVEL2
#define INCLUDED_LEVEL2

#include "Level.h"
#include "SFML\System.hpp"

class Level2 : public Level {
public:
	Level2(ResourceHandler &handler);
	~Level2();

	//Items
	ItemVector getItems();
	void addItem(Item* item);
	void removeItem(Item* item);

	//Player
	Player* getPlayer();

	//UI
	UI* getUI();

	//Sound
	void playBackgroundMusic();
	void playAmbience();

	//Draw
	void drawBackground(sf::RenderWindow &window);
	void drawForeground(sf::RenderWindow &window);
	void drawItems(ItemVector items, sf::RenderWindow &window);
	void drawUI(sf::RenderWindow &window);

	//Rectangles
	rectVector getRects();
	void removeRect(int index);
	void addRect(sf::FloatRect* rect);
	const rectVector getPlayRects();

	//Active Level
	void toggleActive(ResourceHandler &handler, sf::RenderWindow &window, UI *ui);
	bool isActive();

	//View
	sf::View getView();
	void moveViewWithPlayer(float playerPos);

	//Scene
	void clearScene();
	void internalSwap(int num);
	void changeScene(int num);
	int getActiveScene();

	//Eventstuff
	int checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point);
	int checkCollision(sf::FloatRect* boundingBox, sf::Vector2f &point);
	int checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point);
	int checkCollision(sf::FloatRect* boundingBox, sf::FloatRect &rect);
	int checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::FloatRect &rect);
	void eventListen(sf::RenderWindow &window);
	void mouseClick(sf::Event &event);
	void mouseReleased(sf::Event &event);
	void update(sf::RenderWindow &window, float deltaTime);
	void mouseHover();

	//Level Complete
	bool isLevelComplete();

	//Update functions
	void updateTargetItem(float deltaTime);
	void lookAtTargetItem();
	void pickupTargetItem();
	void interactTargetItem();

	//Mouseclick collision functions
	void mouseClickCheckItemCollision(sf::Vector2f point);
	void mouseClickCheckRectCollision(sf::Vector2f point);

private:

	//Rectangles
	rectVector mRects;
	rectVector mPlayRects;
	sf::RectangleShape background;
	sf::RectangleShape playground;
	sf::RectangleShape foreground;
	sf::RectangleShape backgroundZoom;
	sf::RectangleShape playgroundZoom;
	sf::RectangleShape foregroundZoom;
	sf::FloatRect* createRect(float positionX, float positionY, float sizeX, float sizeY);

	//Help Rectangles
	sf::RectangleShape rectangleSteamMachine;
	sf::RectangleShape rectangleVise;
	sf::RectangleShape rectangleDrawer;
	sf::RectangleShape rectangleBicycle;
	sf::RectangleShape rectangleComputer;
	sf::RectangleShape rectanglePosters;
	sf::RectangleShape rectangleToolwall;

	//Sound
	sf::Music music;
	sf::Sound mAmbientSound;
	sf::Sound mRegularItemSound;
	sf::Sound mMenuMainUISound;
	sf::Sound mMenuHatSound;
	sf::Sound mMenuInventorySound;
	sf::Sound mCriticalItemSound;

	//Scene
	bool mIsActive;
	int mActiveScene;

	//View
	sf::View mView;

	//Items
	ItemVector mItems;
	Item* mCable;
	Item* mAirbag;
	Item* mBalloon;
	Item* mFilledBalloon;
	Item* mJuice;
	Item* mGlove;
	Item* mKey;
	Item* mWorkshopStick;
	Item* mCloth;
	Item* mCan;
	Item* mPutte;
	Item* mArnold;
	Item* mSteamMachine;
	Item* mVise;
	Item* mDrawer;

	//Item Glow
	//sf::Sprite mAstronautGlow;

	//Inventory
	Inventory *mInventory;
	sf::Sprite mCursorSprite;

	//DialogueSystem
	DialogueSystem *mDialogueSystem;

	//Player
	Player *mPlayer;

	//Mouse Cursor
	Cursor *mCursor;

	//Menu
	UI *mUI;

	//Clues
	Clue *mClues;

	//Eventstuff
	sf::Vector2f mWorldPos;
	sf::Vector2i mPixelPos;
	sf::Vector2f mViewMoveTo;
	Item* mTargetItem;
	bool mItemInteraction;
	//Scene change
	sf::FloatRect mSceneChangeRect;
	sf::Vector2f mSceneChangePlayerPos;
	int mNewScene;

	bool mMouseReleased;

	bool mSceneChange;
	bool mPlayerToggle;
	bool mLevelComplete;

	bool mAutoDialogueTriggered;
	bool mTalkedToArnold;
	bool mSteamMachineWorking;
};
#endif
