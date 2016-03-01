#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL

#include "ResourceHandler.h"
#include "Inventory.h"
#include "DialogueSystem.h"
#include "Player.h"
#include "Cursor.h"
#include "UI.h"
#include "Clue.h"
#include "RiddleSpider.h"

class Level
{
public:
	//Items
	typedef std::vector<Item*> ItemVector;
	virtual ItemVector getItems() = 0;
	virtual void addItem(Item* item) = 0;
	virtual void removeItem(Item* item) = 0;

	//Player
	virtual Player* getPlayer() = 0;

	//UI
	virtual UI* getUI() = 0;

	//Rectangle for levels
	typedef std::vector<sf::FloatRect*> rectVector;

	//Sound
	virtual void playBackgroundMusic() = 0;
	virtual void playAmbience() = 0;

	//Draw
	virtual void drawBackground(sf::RenderWindow &window) = 0;
	virtual void drawForeground(sf::RenderWindow &window) = 0;
	virtual void drawUI(sf::RenderWindow &window) = 0;

	//Rectangle functions
	virtual rectVector getRects() = 0;
	virtual void addRect(sf::FloatRect* rect) = 0;
	virtual void removeRect(int index) = 0;
	virtual const rectVector getPlayRects() = 0;

	//View
	virtual sf::View getView() = 0;
	virtual void moveViewWithPlayer(float playerPos) = 0;

	//Scene functions
	virtual void clearScene() = 0;
	virtual void internalSwap(int num) = 0;
	virtual void changeScene(int num) = 0;
	virtual int getActiveScene() = 0;
	virtual void toggleActive(ResourceHandler &handler, sf::RenderWindow &window) = 0;
	virtual bool isActive() = 0;

	//Eventstuff
	virtual void eventListen(sf::RenderWindow &window) = 0;
	virtual void mouseClick(sf::Event &event) = 0;
	virtual void update(sf::RenderWindow &window, float deltaTime) = 0;

	//Level Complete
	virtual bool isLevelComplete() = 0;
};

#endif