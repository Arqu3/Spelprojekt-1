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
	addTexture("loadscreen.jpg");
	addTexture("MainMenuBackground.png");
	addTexture("Test1.png");

	loadScreen.setTexture(*getTexture("loadscreen.jpg"));

	mFont.loadFromFile("Resources/Fonts/ShadowsIntoLight.ttf");
	mLoadMessage.setFont(mFont);
	mLoadMessage.setCharacterSize(18);
	mLoadMessage.setStyle(sf::Text::Bold);
	mLoadMessage.setColor(sf::Color::Black);
	mLoadMessage.setPosition(420, 420);
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

void ResourceHandler::loadLevel1(sf::RenderWindow &window)
{
	//internalClear();

	drawLoadScreen(window, "Teklar Karaktärer");
	//Thomas
	addTexture("ThomasWalk.png");
	//Hilma
	addTexture("HilmaWalk.png");
	addTexture("HilmaPush.png");
	addTexture("HilmaFishing.png");

	drawLoadScreen(window, "Davidar UI");
	//In-game UI
	addTexture("haticon.png");
	addTexture("menuicon.png");
	addTexture("hatmenu.png");
	addTexture("menu.png");
	addTexture("inventory.png");
	addTexture("ClueBackground1.png");

	drawLoadScreen(window, "Davidar Inventoryikoner");
	//Inventory icons
	addTexture("AstronautINV.png");
	addTexture("FishingRodINV.png");
	addTexture("MagnetINV.png");
	addTexture("ScrewDeviceINV.png");

	drawLoadScreen(window, "Davidar Muspekare");
	//Cursors
	addTexture("mousecursor.png");
	addTexture("openhand.png");
	addTexture("closedhand.png");
	addTexture("speechbubble.png");
	addTexture("eyecursor.png");
	addTexture("scenechangecursor.png");

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

	drawLoadScreen(window, "Davidar Pratbubblor");
	//Textbubble
	addTexture("textbubble.png");
	addTexture("textbox.png");

	drawLoadScreen(window, "Lailar Ansiktsuttryck");
	//Character Expressions
	addTexture("expressionHilmaAbject.png");
	addTexture("expressionHilmaAngry.png");
	addTexture("expressionHilmaConfident.png");
	addTexture("expressionHilmaDetermined.png");
	addTexture("expressionHilmaGrumpy.png");
	addTexture("expressionHilmaHappy.png");
	addTexture("expressionHilmaNervous.png");
	addTexture("expressionHilmaNeutral.png");
	addTexture("expressionHilmaSad.png");
	addTexture("expressionHilmaSigh.png");
	addTexture("expressionHilmaSurprised.png");
	addTexture("expressionThomasAngry.png");
	addTexture("expressionThomasBlush.png");
	addTexture("expressionThomasCry.png");
	addTexture("expressionThomasDetermined.png");
	addTexture("expressionThomasHappy.png");
	addTexture("expressionThomasNeutral.png");
	addTexture("expressionThomasSad.png");
	addTexture("expressionThomasSceptic.png");
	addTexture("expressionThomasSigh.png");
	addTexture("expressionThomasSmile.png");
	addTexture("expressionThomasSurprised.png");
	addTexture("expressionThomasThoughtful.png");
	addTexture("expressionThomasWorried.png");

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
	addSound("Regular_Item_Pickup.ogg");
	addSound("Crafting.ogg");
	addSound("Menu_Hat.ogg");
	addSound("Menu_Inventory.ogg");
	addSound("Menu_MainUI.ogg");
	addSound("Critical_Item.ogg");
	addSound("Inventory_Move.ogg");
}


void ResourceHandler::loadLevel3(sf::RenderWindow &window)
{
	drawLoadScreen(window, "Gör Saker Med Blommor");
	//Level 3
	addTexture("Garden.png");
	addTexture("GardenForeground.png");

	//Karaktärer
	addTexture("ThomasWalk.png");
	addTexture("HilmaWalk.png");
	addTexture("HilmaPush.png");
	addTexture("HilmaFishing.png");
	addTexture("DogRunning.png");
	addTexture("GardenLady.png");


	//In-game UI
	addTexture("haticon.png");
	addTexture("menuicon.png");
	addTexture("hatmenu.png");
	addTexture("menu.png");
	addTexture("inventory.png");

	//Cursors
	addTexture("mousecursor.png");
	addTexture("openhand.png");
	addTexture("closedhand.png");
	addTexture("speechbubble.png");
	addTexture("eyecursor.png");
	addTexture("scenechangecursor.png");

	//Props
	addTexture("thomasbowl.png");
	addTexture("Saturnus.png");
	addTexture("Venus.png");
	addTexture("Pluto.png");
	addTexture("Fisk1.png");
	addTexture("LastLevel_ItemTest1.png");
	addTexture("LastLevel_ItemTest2.png");
	addTexture("transparent.png");
	addTexture("Stick.png");
	addTexture("StickIcon.png");
	addTexture("Trimmer.png");
	addTexture("TrimmerIcon.png");

	//Sound
	addSound("Footsteps_Thomas.ogg");
	addSound("Level1_Ambience.ogg");
	addSound("Aquarium.ogg");
	addSound("Magnet_Catch.ogg");
	addSound("Magnet_Drop.ogg");
	addSound("Pushing_Object.ogg");
	addSound("Radio_Noise.ogg");
	addSound("Regular_Item_Pickup.ogg");
	addSound("Crafting.ogg");
	addSound("Menu_Hat.ogg");
	addSound("Menu_Inventory.ogg");
	addSound("Menu_MainUI.ogg");
	addSound("Critical_Item.ogg");
	addSound("Inventory_Move.ogg");
	


}


void ResourceHandler::loadLastLevel(sf::RenderWindow &window)
{
	//internalClear();

	drawLoadScreen(window, "Laddar Karaktärer");
	
	drawLoadScreen(window, "Laddar UI");
	//In-game UI
	addTexture("haticon.png");
	addTexture("menuicon.png");
	addTexture("hatmenu.png");
	addTexture("menu.png");
	addTexture("inventory.png");

	drawLoadScreen(window, "Laddar Inventoryikoner");
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

	drawLoadScreen(window, "Laddar Muspekare");
	//Cursors
	addTexture("mousecursor.png");
	addTexture("openhand.png");
	addTexture("closedhand.png");
	addTexture("speechbubble.png");
	addTexture("eyecursor.png");
	addTexture("scenechangecursor.png");

	drawLoadScreen(window, "Laddar Ljud");
	//Sound
	addSound("Footsteps_Thomas.ogg");
	addSound("Level1_Ambience.ogg");
	addSound("Aquarium.ogg");
	addSound("Magnet_Catch.ogg");
	addSound("Magnet_Drop.ogg");
	addSound("Pushing_Object.ogg");
	addSound("Radio_Noise.ogg");
	addSound("Regular_Item_Pickup.ogg");
	addSound("Crafting.ogg");
	addSound("Menu_Hat.ogg");
	addSound("Menu_Inventory.ogg");
	addSound("Menu_MainUI.ogg");
	addSound("Critical_Item.ogg");
	addSound("Inventory_Move.ogg");

    //LastLevel
	drawLoadScreen(window, "Laddar Sista Bananen");
	addTexture("ARBETSRUMbakgrund.png");
	addTexture("ARBETSRUMmellangrund.png");
	addTexture("ARBETSRUMförgrund.png");

	addTexture("VARDAGSRUMbakgrund.png");
	addTexture("VARDAGSRUMmellangrund.png");
	addTexture("VARDAGSRUMförgrund.png");
	addTexture("Fisk2.png");
	addTexture("Jordglob.png");

	addTexture("KÖKbakgrund.png");
	addTexture("KÖKmellangrund.png");
	addTexture("KÖKförgrund.png");
	addTexture("Apelsin.png");
	addTexture("Tavlan.png");

	addTexture("transparent.png");
	addTexture("LastLevel_ItemTest1.png");
	addTexture("LastLevel_ItemTest2.png");

    	//Karaktärer
	addTexture("ThomasWalk.png");
	addTexture("HilmaWalk.png");
	addTexture("HilmaPush.png");
	addTexture("HilmaFishing.png");
	addTexture("Katten.png");
	addTexture("Lisa.png");
	addTexture("PutteSad.png");

	//Cursors
	addTexture("mousecursor.png");
	addTexture("openhand.png");
	addTexture("closedhand.png");
	addTexture("speechbubble.png");
	addTexture("eyecursor.png");

	//In-game UI
	addTexture("haticon.png");
	addTexture("menuicon.png");
	addTexture("hatmenu.png");
	addTexture("menu.png");
	addTexture("inventory.png");

	//Props
	addTexture("thomasbowl.png");
	addTexture("Saturnus.png");
	addTexture("Venus.png");
	addTexture("Pluto.png");
	addTexture("Fisk1.png");


        //Sounds
	addSound("FootSteps.ogg");

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