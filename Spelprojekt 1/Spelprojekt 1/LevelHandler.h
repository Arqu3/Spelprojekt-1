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
	void update(float deltaTime);

	//Draw
	void draw(sf::RenderWindow &window);

	void setActiveLevel(int num);

	ItemVector getActiveItems();
	Level* getActiveLevel();
	Level* getLevel(int index);

	Player* getPlayer();
	void togglePlayer();

private:
	//Items
	ItemVector mItems;
	void setActiveItems();

	//Player
	Player* mPlayer;
	Player* mThomas;
	Player* mHilma;
	std::string activePlayer;

	//Levels
	LevelVector mLevels;

	//1
	Level1* mLevel1;

	//2
	LastLevel* mLastLevel;

};

#endif