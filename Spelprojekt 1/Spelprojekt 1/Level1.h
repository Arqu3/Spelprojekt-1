#ifndef INCLUDED_LEVEL1
#define INCLUDED_LEVEL1

#include "Level.h"
#include "ResourceHandler.h"
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
private:
	
	void addRect(sf::FloatRect);
	typedef std::vector<sf::FloatRect> rectVector;
	rectVector mRects;
	sf::RectangleShape background;
	sf::Music backgroundMusic;
	sf::Sound ambientSound;
};
#endif
