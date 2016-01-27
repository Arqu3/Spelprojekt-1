#ifndef ITEM
#define ITEM

#include "ResourceHandler.h"
#include <string>

class Item
{
public:
	Item(ResourceHandler &handler, sf::Vector2f &posision, std::string id);
	~Item();

	void toggleActive();
	void toggleLookable();
	void toggleInteractable();
	void togglePickupable();

	bool getActive();
	bool getLookable();
	bool getInteractable();
	bool getPickupable();

	std::string getName();

private:
	bool mIsActive;
	bool mIsLookable;
	bool mIsInteractable;
	bool mIsPickupable;

	std::string mName;

	sf::Vector2f mPosition;
	sf::Sprite mSprite;
};

#endif