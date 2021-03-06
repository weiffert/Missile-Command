#include "stdafx.h"

#include <string>
#include <vector>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "BaseState.h"
#include "Entity.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Render.h"

#include <fstream>


BaseState::BaseState()
{
	id = "BaseState";
	number = -1;
	systemManager = nullptr;
	assetManager = nullptr;
}


BaseState::~BaseState()
{

}


//Returns the id number.
int BaseState::getNumber()
{
	return number;
}


//Returns the id string.
std::string BaseState::getId()
{
	return id;
}


//Sets the id.
//Takes in a string.
void BaseState::setId(std::string a)
{
	id = a;
}


//Set the id number.
//Takes in an int.
void BaseState::setNumber(int a)
{
	number = a;
}


//Sets the materials in the state.
//Takes in a vector of predefined entity pointers.
void BaseState::setMaterial(std::vector<Entity*> a)
{
	material = a;
}


//Render the state onto the window.
//Takes in the amount of time lag and the window.
void BaseState::render(double lag, sf::RenderWindow *window)
{
	window->clear();

	Render controller;
	///Pass through all of the materials.
	for (int i = 0; i < material.size(); i++)
	{
		//Render the current entity.
		controller.control(lag, window, material.at(i), assetManager);
	}

	window->display();
}

//Convert a string to an int.
int BaseState::conversionInt(std::string s)
{
	int temp = 0;
	bool negative = false;

	//Repeat until the number has been extracted.
	for (int i = 0; i < s.length(); i++)
	{
		if (s.at(i) == '-')
			negative = true;
		//Conversion from string to base 10.
		temp *= 10;
		temp += static_cast<int>(s.at(i) - 48);
	}

	if (negative)
		temp *= -1;
	return temp;
}


//Convert a string to a float.
float BaseState::conversionFloat(std::string s)
{
	float temp = 0;
	int place = 0;
	bool negative = false;

	bool decimal = false;
	//Repeat until the number has been extracted.
	for (int i = 0; i < s.length(); i++)
	{
		if (s.at(i) == '-')
			negative = true;
		//Conversion from string to base 10.
		if (s.at(i) == '.')
		{
			decimal = true;
		}

		if (!decimal)
		{
			temp *= 10;
			temp += static_cast<int>(s.at(i) - 48);
		}
		else
		{
			place += 10;
			int small = static_cast<int>(s.at(i) - 48);
			small /= place;
			temp += small;
		}
	}

	if (negative)
		temp *= -1;

	return temp;
}


//Convert a string to a double.
double BaseState::conversionDouble(std::string s)
{
	double temp = 0;
	int place = 0;
	bool negative = false;

	bool decimal = false;
	//Repeat until the number has been extracted.
	for (int i = 0; i < s.length(); i++)
	{
		if (s.at(i) == '-')
			negative = true;
		//Conversion from string to base 10.
		if (s.at(i) == '.')
		{
			decimal = true;
		}

		if (!decimal)
		{
			temp *= 10;
			temp += static_cast<int>(s.at(i) - 48);
		}
		else
		{
			place += 10;
			int small = static_cast<int>(s.at(i) - 48);
			small /= place;
			temp += small;
		}
	}

	if (negative)
		temp *= -1;

	return temp;
}