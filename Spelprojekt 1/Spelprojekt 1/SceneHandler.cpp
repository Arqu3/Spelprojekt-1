#include "SceneHandler.h"

using namespace std;

SceneHandler::SceneHandler(ResourceHandler &handler)
{
	mBackground.setTexture(*handler.getTexture(0));
	mBackground.setPosition(0, 0);

}

SceneHandler::~SceneHandler()
{
}

void SceneHandler::update()
{

}

void SceneHandler::draw(sf::RenderWindow &window)
{

}

void SceneHandler::drawScene(sf::RenderWindow &window)
{
	window.draw(mBackground);

}

