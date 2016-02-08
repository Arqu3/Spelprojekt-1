#ifndef ITEM
#define ITEM

#include "ResourceHandler.h"
#include <string>

class Item
{
public:
	Item(ResourceHandler &handler, sf::Vector2f &position, std::string id);
	~Item();
 
	//Toggle functions for flags
	void toggleActive();
	void toggleLookable();
	void toggleInteractable();
	void togglePickupable();
	void toggleIsLookedAt();
	void toggleInteracted();

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
	bool isLookedAt();
	bool isInteracted();

	//Get Name
	std::string getName();

	//Get Description
	std::string getDescription();

	//Get bounding boxes
	sf::FloatRect getRectangle();

	//Get position of item
	sf::Vector2f getPosition();

	//Set position of item
	void setPosition(float x, float y);

	//Set scale of item
	void setScale(float x, float y);

	sf::Sprite getSprite();

private:
	bool mIsActive;
	bool mIsLookable;
	bool mIsInteractable;
	bool mIsPickupable;
	bool mIsLookedAt;
	bool mInteracted;

	int mIndex;

	std::string mId;
	std::string mName;
	std::string mDescription;

	sf::Vector2f mPosition;
	sf::Sprite mSprite;
};

#endif