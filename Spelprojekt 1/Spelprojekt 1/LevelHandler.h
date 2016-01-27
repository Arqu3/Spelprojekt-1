#ifndef INCLUDED_LH
#define INCLUDED_LH

#include "ResourceHandler.h"
#include <vector>

class LevelHandler
{
public:
	LevelHandler(ResourceHandler &handler);
	~LevelHandler();

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);

	void setActiveLevel(int num);

	sf::Sprite* getItems();

private:
	typedef std::vector<sf::Sprite*> SpriteVector;
	SpriteVector items;

	void setActiveItems();

};

#endif