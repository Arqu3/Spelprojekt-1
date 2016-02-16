#include "Button.h"

using namespace std;

//Creates a sf::rectangleshape representing a button with given color
Button::Button(float x, float y, float width, float height, sf::Color col) :
mRect(sf::Vector2f(width, height)),
mMoveToPosition(x, y),
mIsOnPosition(true),
mDirection(0, 0),
mSpeed(100),
mMode(FloatRect)
{
	mRect.setPosition(x, y);
	mRect.setFillColor(col);
}

//Creates a sf::rectangleshape representing a button with given color
Button::Button(sf::RectangleShape &rect, sf::Color col) :
mRect(rect),
mMoveToPosition(rect.getPosition().x, rect.getPosition().y),
mDirection(0, 0),
mIsOnPosition(true),
mSpeed(100),
mMode(FloatRect)
{
	mRect.setPosition(rect.getPosition().x, rect.getPosition().y);
	mRect.setFillColor(col);
}

//Creates a sprite representing a button
Button::Button(ResourceHandler &handler, float x, float y, string textureName):
mTextureName(textureName),
mMoveToPosition(x, y),
mDirection(0, 0),
mIsOnPosition(true),
mSpeed(100),
mMode(Texture)
{
	mSprite.setTexture(*handler.getTexture(textureName));
	mSprite.setPosition(x, y);
}

//Creates a sprite representing a button
Button::Button(ResourceHandler &handler, sf::Vector2f &pos, string textureName):
mTextureName(textureName),
mMoveToPosition(pos),
mDirection(0, 0),
mIsOnPosition(true),
mSpeed(100),
mMode(Texture)
{
	mSprite.setTexture(*handler.getTexture(textureName));
	mSprite.setPosition(pos);
}

Button::~Button()
{

}

bool Button::isPressed(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		mPixelPos = sf::Mouse::getPosition(window);
		mWorldPos = window.mapPixelToCoords(mPixelPos);

		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			switch (mMode)
			{
			case FloatRect:
				if (mRect.getGlobalBounds().contains(mWorldPos))
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case Texture:
				if (mSprite.getGlobalBounds().contains(mWorldPos))
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			}
			break;
		}
	}
}

void Button::setPosition(float x, float y)
{
	switch (mMode)
	{
	case FloatRect:
		mRect.setPosition(x, y);
		mMoveToPosition = sf::Vector2f(x, y);
		mDirection = sf::Vector2f(0, 0);
		break;

	case Texture:
		mSprite.setPosition(x, y);
		mMoveToPosition = sf::Vector2f(x, y);
		mDirection = sf::Vector2f(0, 0);
		break;
	}
}
void Button::setPosition(sf::Vector2f &pos)
{
	switch (mMode)
	{
	case FloatRect:
		mRect.setPosition(pos);
		mMoveToPosition = pos;
		mDirection = sf::Vector2f(0, 0);
		break;
	case Texture:
		mSprite.setPosition(pos);
		mMoveToPosition = pos;
		mDirection = sf::Vector2f(0, 0);
		break;
	}
}

void Button::moveTo(float x, float y)
{
	switch (mMode)
	{
	case FloatRect:
		//Creates a unit-direction vector that the player follows
		mMoveToPosition = sf::Vector2f(x, y);

		float deltaX = (mMoveToPosition.x - mRect.getPosition().x);
		float deltaY = (mMoveToPosition.y - mRect.getPosition().y);

		mDirection = sf::Vector2f(deltaX, deltaY);

		float squareX = (deltaX * deltaX);
		float squareY = (deltaY * deltaY);

		float added = (squareX + squareY);
		float root = sqrt(added);

		sf::Vector2f unit(mDirection.x / root, mDirection.y / root);
		mDirection = unit;
		break;

	case Texture:
		//Creates a unit-direction vector that the player follows
		mMoveToPosition = sf::Vector2f(x, y);

		float deltaX = (mMoveToPosition.x - mSprite.getPosition().x);
		float deltaY = (mMoveToPosition.y - mSprite.getPosition().y);

		mDirection = sf::Vector2f(deltaX, deltaY);

		float squareX = (deltaX * deltaX);
		float squareY = (deltaY * deltaY);

		float added = (squareX + squareY);
		float root = sqrt(added);

		sf::Vector2f unit(mDirection.x / root, mDirection.y / root);
		mDirection = unit;
		break;
	}
}
void Button::moveTo(sf::Vector2f &pos)
{
	switch (mMode)
	{
	case FloatRect:
		//Creates a unit-direction vector that the player follows
		mMoveToPosition = pos;

		float deltaX = (mMoveToPosition.x - mRect.getPosition().x);
		float deltaY = (mMoveToPosition.y - mRect.getPosition().y);

		mDirection = sf::Vector2f(deltaX, deltaY);

		float squareX = (deltaX * deltaX);
		float squareY = (deltaY * deltaY);

		float added = (squareX + squareY);
		float root = sqrt(added);

		sf::Vector2f unit(mDirection.x / root, mDirection.y / root);
		mDirection = unit;
		break;

	case Texture:
		//Creates a unit-direction vector that the player follows
		mMoveToPosition = pos;

		float deltaX = (mMoveToPosition.x - mSprite.getPosition().x);
		float deltaY = (mMoveToPosition.y - mSprite.getPosition().y);

		mDirection = sf::Vector2f(deltaX, deltaY);

		float squareX = (deltaX * deltaX);
		float squareY = (deltaY * deltaY);

		float added = (squareX + squareY);
		float root = sqrt(added);

		sf::Vector2f unit(mDirection.x / root, mDirection.y / root);
		mDirection = unit;
		break;
	}
}

void Button::move(float deltaTime)
{
	switch (mMode)
	{
	case FloatRect:
		sf::FloatRect mMoveToRect(mMoveToPosition.x, mMoveToPosition.y, 2, 2);

		if (mRect.getGlobalBounds().intersects(mMoveToRect))
		{
			mIsOnPosition = true;
		}
		else
		{
			mIsOnPosition = false;
		}

		if (mIsOnPosition == false)
		{
			mSetPos += mDirection * mSpeed * deltaTime;
			mRect.setPosition(mSetPos);
		}
		break;

	case Texture:
		sf::FloatRect mMoveToRect(mMoveToPosition.x, mMoveToPosition.y, 2, 2);

		if (mSprite.getGlobalBounds().intersects(mMoveToRect))
		{
			mIsOnPosition = true;
		}
		else
		{
			mIsOnPosition = false;
		}

		if (mIsOnPosition == false)
		{
			mSetPos += mDirection * mSpeed * deltaTime;
			mSprite.setPosition(mSetPos);
		}
		break;
	}
}

void Button::update(float deltaTime)
{
	move(deltaTime);
}
void Button::draw(sf::RenderWindow &window)
{
	switch (mMode)
	{
	case FloatRect:
		window.draw(mRect);
		break;

	case Texture:
		window.draw(mSprite);
		break;
	}
}

sf::FloatRect Button::getRect()
{
	switch (mMode)
	{
	case FloatRect:
		return mRect.getGlobalBounds();
		break;

	case Texture:
		return mSprite.getGlobalBounds();
		break;
	}
}

std::string Button::getTexureName()
{
	switch (mMode)
	{
	case FloatRect:
		return "";
		break;

	case Texture:
		return mTextureName;
		break;
	}
}
float Button::setSpeed(float value)
{
	mSpeed = value;
}