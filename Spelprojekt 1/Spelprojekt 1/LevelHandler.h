#ifndef INCLUDED_LH
#define INCLUDED_LH

#include "Player.h"
#include "Level.h"
#include "Level1.h"
#include "Level3.h"
#include "LastLevel.h"
#include "Item.h"
#include <vector>

class LevelHandler
{
public:
	LevelHandler(ResourceHandler &handler);
	~LevelHandler();
	typedef std::vector<Level*> LevelVector;

	//Update
	void update(float deltaTime, sf::RenderWindow &window, ResourceHandler &handler);

	//Draw
	void draw(sf::RenderWindow &window);

	void setActiveLevel(int num, ResourceHandler &handler, bool isFirstLevel, sf::RenderWindow &window);

	Level* getActiveLevel();
	Level* getLevel(int index);

	UI* getUI();
private:

	//Levels
	LevelVector mLevels;

	//1
	Level1* mLevel1;

	//2
	Level3* mLevel3;
	
	//3
	LastLevel* mLastLevel;
};

#endif