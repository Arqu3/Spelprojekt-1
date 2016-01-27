#include "Level1.h"

Level1::Level1(ResourceHandler &handler)
{
	background.setSize(sf::Vector2f(800, 600));
	background.setTexture(handler.getTexture(0));
	backgroundMusic = *handler.getMusic(0);
	ambientSound.setBuffer(*handler.getSound(0));
}

Level1::~Level1()
{
}

void Level1::playBackgroundMusic()
{
	backgroundMusic.setPitch(0.5);
	backgroundMusic.play();
}

void Level1::playAmbience()
{
	ambientSound.play();
}

void Level1::drawBackground(sf::RenderWindow &window)
{
	window.draw(background);
}

void Level1::addRect(sf::FloatRect rect)
{
	mRects.push_back(rect);
}

void Level1::removeRect(int index)
{
	mRects.erase(mRects.begin + index);
}

Level1::rectVector Level1::getRects()
{
	return mRects;
}