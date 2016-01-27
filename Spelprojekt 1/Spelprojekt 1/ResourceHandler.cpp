#include "ResourceHandler.h"

using namespace std;

ResourceHandler::ResourceHandler():
mTextures(),
mTextureNames(),
mSounds(),
mSoundNames(),
mMusic(),
mMusicNames(),
textureCounter(0),
soundCounter(0),
musicCounter(0)
{
	//Add resources in constructor
	addTexture("test_1.jpg");
	addTexture("test_2.png");
	addTexture("Test3.png");

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

	//Delete string vectors
	while (!mTextureNames.empty())
	{
		mTextureNames.pop_back();
	}

	while (!mSoundNames.empty())
	{
		mSoundNames.pop_back();
	}

	while (!mMusicNames.empty())
	{
		mMusicNames.pop_back();
	}
}

//Adds a texture to the texture vector
void ResourceHandler::addTexture(string fileName)
{
	mTextures.push_back(new sf::Texture());
	mTextureNames.push_back(fileName);
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
	mSoundNames.push_back(fileName);
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
	mMusicNames.push_back(fileName);
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

//Get texture via name
sf::Texture* ResourceHandler::getTexture(string name)
{
	for (StringVector::size_type i = 0; i < mTextureNames.size(); i++)
	{
		if (name == mTextureNames[i])
		{
			return mTextures[i];
			break;
		}
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

//Get sound via name
sf::SoundBuffer* ResourceHandler::getSound(string name)
{
	for (StringVector::size_type i = 0; i < mSoundNames.size(); i++)
	{
		if (name == mSoundNames[i])
		{
			return mSounds[i];
			break;
		}
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

//Get music via name
sf::Music* ResourceHandler::getMusic(string name)
{
	for (StringVector::size_type i = 0; i < mMusicNames.size(); i++)
	{
		if (name == mMusicNames[i])
		{
			return mMusic[i];
			break;
		}
	}
	return NULL;
}