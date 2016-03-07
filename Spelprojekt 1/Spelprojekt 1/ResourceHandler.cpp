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
	addTexture("loadscreen.png");
	addTexture("MainMenuBackground.png");
	addTexture("Test1.png");

	loadScreen.setSize(sf::Vector2f(1024, 576));
	loadScreen.setTexture(getTexture("loadscreen.png"));

	mFont.loadFromFile("Resources/Fonts/ShadowsIntoLight.ttf");
	mLoadMessage.setFont(mFont);
	mLoadMessage.setCharacterSize(18);
	mLoadMessage.setStyle(sf::Text::Bold);
	mLoadMessage.setColor(sf::Color::White);
	mLoadMessage.setPosition(430, 490);
	mLoadMessage.setString("Laddar...");
}

ResourceHandler::~ResourceHandler()
{
	internalClear();
}

void ResourceHandler::internalClear()
{
	textureCounter = 0;
	soundCounter = 0;
	musicCounter = 0;
	mTextures.clear();
	mTextureNames.clear();

	mSounds.clear();
	mSoundNames.clear();

	mMusicNames.clear();
}

void ResourceHandler::loadGeneral(sf::RenderWindow &window)
{
	drawLoadScreen(window, "Teklar Karaktärer");
	//Thomas
	addTexture("ThomasWalk.png");
	//Hilma
	addTexture("HilmaWalk.png");
	addTexture("HilmaPush.png");
	addTexture("HilmaFishing.png");

	drawLoadScreen(window, "Lailar Ansiktsuttryck");
	//Character Expressions
	addTexture("expressionHilmaAngry.png");
	addTexture("expressionHilmaConfident.png");
	addTexture("expressionHilmaDetermined.png");
	addTexture("expressionHilmaGrumpy.png");
	addTexture("expressionHilmaHappy.png");
	addTexture("expressionHilmaNeutral.png");
	addTexture("expressionHilmaSad.png");
	addTexture("expressionHilmaSigh.png");
	addTexture("expressionHilmaSurprised.png");
	addTexture("expressionThomasBlush.png");
	addTexture("expressionThomasCry.png");
	addTexture("expressionThomasGrumpy.png");
	addTexture("expressionThomasHappy.png");
	addTexture("expressionThomasNeutral.png");
	addTexture("expressionThomasSad.png");
	addTexture("expressionThomasSigh.png");
	addTexture("expressionThomasSmile.png");
	addTexture("expressionThomasSurprised.png");

	drawLoadScreen(window, "Davidar UI");
	//In-game UI
	addTexture("HatIconGlow.png");
	addTexture("MenuIconGlow.png");
	addTexture("InventoryIconGlow.png");
	addTexture("ClueIconGlow.png");
	addTexture("hatmenu.png");
	addTexture("menu.png");
	addTexture("inventory.png");
	addTexture("ClueBackground1.png");

	drawLoadScreen(window, "Davidar Muspekare");
	//Cursors
	addTexture("mousecursor.png");
	addTexture("openhand.png");
	addTexture("closedhand.png");
	addTexture("speechbubble.png");
	addTexture("eyecursor.png");
	addTexture("scenechangecursor.png");

	drawLoadScreen(window, "Davidar Pratbubblor");
	//Textbubble
	addTexture("textbubble.png");
	addTexture("textbox.png");

	drawLoadScreen(window, "Matatasar Ljud");
	//Sound
	addSound("Footsteps_Thomas.ogg");
	addSound("Regular_Item_Pickup.ogg");
	addSound("Menu_Hat.ogg");
	addSound("Menu_Inventory.ogg");
	addSound("Menu_MainUI.ogg");
	addSound("Critical_Item.ogg");
	addSound("Inventory_Move.ogg");
	addSound("Crafting.ogg");

	drawLoadScreen(window, "PerHeimerar Musik");
	//Music
	addMusic("VoiceActingTest.ogg");
	addMusic("VoiceActingTest2.ogg");
}

void ResourceHandler::loadLevel1(sf::RenderWindow &window)
{
	//internalClear();

	drawLoadScreen(window, "Davidar Inventoryikoner");
	//Inventory icons
	addTexture("AstronautINV.png");
	addTexture("FishingRodINV.png");
	addTexture("MagnetINV.png");
	addTexture("ScrewDeviceINV.png");

	// Level1
	drawLoadScreen(window, "Maxar Objekt");
	//Thomas rum items
	addTexture("thomasstar.png");
	addTexture("thomasblock.png");
	addTexture("thomasmagnet.png");
	addTexture("thomasastronaut.png");
	addTexture("thomasbowl.png");
	addTexture("thomascube.png");
	addTexture("FishingRod.png");
	addTexture("FishingRodMagnet.png");
	addTexture("thomaswallstar.png");
	addTexture("RogerSwim.png");

	drawLoadScreen(window, "Maxar Bakgrunder");
	//Thomas room background, playground, foreground
	addTexture("thomasbg.png");
	addTexture("thomaspg.png");
	addTexture("thomasfg.png");
	//Thomas zoom background, playground, foreground
	addTexture("thomaszoombg.png");
	addTexture("thomaszoompg.png");
	addTexture("thomaszoomfg.png");

	drawLoadScreen(window, "Laddar Sepia");
	//Sepia
	addTexture("sepia.png");

	drawLoadScreen(window, "PerHeimerar Musik");
	//Music
	addMusic("Level1Music.ogg");

	drawLoadScreen(window, "Matatasar Ljud");
	//Sound
	addSound("Footsteps_Thomas.ogg");
	addSound("Level1_Ambience.ogg");
	addSound("Aquarium.ogg");
	addSound("Magnet_Catch.ogg");
	addSound("Magnet_Drop.ogg");
	addSound("Pushing_Object.ogg");
	addSound("Radio_Noise.ogg");
}

void ResourceHandler::loadLastLevel(sf::RenderWindow &window)
{
	//internalClear();

	drawLoadScreen(window, "Matatasar Ljud");
	//Sound
	addSound("Fish_Hit_Floor.ogg");
	addSound("Cat_Hissing.ogg");
	addSound("Cat.ogg");
	addSound("Planet_Puzzle.ogg");
	addSound("Gramophone.ogg");
	addSound("Running_Water.ogg");
	addSound("Screw_Globe.ogg");
	addSound("Jewelry_Box.ogg");

	drawLoadScreen(window, "Lailar Karaktärer");
	//Static Characters
	addTexture("LisaTotte.png");
	addTexture("PutteSad.png");
	addTexture("PutteLillemor.png");

	drawLoadScreen(window, "Davidar Inventoryikoner");
	//Inventory icons
	addTexture("beigeballINV.png");
	addTexture("needleINV.png");
	addTexture("marsINV.png");
	addTexture("pocketwatchINV.png");
	addTexture("saturnusringINV.png");
	addTexture("earthINV.png");
	addTexture("fishINV.png");
	addTexture("saturnusINV.png");
	addTexture("ScrewDeviceINV.png");
	addTexture("plutoINV.png");
	addTexture("clamINV.png");
	addTexture("MagnetINV.png"); //TODO - Replace with Pump INV Texture

	drawLoadScreen(window, "PerHeimerar Musik");
	//Music
	addMusic("LastLevelMusic.ogg");

	drawLoadScreen(window, "Maxar Bakgrunder");
	//Backgrounds
	addTexture("ARBETSRUMbakgrund.png");
	addTexture("ARBETSRUMmellangrund.png");
	addTexture("ARBETSRUMförgrund.png");
	addTexture("VARDAGSRUMbakgrund.png");
	addTexture("VARDAGSRUMmellangrund.png");
	addTexture("VARDAGSRUMförgrund.png");
	addTexture("KÖKbakgrund.png");
	addTexture("KÖKmellangrund.png");
	addTexture("KÖKförgrund.png");
	addTexture("Tavlan.png");

	drawLoadScreen(window, "Maxar Objekt");
	//Items
	addTexture("Fisk2.png");
	addTexture("Jordglob.png");
	addTexture("Apelsin.png");
	addTexture("thomasbowl.png");
	addTexture("Saturnus.png");
	addTexture("Venus.png");
	addTexture("Pluto.png");
	addTexture("Fisk1.png");
	addTexture("transparent.png");

	drawLoadScreen(window, "Beccar Testsaker");
	//Test Textures
	addTexture("LastLevel_ItemTest1.png");
	addTexture("LastLevel_ItemTest2.png");

	drawLoadScreen(window, "Teklar Katten");
	//Animations
	addTexture("CatWalking.png");
	addTexture("CatEating.png");
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
	mMusicNames.push_back("Resources/Music/" + fileName);
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
		if ("Resources/Music/" + name == mMusicNames[i])
		{
			return mMusicNames[i];
			break;
		}
	}
	return NULL;
}

void ResourceHandler::drawLoadScreen(sf::RenderWindow &window, string loadMessage)
{
	mLoadMessage.setString(loadMessage);
	window.clear(sf::Color::Black);
	window.draw(loadScreen);
	window.draw(mLoadMessage);
	window.display();
}