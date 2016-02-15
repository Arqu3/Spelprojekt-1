#include "Button.h"

using namespace std;

//Creates a sf::rectangleshape representing a button with given color
Button::Button(float x, float y, float width, float height, sf::Color col) :
mRect(sf::Vector2f(width, height)),
mMoveToPosition(x, y),
mIsOnPosition(true),
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

