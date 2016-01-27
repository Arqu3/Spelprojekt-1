#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL

class Level
{
public:
	typedef std::vector<sf::FloatRect> rectVector;
	virtual void playBackgroundMusic() = 0;
	virtual void playAmbience() = 0;
	virtual void drawBackground(sf::RenderWindow &window) = 0;
	virtual rectVector getRects() = 0;
	virtual void addRect(sf::FloatRect) = 0;
	virtual void removeRect(int index) = 0;
private:
	rectVector mRects;
	sf::RectangleShape background;
	sf::Music backgroundMusic;
	sf::Sound ambientSound;
};

#endif