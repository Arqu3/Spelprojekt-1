#include "Menu.h"

using namespace std;

Menu::Menu(ResourceHandler &handler):
mMainButtons(),
mPauseButtons(),
mState(Main)
{
	mBackground.setSize(sf::Vector2f(1024, 576));
	mBackground.setTexture(handler.getTexture("MainMenuBackground.png"));

	//Adds main menu buttons
	mMainButtons.push_back(new Button(200, 100, sf::Color::Red));
	mMainButtons.push_back(new Button(200, 100, sf::Color::Blue));
	mMainButtons.push_back(new Button(200, 100, sf::Color::Green));

	for (ButtonVector::size_type i = 0; i < mMainButtons.size(); i++)
	{
		mMainButtons[i]->setPosition(512.0f - mMainButtons[0]->getRect().width / 2, 100.0f + (160.0f * i));
	}

	//Adds pause menu buttons
	mPauseButtons.push_back(new Button(100, 100, sf::Color::Red));
	mPauseButtons.push_back(new Button(100, 100, sf::Color::Black));
	mPauseButtons.push_back(new Button(100, 100, sf::Color::Cyan));

	for (ButtonVector::size_type i = 0; i < mPauseButtons.size(); i++)
	{
		mPauseButtons[i]->setPosition(500.0f, 120.0f * i);
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

void Menu::eventListen(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			switch (mState)
			{
			case Menu::Main:
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
			break;

		case sf::Event::MouseButtonPressed:
			switch (mState)
			{
			case Menu::Main:
				if (mMainButtons[0]->isPressed(window))
				{
					setState(InGame);
				}

				if (mMainButtons[2]->isPressed(window))
				{
					window.close();
				}
				break;
			}
			break;
		}
	}
}

void Menu::draw(sf::RenderWindow &window)
{
	switch (mState)
	{
	case Menu::Main:
		window.draw(mBackground);
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

void Menu::setState(Menu::State state)
{
	mState = state;
}