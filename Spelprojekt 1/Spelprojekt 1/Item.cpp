#include "Item.h"

Item::Item(ResourceHandler &handler, sf::Vector2f &posision, std::string id) :
mIsActive(false)
{
	if (id == "")
	{
		mName = "";
		mSprite.setTexture(*handler.getTexture(0));
		mPosition.x = 0;
		mPosition.y = 0;
	}
}

Item::~Item()
{

}