#ifndef EVENTHANDLER
#define EVENTHANDLER

#include "Player.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"


class EventHandler
{
public:
	EventHandler(ResourceHandler &handler);
	~EventHandler();
	void eventListen(sf::RenderWindow &window);
	void eventDraw(sf::RenderWindow &window);
	void eventUpdate(float deltaTime);
private:
	int checkCollision(sf::FloatRect &boundingBox, sf::Vector2f &point);
	void mouseClick(sf::Event &event);
	Player *player;
	ResourceHandler* mHandler;
};

#endif