#include "Player.h"

using namespace std;

Player::Player(ResourceHandler &handler, sf::Vector2f &position) :
mPosition(position),
isOnPosition(true),
moveTo(position),
mActiveAnimation("Walk"),
mWalk(false),
mFrameTime(0.03f),
mCurrentTime(0),
mCurrentFrame(0),
mFrameXOffset(0),
mFrameYOffset(0),
mSpeed(100.0f),
mFacingLeft(true)
{
	//Sounds
	//mWalkingSound.setBuffer(*handler.getSound("FootSteps.ogg"));

	//Spritesheet - Thomas
	mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
	mSprite.setOrigin(400, 700);

	mThomasTexture = *handler.getTexture("ThomasWalk.png");
	mHilmaTexture = *handler.getTexture("HilmaWalk.png");
	mHilmaPushTexture = *handler.getTexture("HilmaPush.png");

	mSprite.setTexture(mThomasTexture);
	mSprite.setTextureRect(sf::IntRect(0, 0, 800, 800));
}


Player::~Player()
{

}


void Player::move(float deltaTime)
{
	mMoveToRect = sf::FloatRect(moveTo.x, moveTo.y, 10, 10);

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
		mPosition += mDirection * mSpeed * deltaTime;
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

	// Walk Animations
	if (mActiveAnimation == "Walk" && mWalk)
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

	//Push Animation
	if (mActiveAnimation == "Push")
	{
		if (mCurrentTime >= mFrameTime)
		{
			mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 600, mFrameYOffset * 600, 600, 600));
			if (mCurrentFrame < 27)
			{
				mFrameXOffset += 1;
				if (mFrameXOffset % 10 == 9)
				{
					mFrameYOffset++;
				}
				if (mFrameXOffset >= 9)
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

	//If Player is moving to the left (getDirection.x < 0) and isn't already facing left, flip Player
	if (getDirection().x < 0 && !isFacingLeft())
	{
		flipPlayer();
	}
	//If Player is moving to the right (getDirection.x > 0) and is facing left, flip Player
	if (getDirection().x > 0 && isFacingLeft())
	{
		flipPlayer();
	}

	mRect = sf::FloatRect(mPosition.x, mPosition.y, 10, 10);
	mSprite.setPosition(mPosition);
	move(deltaTime);
}



void Player::draw(sf::RenderWindow &window)
{
	//Help Rectangles to visualize getGlobalRect()
	/*sf::RectangleShape rectangle(mPosition);
	rectangle.setPosition(sf::Vector2f(mPosition.x - 50, mPosition.y - 200));
	rectangle.setSize(sf::Vector2f(100, 220));
	sf::RectangleShape rectangleHilma(mPosition);
	rectangleHilma.setPosition(sf::Vector2f(mPosition.x - 30, mPosition.y - 115));
	rectangleHilma.setSize(sf::Vector2f(50, 130));
	if (mThomasActive)
		window.draw(rectangle);
	else
		window.draw(rectangleHilma);*/

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
	sf::FloatRect globalRect;
	//Creates a FloatRect at Players current position and size, compensated for previously set Origin and Scale
	if (mThomasActive)
	{
		globalRect = sf::FloatRect(sf::Vector2f(mPosition.x - 50, mPosition.y - 200), sf::Vector2f(100, 220));
	}
	else
	{
		globalRect = sf::FloatRect(sf::Vector2f(mPosition.x - 30, mPosition.y - 115), sf::Vector2f(50, 130));
	}

	return globalRect;
}

void Player::setActiveAnimation(std::string animation)
{
	if (animation == "Walk")
	{
		//Avoid starting animation over if already walking
		if (mActiveAnimation != "Walk")
		{
			mCurrentFrame = 0;
			mFrameXOffset = 0;
			mFrameYOffset = 0;

			if (mThomasActive)
			{
				mSprite.setTexture(mThomasTexture);
			}
			else
			{
				mSprite.setTexture(mHilmaTexture);
			}
		}
		mWalk = true;
	}
	else if (animation == "Push")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
		mSprite.setTexture(mHilmaPushTexture);
		mWalk = false;
	}
	else if (animation == "Idle")
	{
		if (mThomasActive)
		{
			mSprite.setTexture(mThomasTexture);
			mSprite.setTextureRect(sf::IntRect(0, 0, 800, 800));
		}
		else
		{
			mSprite.setTexture(mHilmaTexture);
			mSprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
		}
		mWalk = false;
	}
	else
	{
		mWalk = false;
	}

	mActiveAnimation = animation;
}

std::string Player::getActiveAnimation()
{
	return mActiveAnimation;
}

void Player::togglePlayer()
{
	mThomasActive = !mThomasActive;

	if (mThomasActive)
	{
		mSprite.setTexture(mThomasTexture);
		mSprite.setTextureRect(sf::IntRect(0, 0, 800, 800));
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setOrigin(400, 700);
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
		mFacingLeft = true;
	}
	else
	{
		mSprite.setTexture(mHilmaTexture);
		mSprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
		mSprite.setScale(sf::Vector2f(0.25f, 0.25f));
		mSprite.setOrigin(300, 500);
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
		mFacingLeft = true;
	}
}

float Player::getSpeed()
{
	return mSpeed;
}

void Player::setSpeed(float speed)
{
	mSpeed = speed;
}

bool Player::getIsOnPosition()
{
	return isOnPosition;
}