#include "Player.h"

using namespace std;

Player::Player(ResourceHandler &handler, sf::Vector2f &position) :
mPosition(position),
isOnPosition(true),
moveTo(position)
{
	mSprite.setTexture(*handler.getTexture("test_2.png"));
	
}


Player::~Player()
{

}


void Player::move(float deltaTime)
{
	sf::FloatRect moveToRect(moveTo.x, moveTo.y, 10, 10);

	if (mRect.intersects(moveToRect))
	{
		isOnPosition = true;
	}
	else
	{
		isOnPosition = false;
	}


	if (isOnPosition == false)
	{

		float speed = 200.0f;
		
		mPosition += mDirection * speed * deltaTime;
	}

}


void Player::setPosition(float x, float y)
{
	//Creates a unit-direction vector that the player follows
	moveTo = sf::Vector2f(x, y);

	float deltaX = (moveTo.x - mPosition.x);
	float deltaY = (moveTo.y - mPosition.y);

	mDirection = sf::Vector2f(deltaX, deltaY);

	float squareX = (deltaX * deltaX);
	float squareY = (deltaY * deltaY);

	float added = (squareX + squareY);
	float root = sqrt(added);

	sf::Vector2f unit(mDirection.x / root, mDirection.y / root);
	mDirection = unit;
}


void Player::update(float deltaTime)
{
	mRect = sf::FloatRect(mPosition.x, mPosition.y, mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
	mSprite.setPosition(mPosition);
	move(deltaTime);
}



void Player::draw(sf::RenderWindow &window)
{
	window.draw(mSprite);
}



sf::FloatRect Player::getRect()
{
	return mRect;
}



sf::Vector2f Player::getPosition()
{
	return mPosition;
}

