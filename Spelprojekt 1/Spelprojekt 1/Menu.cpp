#include "Menu.h"

using namespace std;

Menu::Menu():
mMainButtons(),
mPauseButtons(),
mState(Main)
{
	//Adds main menu buttons
	mMainButtons.push_back(new Button(100, 100, sf::Color::Red));
	mMainButtons.push_back(new Button(100, 100, sf::Color::Blue));
	mMainButtons.push_back(new Button(100, 100, sf::Color::Green));

	for (ButtonVector::size_type i = 0; i < mMainButtons.size(); i++)
	{
		mMainButtons[i]->setPosition(100, 100 * i);
	}

	//Adds pause menu buttons
	mPauseButtons.push_back(new Button(100, 100, sf::Color::Red));
	mPauseButtons.push_back(new Button(100, 100, sf::Color::Black));
	mPauseButtons.push_back(new Button(100, 100, sf::Color::Cyan));

	for (ButtonVector::size_type i = 0; i < mPauseButtons.size(); i++)
	{
		mPauseButtons[i]->setPosition(100, 100 * i);
	}
}

Menu::~Menu()
{
	mMainButtons.clear();
	mPauseButtons.clear();
}

void Menu::update(float deltaTime)
{
	switch (mState)
	{
	case Menu::Main:
		for (ButtonVector::size_type i = 0; i < mMainButtons.size(); i++)
		{
			mMainButtons[i]->update(deltaTime);
		}
		break;

	case Menu::Paused:
		for (ButtonVector::size_type i = 0; i < mPauseButtons.size(); i++)
		{
			mPauseButtons[i]->update(deltaTime);
		}
		break;

	default:
		break;
	}
}

void Menu::draw(sf::RenderWindow &window)
{
	switch (mState)
	{
	case Menu::Main:
		for (ButtonVector::size_type i = 0; i < mMainButtons.size(); i++)
		{
			mMainButtons[i]->draw(window);
		}
		break;

	case Menu::Paused:
		for (ButtonVector::size_type i = 0; i < mPauseButtons.size(); i++)
		{
			mPauseButtons[i]->draw(window);
		}
		break;

	default:
		break;
	}
}

Menu::State Menu::getState()
{
	return mState;
}

void Menu::ChangeState(Menu::State state)
{
	mState = state;
}