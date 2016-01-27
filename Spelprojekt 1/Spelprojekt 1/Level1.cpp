#include "Level1.h"

Level1::Level1(ResourceHandler &handler):
mRects(),
mPlayRects(),
mIsActive(false)
{
	background.setSize(sf::Vector2f(1024, 576));
	background.setTexture(handler.getTexture("Test3.png"));
	//backgroundMusic = *handler.getMusic(0);
	//ambientSound.setBuffer(*handler.getSound(0));

	mBackground.setTexture(*handler.getTexture("Test3.png"));
	mBackground.setPosition(sf::Vector2f(0, 0));

	sf::FloatRect* test = new sf::FloatRect(100, 100, 400, 400);

	mPlayRects.push_back(test);
}

Level1::~Level1()
{
	mRects.clear();
	mPlayRects.clear();
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

void Level1::draw(sf::RenderWindow &window)
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

const Level::rectVector Level1::getPlayRects()
{
	return mPlayRects;
}

void Level1::toggleActive()
{
	mIsActive = !mIsActive;
}

bool Level1::isActive()
{
	return mIsActive;
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