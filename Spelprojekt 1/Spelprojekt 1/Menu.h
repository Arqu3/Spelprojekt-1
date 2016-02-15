#ifndef INCLUDED_MENU
#define INCLUDED_MENU

#include "ResourceHandler.h"
#include "SFML\System.hpp"

class Cursor{
public:
	Cursor(ResourceHandler &handler);
	~Cursor();

	enum Menu
	{
		HAT,
		INVENTORY,
		CLUE,
		SETTINGS
	};

	void update();
	void draw(sf::RenderWindow &window);

	void setMode(Menu newMode);
	void setPosition(sf::Vector2f position);

	Menu getMode();
	sf::Vector2f getPosition();
	sf::FloatRect getRect();

private:
	Menu menu;

	sf::Sprite mHatIcon;
	sf::Sprite mMenuIcon;
	sf::Sprite mHatMenu;
	sf::Sprite mMenu;
};

#endif