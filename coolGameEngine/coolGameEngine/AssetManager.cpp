#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "AssetManager.h"


AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
	for (int i = 0; i < image.size(); i++)
	{
		if (image.at(i) != nullptr)
		{
			delete image.at(i);
			image.at(i) = nullptr;
		}
	}
	for (int i = 0; i < sound.size(); i++)
	{
		if (sound.at(i) != nullptr)
		{
			delete sound.at(i);
			sound.at(i) = nullptr;
		}
	}
	for (int i = 0; i < soundBuffer.size(); i++)
	{
		if (soundBuffer.at(i) != nullptr)
		{
			delete soundBuffer.at(i);
			soundBuffer.at(i) = nullptr;
		}
	}
	for (int i = 0; i < texture.size(); i++)
	{
		if (texture.at(i) != nullptr)
		{
			delete texture.at(i);
			texture.at(i) = nullptr;
		}
	}
	for (int i = 0; i < font.size(); i++)
	{
		if (font.at(i) != nullptr)
		{
			delete font.at(i);
			font.at(i) = nullptr;
		}
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

	std::cout << "Image error" << std::endl;

	throw std::bad_typeid("getImage error");
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

		std::cout << "Image error" << std::endl;

	throw std::bad_typeid("getImage error");
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

	std::cout << "Sound error" << std::endl;

	throw std::bad_typeid("getSound error");
	return nullptr;
}

sf::SoundBuffer* AssetManager::getSoundBuffer(int location)
{
	if (location < soundBuffer.size() && location >= 0)
	{
		return soundBuffer.at(location);
	}

	std::cout << "SoundBuffer error" << std::endl;

	throw std::bad_typeid("getSoundBuffer error");
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

		std::cout << "soundBuffer error" << std::endl;

	throw std::bad_typeid("getSoundBuffer error");
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

	std::cout << "getTexture error" << std::endl;

	throw std::bad_typeid("getTexture error");
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

		std::cout << "getTexture error" << std::endl;

	throw std::bad_typeid("getTexture error");
	return nullptr;
}


sf::Font* AssetManager::getFont(int location)
{
	if (location < font.size() && location >= 0)
	{
		return font.at(location);
	}

	std::cout << "getFont error" << std::endl;

	throw std::bad_typeid("getFont error");
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
	
		std::cout << "getFont error" << std::endl;

	throw std::bad_typeid("getFont error");
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