#include "Player.h"

using namespace std;

Player::Player(ResourceHandler &handler, sf::Vector2f &position, std::string textureName) :
mPosition(position),
isOnPosition(true),
moveTo(position)
{
	mSprite.setTexture(*handler.getTexture(textureName));
	if (textureName == "Thomas.png")
	{
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setOrigin(300, 900);
		//mSprite.setScale(sf::Vector2f(0.08f, 0.08f));
		//mSprite.setOrigin(1050, 3250);
	}
	else
	{
		mSprite.setScale(sf::Vector2f(0.04f, 0.04f));
		mSprite.setOrigin(600, 2100);
	}

	mFrameTime = 0.001f;
	mCurrentTime = 0;
	mCurrentFrame = 1;
	mThomasWalk.loadFromFile("Resources/Textures/ThomasWalk.png");
	mTexture.loadFromImage(mThomasWalk, sf::IntRect(100, 0, 400, 1080));
	mSprite.setTexture(mTexture);
}


Player::~Player()
{

}


void Player::move(float deltaTime)
{
	mMoveToRect = sf::FloatRect(moveTo.x, moveTo.y, 2, 2);

	if (mRect.intersects(mMoveToRect))
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
	mPosition = sf::Vector2f(x, y);
	mDirection = sf::Vector2f(0, 0);
}

void Player::moveToPosition(float x, float y)
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
	//Animation
	//mCurrentTime += deltaTime;
	////if (mCurrentTime >= mFrameTime)
	////{
	//	if (mCurrentFrame == 1)
	//	{
	//		mTexture.loadFromImage(mThomasWalk, sf::IntRect(mCurrentFrame * 500, 0, 400, 1080));
	//	}
	//	else if (mCurrentFrame < 3)
	//	{
	//		mTexture.loadFromImage(mThomasWalk, sf::IntRect(mCurrentFrame * 450, 0, 400, 1080));
	//	}
	//	else if (mCurrentFrame < 4)
	//	{
	//		mTexture.loadFromImage(mThomasWalk, sf::IntRect(mCurrentFrame * 430, 0, 400, 1080));
	//	}
	//	else if (mCurrentFrame < 5)
	//	{
	//		mTexture.loadFromImage(mThomasWalk, sf::IntRect(mCurrentFrame * 425, 0, 400, 1080));
	//	}
	//	else if (mCurrentFrame < 7)
	//	{
	//		mTexture.loadFromImage(mThomasWalk, sf::IntRect(mCurrentFrame * 418, 0, 400, 1080));
	//	}
	//	else if (mCurrentFrame < 8)
	//	{
	//		mTexture.loadFromImage(mThomasWalk, sf::IntRect(mCurrentFrame * 415, 0, 400, 1080));
	//	}
	//	else if (mCurrentFrame < 9)
	//	{
	//		mTexture.loadFromImage(mThomasWalk, sf::IntRect(mCurrentFrame * 412, 0, 400, 1080));
	//	}
	//	else
	//	{
	//		mTexture.loadFromImage(mThomasWalk, sf::IntRect(mCurrentFrame * 411, 0, 400, 1080));
	//	}
	//	mSprite.setTexture(mTexture);
	//	if (mCurrentFrame < 9)
	//	{
	//		mCurrentFrame += 1;
	//	}
	//	else
	//	{
	//		mCurrentFrame = 0;
	//	}
	//	mCurrentTime = 0;
	////}
	mRect = sf::FloatRect(mPosition.x, mPosition.y, 10, 10);
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

sf::Vector2f Player::getDirection()
{
	return mDirection;
}

void Player::flipPlayer()
{
	mFacingLeft = !mFacingLeft;
	mSprite.scale(sf::Vector2f(-1, 1));
}

bool Player::isFacingLeft()
{
	return mFacingLeft;
}

sf::FloatRect Player::getGlobalRect()
{
	return mSprite.getGlobalBounds();
}