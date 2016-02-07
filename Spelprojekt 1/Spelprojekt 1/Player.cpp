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
		//Spritesheet
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setOrigin(300, 900);

		//No spritesheet
		//mSprite.setScale(sf::Vector2f(0.08f, 0.08f));
		//mSprite.setOrigin(1050, 3250);
	}
	else
	{
		//Spritesheet
		mSprite.setScale(sf::Vector2f(0.25f, 0.25f));
		mSprite.setOrigin(100, 780);

		//No spritesheet
		//mSprite.setScale(sf::Vector2f(0.04f, 0.04f));
		//mSprite.setOrigin(600, 2100);
	}

	mWalk = false;
	mFrameTime = 0.02f;
	mCurrentTime = 0;
	mCurrentFrame = 0;
	if (textureName == "Thomas.png")
	{
		mThomasWalk.loadFromFile("Resources/Textures/ThomasWalk.png");
		mTexture.loadFromImage(mThomasWalk, sf::IntRect(100, 0, 400, 1080));
		mSprite.setTexture(mTexture);
	}
	else if (textureName == "Hilma.png")
	{
		mHilmaWalk.loadFromFile("Resources/Textures/HilmaWalk.png");
		mTexture.loadFromImage(mThomasWalk, sf::IntRect(55, 0, 250, 1080));
		mSprite.setTexture(mTexture);
	}
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
		mWalk = false;
	}
	else
	{
		isOnPosition = false;
		mWalk = true;
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
	mCurrentTime += deltaTime;
	if (mWalk)
	{
		if (mThomasActive)
		{
			if (mCurrentTime >= mFrameTime)
			{
				//Issues with overlapping sprites in spritesheet, 2 maybe?, Frame 13? Fix by increasing distance between all sprites by 5 pixels?
				mTexture.loadFromImage(mThomasWalk, sf::IntRect(100 + mCurrentFrame * 400, 0, 400, 1080));
				mSprite.setTexture(mTexture);
				if (mCurrentFrame < 50)
				{
					mCurrentFrame += 1;
				}
				else
				{
					mCurrentFrame = 0;
				}
				mCurrentTime = 0;
			}
		}
		else
		{
			if (mCurrentTime >= mFrameTime)
			{
				mTexture.loadFromImage(mHilmaWalk, sf::IntRect(55 + mCurrentFrame * 300, 0, 250, 1080));
				mSprite.setTexture(mTexture);
				if (mCurrentFrame < 47)
				{
					mCurrentFrame += 1;
				}
				else
				{
					mCurrentFrame = 0;
				}
				mCurrentTime = 0;
			}
		}
	}

	mRect = sf::FloatRect(mPosition.x, mPosition.y, 10, 10);
	mSprite.setPosition(mPosition);
	move(deltaTime);
}



void Player::draw(sf::RenderWindow &window)
{
	//Help Rectangle to visualize getGlobalRect()
	/*sf::RectangleShape rectangle(mPosition);
	rectangle.setPosition(sf::Vector2f(mPosition.x - 90, mPosition.y - 230));
	rectangle.setSize(sf::Vector2f(120, 250));
	window.draw(rectangle);*/

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

//Return a Rect that covers the whole character
sf::FloatRect Player::getGlobalRect()
{
	//Creates a FloatRect at Players current position and size, compensated for previously set Origin and Scale
	//TODO - Change depending on mFacingLeft?
	return sf::FloatRect(sf::Vector2f(mPosition.x - 90, mPosition.y - 270), sf::Vector2f(120, 300));

	//TODO - Add separate one for Hilma with correct offsets for Origin and Scale, if (!mThomasActive)

	//return mSprite.getGlobalBounds(); //Doesn't work with spritesheet
}

void Player::setCurrentAnimation(std::string animation)
{
	if (animation == "Walk")
	{
		mWalk = true;
	}
	else if (animation == "Push")
	{
		mWalk = false;
		mPush = true;
	}
	else
	{
		mWalk = false;
		mPush = false;
	}
}

void Player::setThomasActive(bool thomasActive)
{
	if (thomasActive)
	{
		mThomasActive = true;
	}
	else
	{
		mThomasActive = false;
	}
}