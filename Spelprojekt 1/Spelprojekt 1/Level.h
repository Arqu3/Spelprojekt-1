#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL

#include "ResourceHandler.h"

class Level
{
public:
	typedef std::vector<sf::FloatRect*> rectVector;
	virtual void playBackgroundMusic() = 0;
	virtual void playAmbience() = 0;
	virtual void drawBackground(sf::RenderWindow &window) = 0;
	virtual rectVector getRects() = 0;
	virtual void addRect(sf::FloatRect) = 0;
	virtual void removeRect(int index) = 0;
	virtual void clearScene() = 0;
	virtual void internalSwap(int num, ResourceHandler &handler) = 0;
	virtual void changeScene(int num, ResourceHandler &handler) = 0;
};

#endif