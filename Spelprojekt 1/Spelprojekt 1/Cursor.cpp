#include "Cursor.h"

using namespace std;

Cursor::Cursor(ResourceHandler &handler) :
mode(NORMAL)
{
	mNormalMouse = *handler.getTexture("mousecursor.png");
	mEyeMouse = *handler.getTexture("eyecursor.png");
	mOpenHandMouse = *handler.getTexture("openhand.png");
	mClosedHandMouse = *handler.getTexture("closedhand.png");
	mSpeechMouse = *handler.getTexture("speechbubble.png");

	mMouseCursor.setTexture(mEyeMouse);
	mMouseCursor.setScale(sf::Vector2f(0.2f, 0.2f));
}

Cursor::~Cursor()
{
}

//Update mouse cursor texture and origin depending on current active mode
void Cursor::update()
{
	switch (mode){
	case NORMAL:
		mMouseCursor.setTexture(mNormalMouse);
		mMouseCursor.setOrigin(sf::Vector2f(0.0f, 0.0f));
		break;
	case EYE:
		mMouseCursor.setTexture(mEyeMouse);
		mMouseCursor.setOrigin(sf::Vector2f(80.0f, 70.0f));
		break;
	case OPENHAND:
		mMouseCursor.setTexture(mOpenHandMouse);
		mMouseCursor.setOrigin(sf::Vector2f(80.0f, 70.0f));
		break;
	case CLOSEDHAND:
		mMouseCursor.setTexture(mClosedHandMouse);
		mMouseCursor.setOrigin(sf::Vector2f(80.0f, 70.0f));
		break;
	case INVENTORY:
		mMouseCursor.setTexture(mNormalMouse);
		mMouseCursor.setOrigin(sf::Vector2f(0.0f, 0.0f));
		break;
	case DIALOGUE:
		mMouseCursor.setTexture(mSpeechMouse);
		mMouseCursor.setOrigin(sf::Vector2f(0.0f, 0.0f));
		break;
	case DISABLED:
		mMouseCursor.setTexture(mNormalMouse);
		mMouseCursor.setOrigin(sf::Vector2f(0.0f, 0.0f));
		break;
	case MENU:
		mMouseCursor.setTexture(mNormalMouse);
		mMouseCursor.setOrigin(sf::Vector2f(0.0f, 0.0f));
		break;
	default:
		break;
	}
}

void Cursor::draw(sf::RenderWindow &window)
{
	if (mode != DISABLED)
	{
		window.draw(mMouseCursor);
	}
}

void Cursor::setMode(Mode newMode)
{
	mode = newMode;
}

void Cursor::setPosition(sf::Vector2f position)
{
	mMouseCursor.setPosition(position);
}

Cursor::Mode Cursor::getMode()
{
	return mode;
}

sf::Vector2f Cursor::getPosition()
{
	return mMouseCursor.getPosition();
}

//Return a small Rect at the mouse cursors position, small Rect makes sure cursor doesn't change "prematurely"
sf::FloatRect Cursor::getRect()
{
	return sf::FloatRect(getPosition(), sf::Vector2f(1.0f, 1.0f));
}