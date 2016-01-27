#ifndef INCLUDED_LEVEL1
#define INCLUDED_LEVEL1

#include "Level.h"
#include "SFML\System.hpp"

class Level1: public Level{
public:
	Level1(ResourceHandler &handler);
	~Level1();

	void playBackgroundMusic();
	void playAmbience();
	void drawBackground(sf::RenderWindow &window);
	rectVector getRects();
	void removeRect(int index);
	void clearScene();
	void internalSwap(int num, ResourceHandler &handler);
	void changeScene(int num, ResourceHandler &handler);
private:
	
	void addRect(sf::FloatRect* rect);
	rectVector mRects;
	sf::RectangleShape background;
	sf::Music backgroundMusic;
	sf::Sound ambientSound;
};
#endif
