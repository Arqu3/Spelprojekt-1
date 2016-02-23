#ifndef INCLUDED_CURSOR
#define INCLUDED_CURSOR

#include "ResourceHandler.h"
#include "SFML\System.hpp"

class Cursor{
public:
	Cursor(ResourceHandler &handler);
	~Cursor();

	enum Mode
	{
		NORMAL,
		EYE,
		OPENHAND,
		CLOSEDHAND,
		SPEECH,
		INVENTORY,
		DIALOGUE,
		DISABLED,
		MENU,
		SCENECHANGE
	};

	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);

	void setMode(Mode newMode);
	void setPosition(sf::Vector2f position);

	Mode getMode();
	sf::Vector2f getPosition();
	sf::FloatRect getRect();

private:
	Mode mode;

	sf::Texture mNormalMouse;
	sf::Texture mOpenHandMouse;
	sf::Texture mClosedHandMouse;
	sf::Texture mSpeechMouse;
	sf::Texture mEyeMouse;
	sf::Texture mSceneChangeMouse;
	sf::Sprite mMouseCursor;

	sf::Vector2i mPixelPos;
	sf::Vector2f mWorldPos;
};

#endif