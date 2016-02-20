#include "stdafx.h"
#include "StateMenu.h"
#include "SystemManager.h"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

StateMenu::StateMenu(SystemManager *s, AssetManager *a)
{
	id = "Menu";
	number = 2;
	systemManager = s;
	assetManager = a;
}


StateMenu::~StateMenu()
{
}


void StateMenu::update(double totalTime, sf::RenderWindow window)
{
	//Check for arrow key and space bar events
	sf::Event event;
	while (window.pollEvent(event))
	{
		bool moveUp = false, moveDown = false, moveRight = false, moveLeft = false, spaceBarReleased = false;

		//Checks if up arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
		{
			moveUp = true;
		}
		//Checks if down arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
		{
			moveDown = true;
		}
		//Checks if right arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
		{
			moveRight = true;
		}
		//Checks if left arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
		{
			moveLeft = true;
		}
		//Checks if space bar released
		if ((event.type = sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space))
		{
			spaceBarReleased = true;
		}
		//Checks if escape key pressed
		if ((event.type = sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape))
		{
			BaseState::changeState(this, "Pause");
		}
		//Run through the game controllers.
		//Example: Checking for collisions
		systemManager->getController("PlayerInput")->control(moveUp, moveDown, moveRight, moveLeft, spaceBarReleased, &material);
	}
}


void StateMenu::render(double lag, sf::RenderWindow window)
{
	window.clear;
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->hasController("draw"))
		{
			BaseController *controller = material.at(i)->getController("draw");
			controller->control(material.at(i));
		}
	}
	window.display();
}
