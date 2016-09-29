#include "stdafx.h"

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "StateReInit.h"
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "StateLoading.h"
#include "Entity.h"
#include "Property.h"



//SFML includes
StateReInit::StateReInit()
{
	//Sets defaults.
	id = "End";
	number = 4;
	systemManager = nullptr;
	assetManager = nullptr;

	
}


StateReInit::StateReInit(SystemManager *s, AssetManager *a)
{
	//Sets defaults.
	id = "End";
	number = 4;
	systemManager = s;
	assetManager = a;
}


StateReInit::~StateReInit()
{
	std::ofstream files;
	StateReInit *ptr = this;
	files.open("object log.txt", std::ios::app);
	files << "Deleting StateReInit object " << ptr << std::endl;
	files.close();
}


std::string StateReInit::update(double totalTime, sf::RenderWindow* window)
{
	sf::Event event;

	if (systemManager != nullptr)
	{
		delete systemManager;
	}
	if (assetManager != nullptr)
	{
		delete assetManager;
	}

	StateLoading reload(systemManager, assetManager);

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		reload.update(totalTime, window);
	}

	//the process is done.
	return "Welcome1";
}