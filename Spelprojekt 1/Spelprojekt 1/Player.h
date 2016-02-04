#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

#include "ResourceHandler.h"
#include "SFML\System.hpp"
#include <cmath>

class Player{
public:
	Player(ResourceHandler &handler, sf::Vector2f &position, std::string textureName); 
	~Player();
	
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	sf::FloatRect getRect();
	sf::Vector2f getPosition();
	void setPosition(float x, float y);
	void moveToPosition(float x, float y);
	sf::Vector2f getDirection();
	void flipPlayer();
	bool isFacingLeft();
	sf::FloatRect getGlobalRect();

private:
	void move(float deltaTime);

	sf::Vector2f mPosition;
	sf::Vector2f mDirection;
	sf::Vector2f moveTo;
	sf::Sprite mSprite;

	bool mFacingLeft;
	bool isOnPosition;
	sf::FloatRect mRect;
	sf::FloatRect mMoveToRect;
	void waitForClick(sf::RenderWindow &window);
	
};
#endif
