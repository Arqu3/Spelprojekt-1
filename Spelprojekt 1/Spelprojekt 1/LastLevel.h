#ifndef INCLUDED_LASTLEVEL
#define INCLUDED_LASTLEVEL

#include "Level.h"
#include "SFML\System.hpp"

class LastLevel: public Level{
public:

	LastLevel(ResourceHandler &handler);
	~LastLevel();

	//Item
	ItemVector getItems();
	void addItem(Item *item);
	void removeItem(Item *item);

	//Player
	Player* getPlayer();

	//UI
	UI* getUI();

	//Sound
	void playBackgroundMusic();
	void playAmbience();

	//Draw
	void drawItems(ItemVector items, sf::RenderWindow &window);
	void drawBackground(sf::RenderWindow &window);
	void drawForeground(sf::RenderWindow &window);
	void drawUI(sf::RenderWindow &window);

	//Rectangle functions
	rectVector getRects();
	void addRect(sf::FloatRect *rect);
	void removeRect(int index);
	const rectVector getPlayRects();

	//View
	sf::View getView();
	void moveViewWithPlayer(float playerPos);

	//Scene funtions
	void clearScene();
	void internalSwap(int num);
	void changeScene(int num);
	int getActiveScene();
	void toggleActive(ResourceHandler &handler, sf::RenderWindow &window);
	bool isActive();

	//Eventstuff
	int checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point);
	int checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point);
	int checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point);
	int checkCollision(sf::FloatRect* boundingBox, sf::FloatRect &rect);
	int checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::FloatRect &rect);

	void eventListen(sf::RenderWindow &window);
	void mouseClick(sf::Event &event);
	void update(sf::RenderWindow &window, float deltaTime);
	void mouseHover();


	//Level Complete
	bool isLevelComplete();

private:

	//Player
	Player *mPlayer;

	//Rectangles
	rectVector mRects;
	rectVector mPlayRects;

	sf::RectangleShape background;
	sf::RectangleShape playground;
	sf::RectangleShape foreground;

	sf::RectangleShape background2;
	sf::RectangleShape playground2;
	sf::RectangleShape foreground2;

	sf::RectangleShape background3;
	sf::RectangleShape playground3;
	sf::RectangleShape foreground3;

	sf::RectangleShape rectangle; //HelpRect
	sf::FloatRect* createRect(int positionX, int positionY, int sizeX, int sizeY);

	//Sound
	sf::Music music;
	sf::Sound ambientSound;

	//Scene
	bool mIsActive;
	int mActiveScene;

	//View
	sf::View mView;

	//Items
	ItemVector mItems;
	Item* mPutte;
	Item* mDollhouse;
	Item* mMagicClam;
	Item* mNeedle;
	Item* mEarth;
	Item* mFish;
	Item* mGramophone;
	Item* mHoolaHoop;
	Item* mBeigeBall;
	Item* mFruitbowl;
	Item* mRedApple;
	Item* mCat;
	Item* mFoodBowl;
	Item* mKids;
	Item* mHole;
	Item* mPearl;
	Item* mScrewDevice;
	Item* mSaturn;
	Item* mVenus;

	bool mLevelComplete;

	//Inventory
	Inventory *mInventory;

	//DialogueSystem
	DialogueSystem *mDialogueSystem;

	//Mouse Cursor
	Cursor *mCursor;

	//Menu
	UI *mUI;


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
	int mLastScene;

	bool mPlayerToggle;
	bool mInventoryMode;
	bool mDisableClick;
	bool mFishFalling;
	bool mCatWalking;
	bool mEarthPickedUp;
	bool mDollhouseInteracted;
	bool mKidsFound;
	bool mCatMoved;
	bool mPutteTalked;

	ResourceHandler &handler;

	int mUpdateTime;
};

#endif
