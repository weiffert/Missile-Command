#include "stdafx.h"
#include "Property.h"

#include <vector>
#include <string>

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "Entity.h"


Property::Property()
{
	typeId = "type";
	id = "Property";
}


Property::Property(std::string type)
{
	typeId = type;
	id = "Property";
}


//Default destructor
Property::~Property()
{
	for (int i = 0; i < dataInt.size(); i++)
	{
		dataInt.erase(dataInt.begin() + i);
	}
	for (int i = 0; i < dataDouble.size(); i++)
	{
		dataDouble.erase(dataDouble.begin() + i);
	}
	for (int i = 0; i < dataFloat.size(); i++)
	{
		dataFloat.erase(dataFloat.begin() + i);
	}
	for (int i = 0; i < dataChar.size(); i++)
	{
		dataChar.erase(dataChar.begin() + i);
	}
	for (int i = 0; i < dataBool.size(); i++)
	{
		dataBool.erase(dataBool.begin() + i);
	}
	for (int i = 0; i < dataString.size(); i++)
	{
		dataString.erase(dataString.begin() + i);
	}
	for (int i = 0; i < dataSprite.size(); i++)
	{
		delete dataSprite.at(i);
		dataSprite.erase(dataSprite.begin() + i);
	}
	for (int i = 0; i < dataImage.size(); i++)
	{
		dataImage.erase(dataImage.begin() + i);
	}
	for (int i = 0; i < dataTexture.size(); i++)
	{
		delete dataTexture.at(i);
		dataTexture.erase(dataTexture.begin() + i);
	}
	for (int i = 0; i < dataSound.size(); i++)
	{
		dataSound.erase(dataSound.begin() + i);
	}
	for (int i = 0; i < dataText.size(); i++)
	{
		delete dataText.at(i);
		dataText.erase(dataText.begin() + i);
	}
	for (int i = 0; i < dataCircleShape.size(); i++)
	{
		delete dataCircleShape.at(i);
		dataCircleShape.erase(dataCircleShape.begin() + i);
	}
	for (int i = 0; i < dataConvexShape.size(); i++)
	{
		delete dataConvexShape.at(i);
		dataConvexShape.erase(dataConvexShape.begin() + i);
	}
	for (int i = 0; i < dataRectangleShape.size(); i++)
	{
		delete dataRectangleShape.at(i);
		dataRectangleShape.erase(dataRectangleShape.begin() + i);
	}
	for (int i = 0; i < dataEntity.size(); i++)
	{
		dataEntity.erase(dataEntity.begin() + i);
	}
}

//Returns id
std::string Property::getId()
{
	return id;
}


//Sets id
//Takes in a string.
void Property::setId(std::string a)
{
	id = a;
}


std::string Property::getType()
{
	return typeId;
}


//Sets id
//Takes in a string.
void Property::setType(std::string a)
{
	typeId = a;
}


/*
//Returns the data held in the vector.
template <typename T>
std::vector<T> Property::getData()
{
	if(typeId == "int")
		return dataInt;
	if (typeId == "double")
		return dataDouble;
	if (typeId == "float")
		return dataFloat;
	if (typeId == "char")
		return dataChar;
	if (typeId == "bool")
		return dataBool;
	if (typeId == "string")
		return dataString;
	if (typeId == "Sprite")
		return dataSprite;
	if (typeId == "Image")
		return dataImage;
	if (typeId == "Texture")
		return dataTexture;
	if (typeId == "Sound")
		return dataSound;
	if (typeId == "Text")
		return dataText;
	if (typeId == "CircleShape")
		return dataCircleShape;
	if (typeId == "ConvexShape")
		return dataConvexShape;
	if (typeId == "RectangleShape")
		return dataRectangleShape;
	if (typeId == "Entity")
		return dataEntity;
}
*/


std::vector<int> Property::getDataInt()
{
	if (typeId == "int")
		return dataInt;
}


std::vector<double> Property::getDataDouble()
{
	if (typeId == "double")
		return dataDouble;
}


std::vector<float> Property::getDataFloat()
{
	if (typeId == "float")
		return dataFloat;
}


std::vector<char> Property::getDataChar()
{
	if (typeId == "char")
		return dataChar;
}


std::vector<bool> Property::getDataBool()
{
	if (typeId == "bool")
		return dataBool;
}


std::vector<std::string> Property::getDataString()
{
	if (typeId == "string")
		return dataString;
}


std::vector<sf::Image *> Property::getDataImage()
{
	if (typeId == "Image")
		return dataImage;
}


std::vector<sf::Texture *> Property::getDataTexture()
{
	if (typeId == "Texture")
		return dataTexture;
}


std::vector<sf::Sprite *> Property::getDataSprite()
{
	if (typeId == "Sprite")
		return dataSprite;
}


std::vector<sf::CircleShape *> Property::getDataCircleShape()
{
	if (typeId == "CircleShape")
		return dataCircleShape;
}


std::vector<sf::ConvexShape *> Property::getDataConvexShape()
{
	if (typeId == "ConvexShape")
		return dataConvexShape;
}


std::vector<sf::RectangleShape *> Property::getDataRectangleShape()
{
	if (typeId == "RectangleShape")
		return dataRectangleShape;
}


std::vector<sf::Text *> Property::getDataText()
{
	if (typeId == "Text")
		return dataText;
}


std::vector<Entity *> Property::getDataEntity()
{
	if (typeId == "Entity")
		return dataEntity;
}


std::vector<sf::Sound *> Property::getDataSound()
{
	if (typeId == "Sound")
		return dataSound;
}

std::vector<sf::SoundBuffer *> Property::getDataSoundBuffer()
{
	if (typeId == "SoundBuffer")
		return dataSoundBuffer;
}


template <>
void Property::addData<int>(int *value)
{
	if (typeId == "int")
		dataInt.push_back(*value);
	if (typeId == "double")
		dataDouble.push_back(*value);
	if (typeId == "float")
		dataFloat.push_back(*value);
}


template <>
void Property::addData<double>(double *value)
{
	if (typeId == "double")
		dataDouble.push_back(*value);
	if (typeId == "float")
		dataFloat.push_back(*value);
}


template <>
void Property::addData<float>(float *value)
{
	if (typeId == "double")
		dataDouble.push_back(*value);
	if (typeId == "float")
		dataFloat.push_back(*value);
}


template <>
void Property::addData<char>(char *value)
{
	dataChar.push_back(*value);
}


template <>
void Property::addData<bool>(bool *value)
{
	dataBool.push_back(*value);
}


template <>
void Property::addData<std::string>(std::string *value)
{
	dataString.push_back(*value);
}


template <>
void Property::addData<sf::Image>(sf::Image *value)
{
	dataImage.push_back(value);
}


template <>
void Property::addData<sf::Texture>(sf::Texture *value)
{
	dataTexture.push_back(value);
}


template <>
void Property::addData<sf::Sound>(sf::Sound *value)
{
	dataSound.push_back(value);
}


template <>
void Property::addData<sf::SoundBuffer>(sf::SoundBuffer *value)
{
	dataSoundBuffer.push_back(value);
}


template <>
void Property::addData<sf::Sprite>(sf::Sprite *value)
{
	dataSprite.push_back(value);
}


template <>
void Property::addData<sf::CircleShape>(sf::CircleShape *value)
{
	dataCircleShape.push_back(value);
}


template <>
void Property::addData<sf::ConvexShape>(sf::ConvexShape *value)
{
	dataConvexShape.push_back(value);
}


template <>
void Property::addData<sf::RectangleShape>(sf::RectangleShape *value)
{
	dataRectangleShape.push_back(value);
}


template <>
void Property::addData<sf::Text>(sf::Text *value)
{
	dataText.push_back(value);
}


template <>
void Property::addData<Entity>(Entity *value)
{
	dataEntity.push_back(value);
}


template <>
void Property::addData<int>(int value)
{
	if (typeId == "int")
		dataInt.push_back(value);
	if (typeId == "double")
		dataDouble.push_back(value);
	if (typeId == "float")
		dataFloat.push_back(value);
}


template <>
void Property::addData<double>(double value)
{
	if (typeId == "double")
		dataDouble.push_back(value);
	if (typeId == "float")
		dataFloat.push_back(value);
}


template <>
void Property::addData<float>(float value)
{
	if (typeId == "double")
		dataDouble.push_back(value);
	if (typeId == "float")
		dataFloat.push_back(value);
}


template <>
void Property::addData<char>(char value)
{
	dataChar.push_back(value);
}


template <>
void Property::addData<bool>(bool value)
{
	dataBool.push_back(value);
}


template <>
void Property::addData<std::string>(std::string value)
{
	dataString.push_back(value);
}



//Subtracts value from existing data.
//Takes in the data to be deleted.
void Property::deleteData()
{
	if (typeId == "int")
	{
		for (int i = 0; i < dataInt.size(); i++)
		{
			dataInt.erase(dataInt.begin() + i);
		}
	}
	if (typeId == "double")
	{
		for (int i = 0; i < dataDouble.size(); i++)
		{
			dataDouble.erase(dataDouble.begin() + i);
		}
	}
	if (typeId == "float")
	{
		for (int i = 0; i < dataFloat.size(); i++)
		{
			dataFloat.erase(dataFloat.begin() + i);
		}
	}
	if (typeId == "char")
	{
		for (int i = 0; i < dataChar.size(); i++)
		{
			dataChar.erase(dataChar.begin() + i);
		}
	}
	if (typeId == "bool")
	{
		for (int i = 0; i < dataBool.size(); i++)
		{
			dataBool.erase(dataBool.begin() + i);
		}
	}
	if (typeId == "string")
	{
		for (int i = 0; i < dataString.size(); i++)
		{
			dataString.erase(dataString.begin() + i);
		}
	}
	if (typeId == "Sprite")
	{
		for (int i = 0; i < dataSprite.size(); i++)
		{
			delete dataSprite.at(i);
			dataSprite.erase(dataSprite.begin() + i);
		}
	}
	if (typeId == "Image")
	{
		for (int i = 0; i < dataImage.size(); i++)
		{
			dataImage.erase(dataImage.begin() + i);
		}
	}
	if (typeId == "Texture")
	{
		for (int i = 0; i < dataTexture.size(); i++)
		{
			delete dataTexture.at(i);
			dataTexture.erase(dataTexture.begin() + i);
		}
	}
	if (typeId == "Sound")
	{
		for (int i = 0; i < dataSound.size(); i++)
		{
			dataSound.erase(dataSound.begin() + i);
		}
	}
	if (typeId == "SoundBuffer")
	{
		for (int i = 0; i < dataSoundBuffer.size(); i++)
		{
			dataSoundBuffer.erase(dataSoundBuffer.begin() + i);
		}
	}
	if (typeId == "Text")
	{
		for (int i = 0; i < dataText.size(); i++)
		{
			delete dataText.at(i);
			dataText.erase(dataText.begin() + i);
		}
	}
	if (typeId == "CircleShape")
	{
		for (int i = 0; i < dataCircleShape.size(); i++)
		{
			delete dataCircleShape.at(i);
			dataCircleShape.erase(dataCircleShape.begin() + i);
		}
	}
	if (typeId == "ConvexShape")
	{
		for (int i = 0; i < dataConvexShape.size(); i++)
		{
			delete dataConvexShape.at(i);
			dataConvexShape.erase(dataConvexShape.begin() + i);
		}
	}
	if (typeId == "RectangleShape")
	{
		for (int i = 0; i < dataRectangleShape.size(); i++)
		{
			delete dataRectangleShape.at(i);
			dataRectangleShape.erase(dataRectangleShape.begin() + i);
		}
	}
	if (typeId == "Entity")
	{
		for (int i = 0; i < dataEntity.size(); i++)
		{
			dataEntity.erase(dataEntity.begin() + i);
		}
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
//template <typename T>
//void Property::deleteData(T value)
//{


template <>
void Property::deleteData<int>(int *value)
{
	for (int i = 0; i < dataInt.size(); i++)
	{
		if (dataInt.at(i) == *value)
		{
			dataInt.erase(dataInt.begin() + i);
		}
	}
}


template <>
void Property::deleteData<double>(double *value)
{
	for (int i = 0; i < dataDouble.size(); i++)
	{
		if (dataDouble.at(i) == *value)
		{
			dataDouble.erase(dataDouble.begin() + i);
		}
	}
}


template <>
void Property::deleteData<float>(float *value)
	{
		for (int i = 0; i < dataFloat.size(); i++)
		{
			if (dataFloat.at(i) == *value)
			{
				dataFloat.erase(dataFloat.begin() + i);
			}
		}
}


template <>
void Property::deleteData<char>(char *value)
	{
		for (int i = 0; i < dataChar.size(); i++)
		{
			if (dataChar.at(i) == *value)
			{
				dataChar.erase(dataChar.begin() + i);
			}
		}
}


template <>
void Property::deleteData<bool>(bool *value)
	{
		for (int i = 0; i < dataBool.size(); i++)
		{
			if (dataBool.at(i) == *value)
			{
				dataBool.erase(dataBool.begin() + i);
			}
		}
}


template <>
void Property::deleteData<std::string>(std::string *value)
	{
		for (int i = 0; i < dataString.size(); i++)
		{
			if (dataString.at(i) == *value)
			{
				dataString.erase(dataString.begin() + i);
			}
		}
}


template <>
void Property::deleteData<sf::Sprite>(sf::Sprite *value)
	{
		for (int i = 0; i < dataSprite.size(); i++)
		{
			if (dataSprite.at(i) == value)
			{
				dataSprite.erase(dataSprite.begin() + i);
			}
		}
}


template <>
void Property::deleteData<sf::Image>(sf::Image *value)
	{
		for (int i = 0; i < dataImage.size(); i++)
		{
			if (dataImage.at(i) == value)
			{
				dataImage.erase(dataImage.begin() + i);
			}
		}
}


template <>
void Property::deleteData<sf::Texture>(sf::Texture *value)
	{ 
		for (int i = 0; i < dataTexture.size(); i++)
		{
			if (dataTexture.at(i) == value)
			{
				dataTexture.erase(dataTexture.begin() + i);
			}
		}
}


template <>
void Property::deleteData<sf::Sound>(sf::Sound *value)
	{
		for (int i = 0; i < dataSound.size(); i++)
		{
			if (dataSound.at(i) == value)
			{
				dataSound.erase(dataSound.begin() + i);
			}
		}
}


template <>
void Property::deleteData<sf::SoundBuffer>(sf::SoundBuffer *value)
{
	for (int i = 0; i < dataSoundBuffer.size(); i++)
	{
		if (dataSoundBuffer.at(i) == value)
		{
			dataSoundBuffer.erase(dataSoundBuffer.begin() + i);
		}
	}
}


template <>
void Property::deleteData<sf::Text>(sf::Text *value)
{
	for (int i = 0; i < dataText.size(); i++)
	{
		if (dataText.at(i) == value)
		{
			dataText.erase(dataText.begin() + i);
		}
	}
}


template <>
void Property::deleteData<sf::CircleShape>(sf::CircleShape *value)
{
	for (int i = 0; i < dataCircleShape.size(); i++)
	{
		if (dataCircleShape.at(i) == value)
		{
			dataCircleShape.erase(dataCircleShape.begin() + i);
		}
	}
}


template <>
void Property::deleteData<sf::ConvexShape>(sf::ConvexShape *value)
{
	for (int i = 0; i < dataConvexShape.size(); i++)
	{
		if (dataConvexShape.at(i) == value)
		{
			dataConvexShape.erase(dataConvexShape.begin() + i);
		}
	}
}


template <>
void Property::deleteData<sf::RectangleShape >(sf::RectangleShape *value)
{
	for (int i = 0; i < dataRectangleShape.size(); i++)
	{
		if (dataRectangleShape.at(i) == value)
		{
			dataRectangleShape.erase(dataRectangleShape.begin() + i);
		}
	}
}


template <>
void Property::deleteData<Entity>(Entity *value)
{
	for (int i = 0; i < dataEntity.size(); i++)
	{
		if (dataEntity.at(i)->getId() == value->getId())
		{
			dataEntity.erase(dataEntity.begin() + i);
		}
	}
}


//Subtracts value from existing data with the position.
//Takes in the position with data to be deleted.
void Property::deleteDataPosition(int position)
{
	if (typeId == "int")
	{
		if (position < dataInt.size())
		{
			dataInt.erase(dataInt.begin() + position);
		}
	}
	if (typeId == "double")
	{
		if (position < dataDouble.size())
		{
			dataDouble.erase(dataDouble.begin() + position);
		}
	}
	if (typeId == "float")
	{
		if (position < dataFloat.size())
		{
			dataFloat.erase(dataFloat.begin() + position);
		}
	}
	if (typeId == "char")
	{
		if (position < dataChar.size())
		{
			dataChar.erase(dataChar.begin() + position);
		}
	}
	if (typeId == "bool")
	{
		if (position < dataBool.size())
		{
			dataBool.erase(dataBool.begin() + position);
		}
	}
	if (typeId == "string")
	{
		if (position < dataString.size())
		{
			dataString.erase(dataString.begin() + position);
		}
	}
	if (typeId == "Sprite")
	{
		if (position < dataSprite.size())
		{
			dataSprite.erase(dataSprite.begin() + position);
		}
	}
	if (typeId == "Image")
	{
		if (position < dataImage.size())
		{
			dataImage.erase(dataImage.begin() + position);
		}
	}
	if (typeId == "Texture")
	{
		if (position < dataTexture.size())
		{
			dataTexture.erase(dataTexture.begin() + position);
		}
	}
	if (typeId == "Sound")
	{
		if (position < dataSound.size())
		{
			dataSound.erase(dataSound.begin() + position);
		}
	}
	if (typeId == "SoundBuffer")
	{
		if (position < dataSoundBuffer.size())
		{
			dataSoundBuffer.erase(dataSoundBuffer.begin() + position);
		}
	}
	if (typeId == "Text")
	{
		if (position < dataText.size())
		{
			dataText.erase(dataText.begin() + position);
		}
	}
	if (typeId == "CircleShape")
	{
		if (position < dataCircleShape.size())
		{
			dataCircleShape.erase(dataCircleShape.begin() + position);
		}
	}
	if (typeId == "ConvexShape")
	{
		if (position < dataConvexShape.size())
		{
			dataConvexShape.erase(dataConvexShape.begin() + position);
		}
	}
	if (typeId == "RectangleShape")
	{
		if (position < dataRectangleShape.size())
		{
			dataRectangleShape.erase(dataRectangleShape.begin() + position);
		}
	}
	if (typeId == "Entity")
	{
		if (position < dataEntity.size())
		{
			dataEntity.erase(dataEntity.begin() + position);
		}
	}
}


//Value changes the data at position.
//Takes in a value to change to and the position to change it at.
//template <typename T>
//void Property::changeData(T value, int position)
//{


template <>
void Property::changeData<int>(int *value, int position)
{
	if (position < dataInt.size())
		dataInt.at(position) = *value;
	else
		addData(value);
}


template <>
void Property::changeData<double>(double *value, int position)
{
	if (position < dataDouble.size())
		dataDouble.at(position) = *value;
	else
		addData(value);
}


template <>
void Property::changeData<float>(float *value, int position)
{
	if (position < dataFloat.size())
		dataFloat.at(position) = *value;
	else
		addData(value);
}


template <>
void Property::changeData<char>(char *value, int position)
{
	if (position < dataChar.size())
		dataChar.at(position) = *value;
	else
		addData(value);
}


template <>
void Property::changeData<bool>(bool *value, int position)
{
	if (position < dataBool.size())
		dataBool.at(position) = *value;
	else
		addData(value);
}


template <>
void Property::changeData<std::string>(std::string *value, int position)
{
	if (position < dataString.size())
		dataString.at(position) = *value;
	else
		addData(value);
}


template <>
void Property::changeData<sf::Sprite>(sf::Sprite *value, int position)
{
	if (position < dataSprite.size())
		dataSprite.at(position) = value;
	else
		addData(value);
}


template <>
void Property::changeData<sf::Image>(sf::Image *value, int position)
{
	if (position < dataImage.size())
		dataImage.at(position) = value;
	else
		addData(value);
}


template <>
void Property::changeData<sf::Texture>(sf::Texture *value, int position)
{
	if (position < dataTexture.size())
		dataTexture.at(position) = value;
	else
		addData(value);
}


template <>
void Property::changeData<sf::Sound>(sf::Sound *value, int position)
{
	if (position < dataSound.size())
		dataSound.at(position) = value;
	else
		addData(value);
}


template <>
void Property::changeData<sf::SoundBuffer>(sf::SoundBuffer *value, int position)
{
	if (position < dataSoundBuffer.size())
		dataSoundBuffer.at(position) = value;
	else
		addData(value);
}


template <>
void Property::changeData<sf::Text>(sf::Text *value, int position)
{
	if (position < dataText.size())
		dataText.at(position) = value;
	else
		addData(value);
}


template <>
void Property::changeData<sf::CircleShape>(sf::CircleShape *value, int position)
{
	if (position < dataCircleShape.size())
		dataCircleShape.at(position) = value;
	else
		addData(value);
}


template <>
void Property::changeData<sf::ConvexShape>(sf::ConvexShape *value, int position)
{
	if (position < dataConvexShape.size())
		dataConvexShape.at(position) = value;
	else
		addData(value);
}


template <>
void Property::changeData<sf::RectangleShape>(sf::RectangleShape *value, int position)
{
	if (position < dataRectangleShape.size())
		dataRectangleShape.at(position) = value;
	else
		addData(value);
}


template <>
void Property::changeData<Entity>(Entity *value, int position)
{
	if (position < dataEntity.size())
		dataEntity.at(position) = value;
	else
		addData(value);
}