#include "Level1.h"

Level1::Level1(ResourceHandler &handler)
{
	background.setSize(sf::Vector2f(800, 600));
	background.setTexture(handler.getTexture("thomasrum.png"));
	//backgroundMusic = *handler.getMusic(0);
	ambientSound.setBuffer(*handler.getSound(0));
}

Level1::~Level1()
{
	mRects.clear();
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

void Level1::addRect(sf::FloatRect* rect)
{
	mRects.push_back(rect);
}

void Level1::removeRect(int index)
{
	std::swap(mRects[index], mRects.back());
}

void Level1::clearScene()
{
	mRects.clear();
}

void Level1::internalSwap(int num, ResourceHandler &handler)
{
	if (num == 0){
		background.setTexture(handler.getTexture("thomasrum.png"));
	}
	else{
		background.setTexture(handler.getTexture("thomasbyra.png"));
	}
}

void Level1::changeScene(int num, ResourceHandler &handler)
{
	clearScene();
	internalSwap(num, handler);
}

Level1::rectVector Level1::getRects()
{
	return mRects;
}