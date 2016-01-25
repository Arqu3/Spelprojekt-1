#ifndef INCLUDED_RH
#define INCLUDED_RH

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include <vector>
#include <cassert>
#include <iostream>
#include <string>

class ResourceHandler
{
public:
	ResourceHandler();
	~ResourceHandler();

	sf::Texture* getTexture(int index);
	sf::SoundBuffer* getSound(int index);
	sf::Music* getMusic(int index);

private:
	void addTexture(std::string fileName);
	int textureCounter;

	void addSound(std::string fileName);
	int soundCounter;

	void addMusic(std::string fileName);
	int musicCounter;

	typedef std::vector<sf::Texture*> TextureVector;
    TextureVector mTextures;

	typedef std::vector<sf::SoundBuffer*> SoundVector;
	SoundVector mSounds;

	typedef std::vector<sf::Music*> MusicVector;
	MusicVector mMusic;
};

#endif