#ifndef INCLUDED_BUTTON
#define INCLUDED_BUTTON

#include "ResourceHandler.h"

class Button
{
public:
	Button(float x, float y, float width, float height, sf::Color col);
	Button(sf::RectangleShape &rect, sf::Color col);
	Button(ResourceHandler &handler, float x, float y, std::string textureName);
	Button(ResourceHandler &handler, sf::Vector2f &pos, std::string textureName);
	~Button();

	bool isPressed();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f &pos);

	void moveTo(float x, float y);
	void moveTo(sf::Vector2f &pos);
	
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);

	sf::FloatRect getRect();
	std::string getTexureName();
	float setSpeed(float value);

private:
	sf::RectangleShape mRect;
	sf::Vector2f mMoveToPosition;
	bool mIsOnPosition;
	float mSpeed;
	sf::Sprite mSprite;
	std::string mTextureName;

	enum Mode
	{
		FloatRect,
		Texture
	};
	Mode mMode;
};

#endif