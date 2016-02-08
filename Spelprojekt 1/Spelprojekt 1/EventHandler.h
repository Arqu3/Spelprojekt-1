#ifndef EVENTHANDLER
#define EVENTHANDLER

#include "LevelHandler.h"
#include "DialogueSystem.h"
#include "Inventory.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"


class EventHandler
{
public:
	EventHandler(LevelHandler &lHandler);
	~EventHandler();

	//Listen for mouse clicks
	void eventListen(sf::RenderWindow &window);

	void update(sf::RenderWindow &window);

private:
	//Check collision between a single rectangle and a point
	int checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point);

	//Check collision between a single rectangle and a point
	int checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point);

	//Check collision between a vector of rectangles and a point
	int checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point);

	void mouseClick(sf::Event &event);
	void mouseClickLevel1(sf::Event &event);

	//Member variables
	LevelHandler *mLHandler;
	DialogueSystem *mDialogueSystem;
	Inventory *mInventory;
	sf::Vector2f mWorldPos;
	sf::Vector2i mPixelPos;
	sf::Vector2f mViewMoveTo;
	Item* mTargetItem;
	bool mItemInteraction;
	//Scene change
	sf::FloatRect mSceneChangeRect;
	sf::Vector2f mSceneChangePlayerPos;
	int mNewScene;
	bool mPlayerToggle;
	bool mInventoryMode;

	//Sound/music
	sf::SoundBuffer mBuffer;
	sf::Sound mPickupItemSound;
};

#endif