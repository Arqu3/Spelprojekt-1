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

	//Get resources via index
	sf::Texture* getTexture(int index);
	sf::SoundBuffer* getSound(int index);
	sf::Music* getMusic(int index);

	//Get resources via name
	sf::Texture* getTexture(std::string name);
	sf::SoundBuffer* getSound(std::string name);
	sf::Music* getMusic(std::string name);

private:
	//Add texture
	void addTexture(std::string fileName);
	int textureCounter;

	//Add sound
	void addSound(std::string fileName);
	int soundCounter;

	//Add music
	void addMusic(std::string fileName);
	int musicCounter;

	typedef std::vector<std::string> StringVector;

	//Texture variables
	typedef std::vector<sf::Texture*> TextureVector;
    TextureVector mTextures;
	StringVector mTextureNames;

	//Sound variables
	typedef std::vector<sf::SoundBuffer*> SoundVector;
	SoundVector mSounds;
	StringVector mSoundNames;

	//Music variables
	typedef std::vector<sf::Music*> MusicVector;
	MusicVector mMusic;
	StringVector mMusicNames;
};

#endif