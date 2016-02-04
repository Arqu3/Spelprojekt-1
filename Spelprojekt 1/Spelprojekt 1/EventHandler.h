#ifndef EVENTHANDLER
#define EVENTHANDLER

#include "LevelHandler.h"
#include "DialogueSystem.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"


class EventHandler
{
public:
	EventHandler(LevelHandler &lHandler, DialogueSystem &dSystem);
	~EventHandler();

	//Listen for mouse clicks
	void eventListen(sf::RenderWindow &window);

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
	sf::Vector2f mWorldPos;
	sf::Vector2i mPixelPos;
};

#endif