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
		mSprite.setOrigin(400, 700);
	}
	else
	{
		//Spritesheet
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setOrigin(300, 500);
	}

	mWalk = false;
	mFrameTime = 0.06f;
	mCurrentTime = 0;
	mCurrentFrame = 0;
	mFrameXOffset = 0;
	mFrameYOffset = 0;
	if (textureName == "Thomas.png")
	{
		mTexture.loadFromFile("Resources/Textures/ThomasWalk.png");
		mSprite.setTexture(mTexture);
		mSprite.setTextureRect(sf::IntRect(0, 0, 800, 800));
	}
	else if (textureName == "Hilma.png")
	{
		mTexture.loadFromFile("Resources/Textures/HilmaWalk.png");
		mSprite.setTexture(mTexture);
		mSprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
	}

	//Sounds
	mWalkingSound.setBuffer(*handler.getSound("FootSteps.ogg"));
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

		float speed = 150.0f;
		
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
		if (mWalkingSound.getStatus() != 2)
		{
			mWalkingSound.play();
		}
		if (mThomasActive)
		{
			if (mCurrentTime >= mFrameTime)
			{
				mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 800, mFrameYOffset * 800, 800, 800));
				if (mCurrentFrame < 27)
				{
					mFrameXOffset += 1;
					if (mFrameXOffset % 11 == 10)
					{
						mFrameYOffset++;
					}
					if (mFrameXOffset >= 10)
					{
						mFrameXOffset = 0;
					}
					mCurrentFrame += 1;
				}
				else
				{
					mCurrentFrame = 0;
					mFrameXOffset = 0;
					mFrameYOffset = 0;
				}
				mCurrentTime = 0;
			}
		}
		else
		{
			if (mCurrentTime >= mFrameTime)
			{
				mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 600, mFrameYOffset * 600, 600, 600));
				if (mCurrentFrame < 27)
				{
					mFrameXOffset += 1;
					if (mFrameXOffset % 8 == 7)
					{
						mFrameYOffset++;
					}
					if (mFrameXOffset >= 7)
					{
						mFrameXOffset = 0;
					}
					mCurrentFrame += 1;
				}
				else
				{
					mCurrentFrame = 0;
					mFrameXOffset = 0;
					mFrameYOffset = 0;
				}
				mCurrentTime = 0;
			}
		}
	}
	else
	{
		mWalkingSound.pause();
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