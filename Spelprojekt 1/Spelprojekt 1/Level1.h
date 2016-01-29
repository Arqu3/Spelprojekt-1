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

	//Sound
	void playBackgroundMusic();
	void playAmbience();

	//Draw
	void draw(sf::RenderWindow &window);
	void drawItems(ItemVector items, sf::RenderWindow &window);

	//Rectangles
	rectVector getRects();
	void removeRect(int index);
	void addRect(sf::FloatRect* rect);
	const rectVector getPlayRects();

	//Scene
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
	sf::RectangleShape backgroundfishtank;
	sf::RectangleShape rectangle;
	sf::FloatRect* createRect(float positionX, float positionY, float sizeX, float sizeY);

	//Sound
	sf::Music backgroundMusic;
	sf::Sound ambientSound;

	//Scene
	bool mIsActive;
	int mActiveScene;

	//Items
	ItemVector mItems;
	Item* mScrewdevice;
	Item* mStar;
	Item* mBlock;
	Item* mString;
	Item* mMagnet;
	Item* mAstronaut;
};
#endif
