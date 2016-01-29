#ifndef ITEM
#define ITEM

#include "ResourceHandler.h"
#include <string>

class Item
{
public:
	Item(ResourceHandler &handler, sf::Vector2f &position, sf::FloatRect &rectangle, std::string id);
	~Item();
 
	//Toggle functions for flags
	void toggleActive();
	void toggleLookable();
	void toggleInteractable();
	void togglePickupable();

	std::string getId();

	int getIndex();
	void setIndex(int value);

	//Draw
	void draw(sf::RenderWindow &window);
	
	//Get functions to check flags
	bool getActive();
	bool getLookable();
	bool getInteractable();
	bool getPickupable();

	//Get Name
	std::string getName();

	//Get bounding boxes
	sf::FloatRect getRectangle();

	//Get position of item
	sf::Vector2f getPosition();

private:
	bool mIsActive;
	bool mIsLookable;
	bool mIsInteractable;
	bool mIsPickupable;

	int mIndex;

	std::string mId;
	std::string mName;

	sf::FloatRect mRectangle;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
};

#endif