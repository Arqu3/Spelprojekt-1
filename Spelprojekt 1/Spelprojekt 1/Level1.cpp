#include "Level1.h"

Level1::Level1(ResourceHandler &handler):
mRects(),
mPlayRects(),
mIsActive(false)
{
	background.setSize(sf::Vector2f(1024, 576));
	background.setTexture(handler.getTexture("Test3.png"));
	backgroundfishtank.setSize(sf::Vector2f(1024, 576));
	backgroundfishtank.setTexture(handler.getTexture("test_2.png"));
	//backgroundMusic = *handler.getMusic(0);
	//ambientSound.setBuffer(*handler.getSound(0));

	rectangle.setPosition(sf::Vector2f(140, 480));
	rectangle.setSize(sf::Vector2f(400, 30));
	//sf::FloatRect* test = new sf::FloatRect(110, 360, 660, 200);
	//sf::FloatRect* testSceneChange = new sf::FloatRect(440, 150, 210, 70);

	mPlayRects.push_back(createRect(110, 360, 660, 200));
	mRects.push_back(createRect(440, 150, 210, 70));
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
	if (mActiveScene == 0)
	{
		window.draw(background);
	}
	else
	{
		window.draw(backgroundfishtank);
	}
	window.draw(rectangle);
}

void Level1::addRect(sf::FloatRect* rect)
{
	mRects.push_back(rect);
}

void Level1::removeRect(int index)
{
	//std::swap(mRects[index], mRects.back());
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
	mPlayRects.clear();
}

void Level1::internalSwap(int num)
{
	if (num == 0){
		mActiveScene = 0;
		mPlayRects.push_back(createRect(110, 360, 660, 200));
		mRects.push_back(createRect(440, 150, 210, 70));
	}
	else{
		mActiveScene = 1;
		mPlayRects.push_back(createRect(140, 480, 400, 30));
		mRects.push_back(createRect(440, 150, 210, 70));
	}
}

void Level1::changeScene(int num)
{
	clearScene();
	internalSwap(num);
}

int Level1::getActiveScene()
{
	return mActiveScene;
}

Level1::rectVector Level1::getRects()
{
	return mRects;
}

sf::FloatRect* Level1::createRect(int positionX, int positionY, int sizeX, int sizeY)
{
	sf::FloatRect* floatRect = new sf::FloatRect(positionX, positionY, sizeX, sizeY);
	return floatRect;
}