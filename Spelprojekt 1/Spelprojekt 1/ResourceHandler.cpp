#include "ResourceHandler.h"

using namespace std;

ResourceHandler::ResourceHandler():
mTextures(),
mSounds(),
mMusic(),
textureCounter(0),
soundCounter(0),
musicCounter(0)
{
	//Add resources in constructor
	addTexture("test_1.jpg");
	addTexture("test_2.png");

	cout << "Number of textures loaded: " << mTextures.size() << endl;
}

ResourceHandler::~ResourceHandler()
{
	//Delete textures
	while (!mTextures.empty())
	{
		delete mTextures.back();
		mTextures.pop_back();
	}

	//Delete sounds
	while (!mSounds.empty())
	{
		delete mSounds.back();
		mSounds.pop_back();
	}

	//Delete music
	while (!mMusic.empty())
	{
		delete mMusic.back();
		mMusic.pop_back();
	}
}

//Adds a texture to the texture vector
void ResourceHandler::addTexture(string fileName)
{
	mTextures.push_back(new sf::Texture());
	textureCounter++;
	for (TextureVector::size_type i = 0; i < mTextures.size(); i++)
	{
		if (!mTextures[textureCounter - 1]->loadFromFile("Resources/Textures/" + fileName))
		{
			cout << "Could not load texture at index: " << i << endl;
		}
	}
}

//Adds sound to the sound vector
void ResourceHandler::addSound(string fileName)
{
	mSounds.push_back(new sf::SoundBuffer());
	soundCounter++;
	for (SoundVector::size_type i = 0; i < mSounds.size(); i++)
	{
		if (!mSounds[soundCounter - 1]->loadFromFile("Resources/Sounds/" + fileName))
		{
			cout << "Could not load sound at index: " << i << endl;
		}
	}
}

//Adds music to the musicvector
void ResourceHandler::addMusic(string fileName)
{
	mMusic.push_back(new sf::Music());
	musicCounter++;
	for (MusicVector::size_type i = 0; i < mMusic.size(); i++)
	{
		if (!mMusic[musicCounter - 1]->openFromFile("Resources/Music/" + fileName))
		{
			cout << "Could not open music at index: " << i << endl;
		}
	}
}

//Get texture at specific index
sf::Texture* ResourceHandler::getTexture(int index)
{
	assert(index >= 0);
	assert((unsigned int)index <= mTextures.size() - 1);

	for (TextureVector::size_type i = 0; i < mTextures.size(); i++)
	{
		return mTextures[index];
	}
	return NULL;
}

//Get sound at specific index
sf::SoundBuffer* ResourceHandler::getSound(int index)
{
	assert(index >= 0);
	assert((unsigned int)index <= mSounds.size() - 1);

	for (SoundVector::size_type i = 0; i < mSounds.size(); i++)
	{
		return mSounds[index];
	}
	return NULL;
}

//Get music at specific index
sf::Music* ResourceHandler::getMusic(int index)
{
	assert(index >= 0);
	assert((unsigned int)index <= mMusic.size() - 1);

	for (MusicVector::size_type i = 0; i < mMusic.size(); i++)
	{
		return mMusic[index];
	}
	return NULL;
}