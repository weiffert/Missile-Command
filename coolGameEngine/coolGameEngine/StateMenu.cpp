#include "stdafx.h"

#include <fstream>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "StateMenu.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Property.h"
#include "Entity.h"
//include controllers.

#include<iostream>

StateMenu::StateMenu()
{
	//Sets defaults.
	id = "Menu";
	number = 2;
	systemManager = nullptr;
	assetManager = nullptr;
	
}

StateMenu::StateMenu(SystemManager *s, AssetManager *a)
{
	//Sets defaults.
	id = "Menu";
	number = 2;
	systemManager = s;
	assetManager = a;
}


StateMenu::~StateMenu()
{
}


//Polls for events and calls the PlayerInput controller accordingly.
//Takes in the total time elapsed and the window.
std::string StateMenu::update(double totalTime, sf::RenderWindow *window)
{
	//Check for arrow key and space bar events
	sf::Event event;
	while (window->pollEvent(event))
	{
		centerCoordinates.x = (window->getSize().x) / 2;
		centerCoordinates.y = (window->getSize().y) / 2;
		sf::Mouse::setPosition(centerCoordinates, *window);
		bool moveUp = false, moveDown = false, moveRight = false, moveLeft = false, spaceBarReleased = false;

		//Checks if trackball moved up
		if (sf::Mouse::getPosition(*window).y > centerCoordinates.y)
			moveUp = true;
		//Checks if trackball moved down
		if (sf::Mouse::getPosition(*window).y < centerCoordinates.y)
			moveDown = true;
		//Checks if trackball moved right
		if (sf::Mouse::getPosition(*window).x > centerCoordinates.x)
			moveRight = true;
		//Checks if trackball moved left
		if (sf::Mouse::getPosition(*window).x < centerCoordinates.x)
			moveLeft = true;
		//Checks if space bar released
		if ((event.type = sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space))
		{
			spaceBarReleased = true;
		}
		//Checks if escape key pressed, if so pauses until escape key is pressed again
		if ((event.type = sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape))
		{

		}

		if (event.type == sf::Event::Closed)
			window->close();
		//Run through the game controllers.
		//Example: Checking for collisions
		//systemManager->getController("PlayerInput")->control(moveUp, moveDown, moveRight, moveLeft, spaceBarReleased, &material);
	}
	return "constant";
}

void StateMenu::paused(sf::RenderWindow* window)
{
	//Set mouse to visible
	window->setMouseCursorVisible(true);

	
	//Clear window
	window->clear(sf::Color::Black);
	
	//Draw pause message
	sf::Text pauseMessage;
	sf::Font font;
	
	//Set up font for message
	if (!font.loadFromFile("square.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
		system("pause");
		window->close();
		return;
	}

	pauseMessage.setFont(font);
	pauseMessage.setString("\n\n\n\n\n\n\n\n\n\n\nPaused\nPress escape to continue");
	window->draw(pauseMessage);

	sf::Text score;
	score.setFont(font);
	score.setString((char)systemManager->getMaterial("Player")->getComponent("Points")->getDataInt().at(0));
	window->draw(score);

	window->display();

	//Stay paused until escape is pressed to unpause
	sf::Event newEvent;
	bool paused = true;
	do
	{
		window->pollEvent(newEvent);
		if ((newEvent.type == sf::Event::KeyPressed) && (newEvent.key.code == sf::Keyboard::Escape))
			paused = false;

		else if (newEvent.type == sf::Event::Closed)
		{
			window->close();
			return;
		}

	} while (paused);

	//Set mouse back to invisible
	window->setMouseCursorVisible(false);

	return;
}