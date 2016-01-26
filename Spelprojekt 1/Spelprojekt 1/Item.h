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
	void setLookable();
	void setInteractable();
	void setPickupable();

	bool getActive();
	bool getLookable();
	bool getInteractable();
	bool getPickupable();
private:
	bool mIsActive;
	std::string mName;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
};

#endif