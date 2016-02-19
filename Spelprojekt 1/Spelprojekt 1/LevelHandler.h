#ifndef INCLUDED_LH
#define INCLUDED_LH

#include "Player.h"
#include "Level.h"
#include "Level1.h"
#include "LastLevel.h"
#include "Item.h"
#include <vector>

class LevelHandler
{
public:
	LevelHandler(ResourceHandler &handler);
	~LevelHandler();

	typedef std::vector<Item*> ItemVector;
	typedef std::vector<Level*> LevelVector;

	//Update
	void update(float deltaTime, sf::RenderWindow &window, ResourceHandler &handler);

	//Draw
	void draw(sf::RenderWindow &window);

	void setActiveLevel(int num, ResourceHandler &handler, bool firstStart);

	ItemVector getActiveItems();
	Level* getActiveLevel();
	Level* getLevel(int index);

	Player* getPlayer();

	UI* getUI();

private:
	//Items
	ItemVector mItems;
	void setActiveItems();

	//Levels
	LevelVector mLevels;

	//1
	Level1* mLevel1;

	//2
	LastLevel* mLastLevel;

	Player *mPlayer;

};

#endif