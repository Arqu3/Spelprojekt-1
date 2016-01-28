#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL

#include "ResourceHandler.h"

class Level
{
public:
	//Rectangle for levels
	typedef std::vector<sf::FloatRect*> rectVector;

	//Sound
	virtual void playBackgroundMusic() = 0;
	virtual void playAmbience() = 0;

	//Draw
	virtual void draw(sf::RenderWindow &window) = 0;

	//Rectangle functions
	virtual rectVector getRects() = 0;
	virtual void addRect(sf::FloatRect* rect) = 0;
	virtual void removeRect(int index) = 0;
	virtual const rectVector getPlayRects() = 0;

	//Scene functions
	virtual void clearScene() = 0;
	virtual void internalSwap(int num) = 0;
	virtual void changeScene(int num) = 0;
	virtual int getActiveScene() = 0;
	virtual void toggleActive() = 0;
	virtual bool isActive() = 0;
};

#endif