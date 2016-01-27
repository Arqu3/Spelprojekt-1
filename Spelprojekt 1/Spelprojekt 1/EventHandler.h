#ifndef EVENTHANDLER
#define EVENTHANDLER

#include "LevelHandler.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"


class EventHandler
{
public:
	EventHandler(LevelHandler &lHandler);
	~EventHandler();

	void eventListen(sf::RenderWindow &window);
	void eventDraw(sf::RenderWindow &window);
	void eventUpdate(float deltaTime);
private:
	int checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point);
	int checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point);
	void mouseClick(sf::Event &event);
	LevelHandler *mLHandler;
};

#endif