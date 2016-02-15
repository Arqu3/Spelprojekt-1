#ifndef INCLUDED_LEVEL1
#define INCLUDED_LEVEL1

#include "Level.h"
#include "SFML\System.hpp"

class Level1: public Level{
public:
	Level1(ResourceHandler &handler);
	~Level1();

	//Items
	ItemVector getItems();
	void addItem(Item* item);
	void removeItem(Item* item);

	//Player
	Player* getPlayer();

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
	void toggleActive(ResourceHandler &handler);
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
	void update(sf::RenderWindow &window, float deltaTime);
	void mouseHover();

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
	sf::RectangleShape rectangle;
	sf::FloatRect* createRect(float positionX, float positionY, float sizeX, float sizeY);

	//UI
	sf::Sprite mHatIcon;
	sf::Sprite mMenuIcon;
	sf::Sprite mHatMenu;
	sf::Sprite mMenu;

	//Cursor
	sf::Texture mNormalMouse;
	sf::Texture mOpenHandMouse;
	sf::Texture mClosedHandMouse;
	sf::Texture mSpeechMouse;
	sf::Texture mEyeMouse;
	sf::Sprite mMouseCursor;

	//Sound
	sf::Music music;
	sf::Sound mAmbientSound;

	//Scene
	bool mIsActive;
	int mActiveScene;

	//View
	sf::View mView;

	//Items
	ItemVector mItems;
	Item* mScrewdevice;
	Item* mStar;
	Item* mBlock;
	Item* mString;
	Item* mMagnet;
	Item* mAstronaut;
	Item* mBowl;
	Item* mCube;

	//Inventory
	Inventory *mInventory;

	//DialogueSystem
	DialogueSystem *mDialogueSystem;

	//Player
	Player *mPlayer;

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

	bool mPlayerToggle;
	bool mInventoryMode;
	bool mDialogueMode;
	bool mDisableClick;
	bool mLookedAtAquarium;
	bool mHatMode;
	bool mMenuMode;

	int mUpdateTime;
};
#endif
