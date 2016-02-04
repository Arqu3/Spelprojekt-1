#ifndef EVENTHANDLER
#define EVENTHANDLER

#include "LevelHandler.h"
#include "DialogueSystem.h"
#include "Inventory.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"


class EventHandler
{
public:
	EventHandler(LevelHandler &lHandler);
	~EventHandler();

	//Listen for mouse clicks
	void eventListen(sf::RenderWindow &window);

	void update();

private:
	//Check collision between a single rectangle and a point
	int checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point);

	//Check collision between a single rectangle and a point
	int checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point);

	//Check collision between a list of rectangles and a point
	int checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point);

	void mouseClick(sf::Event &event);

	//Member variables
	LevelHandler *mLHandler;
	DialogueSystem *mDialogueSystem;
	Inventory *mInventory;
	sf::Vector2f mWorldPos;
	sf::Vector2i mPixelPos;
	sf::Vector2f mViewMoveTo;
	float mXMove;
	float mYMove;
};

#endif