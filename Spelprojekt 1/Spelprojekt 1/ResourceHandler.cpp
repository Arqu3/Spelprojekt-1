#include "ResourceHandler.h"

using namespace std;

ResourceHandler::ResourceHandler():
mTextures(),
mTextureNames(),
mSounds(),
mSoundNames(),
mMusicNames(),
textureCounter(0),
soundCounter(0),
musicCounter(0)
{
	//Add resources in constructor
	// Textures
	//Thomas
	addTexture("Thomas.png");
	//Thomas rum items
	addTexture("thomasstar.png");
	addTexture("thomasblock.png");
	addTexture("thomasstring.png");
	addTexture("thomasmagnet.png");
	addTexture("thomasastronaut.png");
	addTexture("thomasbowl.png");
	addTexture("thomascube.png");
	//Thomas rum bakgrund
	addTexture("thomasbg.png");
	addTexture("thomaspg.png");
	addTexture("thomasfg.png");
	//Thomas zoom bakgrund
	addTexture("thomaszoombg.png");
	addTexture("thomaszoompg.png");
	addTexture("thomaszoomfg.png");

	//Music
	addMusic("Level1Music.ogg");

	cout << "Number of textures loaded: " << mTextures.size() << endl;
	cout << "Number of sounds loaded: " << mSounds.size() << endl;
	cout << "Number of music files loaded: " << mMusicNames.size() << endl;
}

ResourceHandler::~ResourceHandler()
{
	internalClear();
}

void ResourceHandler::internalClear()
{
	mTextures.clear();
	mTextureNames.clear();

	mSounds.clear();
	mSoundNames.clear();

	mMusicNames.clear();
}

//Adds a texture to the texture vector
void ResourceHandler::addTexture(string fileName)
{
	mTextures.push_back(new sf::Texture());
	mTextureNames.push_back(fileName);
	textureCounter++;

	if (!mTextures[textureCounter - 1]->loadFromFile("Resources/Textures/" + fileName))
	{
		cout << "Could not load texture at index: " << textureCounter - 1 << endl;
	}
}

//Adds sound to the sound vector
void ResourceHandler::addSound(string fileName)
{
	mSounds.push_back(new sf::SoundBuffer());
	mSoundNames.push_back(fileName);
	soundCounter++;

	if (!mSounds[soundCounter - 1]->loadFromFile("Resources/Sounds/" + fileName))
	{
		cout << "Could not load sound at index: " << soundCounter - 1 << endl;
	}
}

//Adds music name to the name vector
void ResourceHandler::addMusic(string fileName)
{
	mMusicNames.push_back(fileName);
}

//Get texture at specific index
sf::Texture* ResourceHandler::getTexture(int index)
{
	assert(index >= 0);
	assert((unsigned int)index <= mTextures.size() - 1);

	return mTextures[index];
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

	return mSounds[index];
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
string ResourceHandler::getMusic(int index)
{
	assert(index >= 0);
	assert((unsigned int)index <= mMusicNames.size() - 1);

	return mMusicNames[index];
}

//Get music via name
string ResourceHandler::getMusic(string name)
{
	for (StringVector::size_type i = 0; i < mMusicNames.size(); i++)
	{
		if (name == mMusicNames[i])
		{
			return mMusicNames[i];
			break;
		}
	}
	return NULL;
}