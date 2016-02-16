#ifndef INCLUDED_MENU
#define INCLUDED_MENU

#include "Button.h"

class Menu
{
public:
	Menu();
	~Menu();

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);

	enum State
	{
		Main,
		InGame,
		Paused
	};
	State mState;

	State getState();
	void ChangeState(State state);

private:
	typedef std::vector<Button*> ButtonVector;
	ButtonVector mMainButtons;
	ButtonVector mPauseButtons;
};

#endif