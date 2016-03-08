#include "stdafx.h"
#include "Property.h"

#include <vector>
#include <string>

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "Entity.h"


Property::Property(std::string type)
{
	typeId = type;
	id = "Property";
}


//Default destructor
Property::~Property();
{

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



//Returns the data held in the vector.
template <class T>
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
	if (typeId == "Shape")
		return dataShape;
	if (typeId == "Entity")
		return dataEntity;
}


//Returns the data at the location.
template <class T>
T Property::getData(int location)
{
	if (typeId == "int")
	{
		if (location < dataInt.size())
			return dataInt.at(location);
	}
	if (typeId == "double")
	{
		if (location < dataDouble.size())
			return dataDouble.at(location);
	}
	if (typeId == "float")
	{
		if (location < dataFloat.size())
			return dataFloat.at(location);
	}
	if (typeId == "char")
	{
		if (location < dataChar.size())
			return dataChar.at(location);
	}
	if (typeId == "bool")
	{
		if (location < dataBool.size())
			return dataBool.at(location);
	}
	if (typeId == "string")
	{
		if (location < dataString.size())
			return dataString.at(location);
	}
	if (typeId == "Sprite")
	{
		if (location < dataSprite.size())
			return dataSprite.at(location);
	}
	if (typeId == "Image")
	{
		if (location < dataImage.size())
			return dataImage.at(location);
	}
	if (typeId == "Texture")
	{
		if (location < dataTexture.size())
			return dataTexture.at(location);
	}
	if (typeId == "Sound")
	{
		if (location < dataSound.size())
			return dataSound.at(location);
	}
	if (typeId == "Text")
	{
		if (location < dataText.size())
			return dataText.at(location);
	}
	if (typeId == "Shape")
	{
		if (location < dataShape.size())
			return dataShape.at(location);
	}
	if (typeId == "Entity")
	{
		if (location < dataEntity.size())
			return dataEntity.at(location);
	}
}


//Adds value to existing data
//Takes in data.
template <class T>
void Property::addData(T value)
{
	if (typeId == "int")
		dataInt.push_back(value);
	if (typeId == "double")
		dataDouble.push_back(value);
	if (typeId == "float")
		dataFloat.push_back(value);
	if (typeId == "char")
		dataChar.push_back(value);
	if (typeId == "bool")
		dataBool.push_back(value);
	if (typeId == "string")
		dataString.push_back(value);
	if (typeId == "Sprite")
		dataSprite.push_back(value);
	if (typeId == "Image")
		dataImage.push_back(value);
	if (typeId == "Texture")
		dataTexture.push_back(value);
	if (typeId == "Sound")
		dataSound.push_back(value);
	if (typeId == "Text")
		dataText.push_back(value);
	if (typeId == "Shape")
		dataShape.push_back(value);
	if (typeId == "Entity")
		dataEntity.push_back(value);
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
template <class T>
void Property::deleteData()
{
	if (typeId == "int")
	{
		for (int i = 0; i < dataInt.size(); i++)
		{
			dataInt.erase(i);
		}
	}
	if (typeId == "double")
	{
		for (int i = 0; i < dataDouble.size(); i++)
		{
			dataDouble.erase(i);
		}
	}
	if (typeId == "float")
	{
		for (int i = 0; i < dataFloat.size(); i++)
		{
			dataFloat.erase(i);
		}
	}
	if (typeId == "char")
	{
		for (int i = 0; i < dataChar.size(); i++)
		{
			dataChar.erase(i);
		}
	}
	if (typeId == "bool")
	{
		for (int i = 0; i < dataBool.size(); i++)
		{
			dataBool.erase(i);
		}
	}
	if (typeId == "string")
	{
		for (int i = 0; i < dataString.size(); i++)
		{
			dataString.erase(i);
		}
	}
	if (typeId == "Sprite")
	{
		for (int i = 0; i < dataSprite.size(); i++)
		{
			dataSprite.erase(i);
		}
	}
	if (typeId == "Image")
	{
		for (int i = 0; i < dataImage.size(); i++)
		{
			dataImage.erase(i);
		}
	}
	if (typeId == "Texture")
	{
		for (int i = 0; i < dataTexture.size(); i++)
		{
			dataTexture.erase(i);
		}
	}
	if (typeId == "Sound")
	{
		for (int i = 0; i < dataSound.size(); i++)
		{
			dataSound.erase(i);
		}
	}
	if (typeId == "Text")
	{
		for (int i = 0; i < dataText.size(); i++)
		{
			dataText.erase(i);
		}
	}
	if (typeId == "Shape")
	{
		for (int i = 0; i < dataShape.size(); i++)
		{
			dataShape.erase(i);
		}
	}
	if (typeId == "Entity")
	{
		for (int i = 0; i < dataEntity.size(); i++)
		{
			dataEntity.erase(i);
		}
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
template <class T>
void Property::deleteData(T value)
{
	if (typeId == "int")
	{
		for (int i = 0; i < dataInt.size(); i++)
		{
			if (dataInt.at(i) == value)
			{
				dataInt.erase(dataInt.begin() + i);
			}
		}
	}
	if (typeId == "double")
	{
		for (int i = 0; i < dataDouble.size(); i++)
		{
			if (dataDouble.at(i) == value)
			{
				dataDouble.erase(dataDouble.begin() + i);
			}
		}
	}
	if (typeId == "float")
	{
		for (int i = 0; i < dataFloat.size(); i++)
		{
			if (dataFloat.at(i) == value)
			{
				dataFloat.erase(dataFloat.begin() + i);
			}
		}
	}
	if (typeId == "char")
	{
		for (int i = 0; i < dataChar.size(); i++)
		{
			if (dataChar.at(i) == value)
			{
				dataChar.erase(dataChar.begin() + i);
			}
		}
	}
	if (typeId == "bool")
	{
		for (int i = 0; i < dataBool.size(); i++)
		{
			if (dataBool.at(i) == value)
			{
				dataBool.erase(dataBool.begin() + i);
			}
		}
	}
	if (typeId == "string")
	{
		for (int i = 0; i < dataString.size(); i++)
		{
			if (dataString.at(i) == value)
			{
				dataString.erase(dataString.begin() + i);
			}
		}
	}
	if (typeId == "Sprite")
	{
		for (int i = 0; i < dataSprite.size(); i++)
		{
			if (dataSprite.at(i) == value)
			{
				dataSprite.erase(dataSprite.begin() + i);
			}
		}
	}
	if (typeId == "Image")
	{
		for (int i = 0; i < dataImage.size(); i++)
		{
			if (dataImage.at(i) == value)
			{
				dataImage.erase(dataImage.begin() + i);
			}
		}
	}
	if (typeId == "Texture")
	{ 
		for (int i = 0; i < dataTexture.size(); i++)
		{
			if (dataTexture.at(i) == value)
			{
				dataTexture.erase(dataTexture.begin() + i);
			}
		}
	}
	if (typeId == "Sound")
	{
		for (int i = 0; i < dataSound.size(); i++)
		{
			if (dataSound.at(i) == value)
			{
				dataSound.erase(dataSound.begin() + i);
			}
		}
	}
	if (typeId == "Text")
	{
		for (int i = 0; i < dataText.size(); i++)
		{
			if (dataText.at(i) == value)
			{
				dataText.erase(dataText.begin() + i);
			}
		}
	}
	if (typeId == "Shape")
	{
		for (int i = 0; i < dataShape.size(); i++)
		{
			if (dataShape.at(i) == value)
			{
				dataShape.erase(dataShape.begin() + i);
			}
		}
	}
	if (typeId == "Entity")
	{
		for (int i = 0; i < dataEntity.size(); i++)
		{
			if (dataEntity.at(i) == value)
			{
				dataEntity.erase(dataEntity.begin() + i);
			}
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
	if (typeId == "Text")
	{
		if (position < dataText.size())
		{
			dataText.erase(dataText.begin() + position);
		}
	}
	if (typeId == "Shape")
	{
		if (position < dataShape.size())
		{
			dataShape.erase(dataShape.begin() + position);
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
template <class T>
void Property::changeData(T value, int position)
{
	if (typeId == "int")
	{
		if (position < dataInt.size())
			dataInt.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "double")
	{
		if (position < dataDouble.size())
			dataDouble.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "float")
	{
		if (position < dataFloat.size())
			dataFloat.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "char")
	{ 
		if (position < dataChar.size())
			dataChar.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "bool")
	{
		if (position < dataBool.size())
			dataBool.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "string")
	{
		if (position < dataString.size())
			dataString.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "Sprite")
	{
		if (position < dataSprite.size())
			dataSprite.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "Image")
	{
		if (position < dataImage.size())
			dataImage.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "Texture")
	{
		if (position < dataTexture.size())
			dataTexture.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "Sound")
	{ 
		if (position < dataSound.size())
			dataSound.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "Text")
	{
		if (position < dataText.size())
			dataText.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "Shape")
	{
		if (position < dataShape.size())
			dataShape.at(position) = value;
		else
			addData(value);
	}
	if (typeId == "Entity")
	{
		if (position < dataEntity.size())
			dataEntity.at(position) = value;
		else
			addData(value);
	}
}