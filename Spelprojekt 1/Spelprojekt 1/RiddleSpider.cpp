#include "RiddleSpider.h"

using namespace std;

RiddleSpider::RiddleSpider(ResourceHandler &handler, sf::Vector2f position) :
mPosition(position),
mState(INACTIVE),
mTimer(0),
mTextCounter(-1),
mTexts()
{
	mSprite.setTexture(*handler.getTexture("RiddleSpider.png"));
	mSprite.setPosition(position);
	mSprite.setScale(0.1f, 0.1f);
	mFont.loadFromFile("Resources/Fonts/ShadowsIntoLight.ttf");
}

RiddleSpider::~RiddleSpider()
{

}

void RiddleSpider::update(float deltaTime)
{
	switch (mState)
	{
	case ENTERING:
		moveDown(deltaTime);
		break;

	case LEAVING:
		moveUp(deltaTime);
		break;

	case IDLE:
		idleMove(deltaTime);
		break;
	}

	mSprite.setPosition(mPosition);
}

void RiddleSpider::draw(sf::RenderWindow &window)
{
	window.draw(mSprite);
}

void RiddleSpider::moveUp(float deltaTime)
{
	if (mPosition.y + mSprite.getGlobalBounds().height > 0)
	{
		mPosition.y -= 100.0f * deltaTime;
	}
}

void RiddleSpider::moveDown(float deltaTime)
{
	if (mPosition.y + mSprite.getGlobalBounds().height < 200)
	{
		mPosition.y += 100.0f * deltaTime;
	}
}

void RiddleSpider::idleMove(float deltaTime)
{
	mTimer++;
	if (mTimer >= 500)
	{
		mTimer = 0;
	}

	if (mTimer <= 250)
	{
		mPosition.y += 50.0f * deltaTime;
	}
	else if (mTimer >= 251)
	{
		mPosition.y -= 50.0f * deltaTime;
	}
}

void RiddleSpider::setState(State newState)
{
	mTimer = 0;
	mState = newState;
}

RiddleSpider::State RiddleSpider::getState()
{
	return mState;
}

sf::FloatRect RiddleSpider::getRect()
{
	return mSprite.getGlobalBounds();
}

void RiddleSpider::addText(string text)
{
	mTextCounter++;
	mTexts.push_back(sf::Text());
	mTexts[mTextCounter].setCharacterSize(18);
	mTexts[mTextCounter].setStyle(sf::Text::Bold);
	mTexts[mTextCounter].setColor(sf::Color::Black);
	mTexts[mTextCounter].setFont(mFont);
}