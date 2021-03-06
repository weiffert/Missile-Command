#include "stdafx.h"

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include <stdlib.h>
#include <Windows.h>
#include <fstream>

#include "StateStatic.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Property.h"
#include "Entity.h"


StateStatic::StateStatic()
{
	//Sets defaults.
	id = "Static";
	number = 1;
	systemManager = nullptr;
	assetManager = nullptr;
}


StateStatic::StateStatic(SystemManager *s, AssetManager *a)
{
	//Sets defaults.
	id = "Static";
	number = 1;
	systemManager = s;
	assetManager = a;
}


StateStatic::~StateStatic()
{
}


//Runs until a certain amount of time has elapsed.
//Takes in a double which contains the amount of time elapsed. Takes in the window for consistency.
std::string StateStatic::update(double totalTime, sf::RenderWindow *window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
				window->close();
			else
			{
				if (id.find("GameOver") == std::string::npos)
					return "next";
				else
					window->close();
			}
		}
	}
	if (id.find("GameOver") != std::string::npos)
	{
		if (systemManager->getMaterial("GameOver")->getComponent("LevelStart")->getDataBool().at(0))
		{
			Property *t = systemManager->getMaterial("GameOver")->getComponent("Text");
			sf::Text *text = new sf::Text;
			text->setString(std::to_string(systemManager->getMaterial("Player")->getComponent("Points")->getDataInt().at(0)) + " Points");
			text->setPosition(0, 50);
			text->setCharacterSize(30);
			sf::Color c(255, 255, 255);
			text->setFillColor(c);
			text->setFont(*t->getDataText().at(0)->getFont());
			t->addData(text);

			//Play sound
			systemManager->getMaterial("GameOver")->getComponent("LevelStart")->deleteData();
			systemManager->getMaterial("GameOver")->getComponent("LevelStart")->addData(false);
			sf::Sound * sound = new sf::Sound;
			sound->setBuffer(*systemManager->getComponent("SoundGameOver")->getDataSoundBuffer().at(0));
			sound->play();
			assetManager->add(sound);
		}
	}
	
	return "constant";
}
