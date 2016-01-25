#ifndef INCLUDED_SCENEHANDLER
#define INCLUDED_SCENEHANDLER

#include "ResourceHandler.h"
#include "SFML\Window.hpp"

class SceneHandler{
public:
	SceneHandler(ResourceHandler &handler);
	~SceneHandler();
	void update();
	void draw(sf::RenderWindow &window);

private:
	void drawScene(sf::RenderWindow &window);

	//Textures
	sf::Sprite mBackground;

};

#endif;