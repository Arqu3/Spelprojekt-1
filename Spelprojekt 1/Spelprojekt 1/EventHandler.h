#ifndef EVENTHANDLER
#define EVENTHANDLER

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"


class EventHandler
{
public:
	EventHandler();
	~EventHandler();
	void eventListen(sf::RenderWindow &window);
private:
	int checkCollision(sf::FloatRect &boundingBox, sf::Vector2f &point);
	void mouseClick(sf::Event &event);
};

#endif