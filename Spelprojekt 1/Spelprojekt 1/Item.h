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

	//Get functions to check flags
	bool getActive();
	bool getLookable();
	bool getInteractable();
	bool getPickupable();

	//Function that is called through the EventHandler, to put an item in the inventory
	void addToInventory(std::string &id);

	//Get Name
	std::string getName();

	//Get bounding boxes
	sf::FloatRect getRectangle();

private:
	bool mIsActive;
	bool mIsLookable;
	bool mIsInteractable;
	bool mIsPickupable;

	std::string mId;
	std::string mName;

	sf::FloatRect mRectangle;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
};

#endif