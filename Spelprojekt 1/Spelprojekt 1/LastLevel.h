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

	//Sound
	void playBackgroundMusic();
	void playAmbience();

	//Draw
	void drawItems(ItemVector items, sf::RenderWindow &window);
	void drawBackground(sf::RenderWindow &window);
	void drawForeground(sf::RenderWindow &window);

	//Rectangle functions
	rectVector getRects();
	void addRect(sf::FloatRect *rect);
	void removeRect(int index);
	const rectVector getPlayRects();


	//Scene funtions
	void clearScene();
	void internalSwap(int num);
	void changeScene(int num);
	int getActiveScene();
	void toggleActive();
	bool isActive();

private:

	//Rectangles
	rectVector mRects;
	rectVector mPlayRects;

	sf::RectangleShape background;
	sf::RectangleShape background2;
	sf::RectangleShape background3;

	sf::RectangleShape rectangle; //HelpRect
	sf::FloatRect* createRect(int positionX, int positionY, int sizeX, int sizeY);

	//Sound
	sf::Music backgroundMusic;
	sf::Sound ambientSound;

	//Scene
	bool mIsActive;
	int mActiveScene;

	//Items
	ItemVector mItems;
	Item* mMagicClam;
	Item* mNeedle;
	Item* mEarth;
	Item* mFish;
	Item* mHoolaHoop;
	Item* mBeigeBall;
	Item* mRedApple;


	
};

#endif
