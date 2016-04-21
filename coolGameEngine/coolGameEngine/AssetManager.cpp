#include "stdafx.h"
#include <string>
#include <vector>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "AssetManager.h"


AssetManager::AssetManager()
{

}


AssetManager::~AssetManager()
{
	while (!image.empty())
	{
		delete image.at(image.size() - 1);
		image.pop_back();
	}
	while (!sound.empty())
	{
		delete sound.at(sound.size() - 1);
		sound.pop_back();
	}
	while (!soundBuffer.empty())
	{
		delete soundBuffer.at(soundBuffer.size() - 1);
		soundBuffer.pop_back();
	}
	while (!texture.empty())
	{
		delete texture.at(texture.size() - 1);
		texture.pop_back();
	}
	while (!font.empty())
	{
		delete font.at(font.size() - 1);
		font.pop_back();
	}
}


//Takes in the location in the vector.
//Returns an image for a property.
sf::Image* AssetManager::getImage(int location)
{
	if (location < image.size() && location >= 0)
	{
		return image.at(location);
	}

	return nullptr;
}


//Takes in the filename.
//Returns an image for a property.
sf::Image* AssetManager::getImage(std::string filename)
{
	for (int i = 0; i < imageNames.size(); i++)
		if (imageNames.at(i) == filename)
		{
			if (i < image.size())
				return image.at(i);
		}

	return nullptr;
}


//Takes in the location in the vector.
//Returns a sound for a property.
sf::Sound* AssetManager::getSound(int location)
{
	if (location < sound.size() && location >= 0)
	{
		return sound.at(location);
	}

	return nullptr;
}

sf::SoundBuffer* AssetManager::getSoundBuffer(int location)
{
	if (location < soundBuffer.size() && location >= 0)
	{
		return soundBuffer.at(location);
	}

	return nullptr;
}


//Takes in the filename.
//Returns an sound buffer for a property.
sf::SoundBuffer* AssetManager::getSoundBuffer(std::string filename)
{
	for (int i = 0; i < soundBufferNames.size(); i++)
		if (soundBufferNames.at(i) == filename)
		{
			if (i < soundBuffer.size())
				return soundBuffer.at(i);
		}

	return nullptr;
}


//Takes in the location in the vector.
//Returns a texture for a property.
sf::Texture* AssetManager::getTexture(int location)
{
	if (location < texture.size() && location >= 0)
	{
		return texture.at(location);
	}

	return nullptr;
}


//Takes in the filename.
//Returns an image for a property.
sf::Texture* AssetManager::getTexture(std::string filename)
{
	for (int i = 0; i < textureNames.size(); i++)
		if (textureNames.at(i) == filename)
		{
			if (i < texture.size())
				return texture.at(i);
		}

	return nullptr;
}


sf::Font* AssetManager::getFont(int location)
{
	if (location < font.size() && location >= 0)
	{
		return font.at(location);
	}

	return nullptr;
}


sf::Font* AssetManager::getFont(std::string filename)
{
	for (int i = 0; i < fontNames.size(); i++)
		if (fontNames.at(i) == filename)
		{
			if (i < font.size())
				return font.at(i);
		}

	return nullptr;
}


//Adds an image to the vector for the state.
//Takes in a image.
void AssetManager::add(sf::Image* a)
{
	image.push_back(a);
}


//Adds a sound to the vector for the state.
//Takes in a sound.
void AssetManager::add(sf::Sound* a)
{
	sound.push_back(a);
}

void AssetManager::add(sf::SoundBuffer* a)
{
	soundBuffer.push_back(a);
}


//Adds an image to the vector for the state.
//Takes in a texture.
void AssetManager::add(sf::Texture* a)
{
	texture.push_back(a);
}


void AssetManager::add(sf::Font* a)
{
	font.push_back(a);
}


//Adds a name to be linked with the image.
//Takes in a string.
void AssetManager::addImageString(std::string a)
{
	imageNames.push_back(a);
}


//Adds a name to be linked with the sound.
//Takes in a string.
void AssetManager::addSoundString(std::string a)
{
	soundNames.push_back(a);
}

void AssetManager::addBufferString(std::string a)
{
	soundBufferNames.push_back(a);
}


//Adds a name to be linked with the texture.
//Takes in a string.
void AssetManager::addTextureString(std::string a)
{
	textureNames.push_back(a);
}


void AssetManager::addFontString(std::string a)
{
	fontNames.push_back(a);
}


void AssetManager::clearSounds()
{
	while (!sound.empty())
	{
		delete sound.at(sound.size() - 1);
		sound.pop_back();
	}
}