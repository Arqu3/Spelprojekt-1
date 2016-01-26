#include "Player.h"

using namespace std;

Player::Player(ResourceHandler &handler, sf::Vector2f &position) :
mPosition(position),
isOnPosition(true),
moveTo(position)
{
	mSprite.setTexture(*handler.getTexture(0));
	
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

		float speed = 1.0f;
		
		mPosition += mDirection * speed * deltaTime;
	}

}


void Player::setPosition(float x, float y)
{
	moveTo = sf::Vector2f(x, y);
	mDirection = moveTo - mPosition;

	float unitX = mDirection.x;
	unitX = unitX * unitX;

	float unitY = mDirection.y;
	unitY = unitY * unitY;

	sf::Vector2f unitVector(unitX, unitY);
	mDirection = unitVector;
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

