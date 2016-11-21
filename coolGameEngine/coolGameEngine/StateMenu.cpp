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
#include"windows.h"
//include controllers.

#include<iostream>
#include<sstream>

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

	//Actual pause message to display
	pauseMessage.setString("\nPaused\nPress escape to continue");
	pauseMessage.setCharacterSize(18);
	window->draw(pauseMessage);

	//Set up score to display in pause menu
	sf::Text score;
	score.setFont(font);
	std::stringstream points;
	points << (systemManager->getMaterial("Player")->getComponent("Points")->getDataInt().at(0));
	score.setString(points.str());
	score.setCharacterSize(18);
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

void StateMenu::endGame(sf::RenderWindow* window)
{
	//Read all the scores from the file
	std::string scoreOne, scoreTwo, scoreThree, scoreFour, scoreFive, playerScore, name;
	std::fstream scores;
	scores.open("scores.txt");
	getline(scores, scoreOne);
	getline(scores, scoreTwo);
	getline(scores, scoreThree);
	getline(scores, scoreFour);
	getline(scores, scoreFive);
	std::stringstream points;
	points << (systemManager->getMaterial("Player")->getComponent("Points")->getDataInt().at(0));
	playerScore=(points.str());
	scores.close();
	playerScore += " - ";

	//Pull the numerical scores out of the strings
	int scoreOneNum, scoreTwoNum, scoreThreeNum, scoreFourNum, scoreFiveNum;
	std::stringstream scoreHolder(scoreOne);
	scoreHolder >> scoreOneNum;
	scoreHolder=std::stringstream (scoreTwo);
	scoreHolder >> scoreTwoNum;
	scoreHolder = std::stringstream(scoreThree);
	scoreHolder >> scoreThreeNum;
	scoreHolder = std::stringstream(scoreFour);
	scoreHolder >> scoreFourNum;
	scoreHolder = std::stringstream(scoreFive);
	scoreHolder >> scoreFiveNum;

	//Only edit the window if it's open
	if (!window->isOpen())
	{
		window = new sf::RenderWindow;
		sf::VideoMode windowResolution;
		windowResolution.width = 480;
		windowResolution.height = 480;
		std::string gameName = "missileCommand";
		window->create(windowResolution, gameName);
		window->setVerticalSyncEnabled(false);
		window->setFramerateLimit(30);
		window->clear(sf::Color::Black);
	}
	
	window->clear(sf::Color::Black);

	//Set up score to display in endgame menu
	sf::Font font;
	if (!font.loadFromFile("square.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
		system("pause");
		window->close();
		return;
	}

	sf::Text score;
	score.setFont(font);
	score.setString(points.str());
	score.setCharacterSize(18);
	window->draw(score);
	sf::Text initials;
	std::string enteredInitials = "\nPlease enter your three intials: ";
	initials.setFont(font);
	initials.setString(enteredInitials);
	initials.setCharacterSize(18);
	window->draw(initials);

	sf::Event event;
	bool entered = false;
	int initialNum = 0;

	//Get player initials
	do
	{
		window->display();

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					enteredInitials+=(static_cast<char>(event.text.unicode));
					initialNum++;
					initials.setString(enteredInitials);
					window->clear(sf::Color::Black);
					window->draw(initials);
					window->draw(score);
					playerScore += static_cast<char>(event.text.unicode);
				}
			}
		}
		if (initialNum == 3)
			entered = true;
	} while (!entered);

	window->display();
	Sleep(1000);
	window->clear(sf::Color::Black);

	//Sort scores
	int scoreSort[6] = { scoreOneNum, scoreTwoNum, scoreThreeNum, scoreFourNum, scoreFiveNum, systemManager->getMaterial("Player")->getComponent("Points")->getDataInt().at(0)};
	std::sort(scoreSort, scoreSort + 6);

	//Write sorted scores and names to the file
	scores.open("scores.txt");
	for (int i = 5; i > 0; i--)
	{
		if (scoreSort[i] == scoreOneNum)
		{
			scores << scoreOne << std::endl;
		}

		else if (scoreSort[i] == scoreTwoNum)
		{
			scores << scoreTwo << std::endl;
		}

		else if (scoreSort[i] == scoreThreeNum)
		{
			scores << scoreThree << std::endl;
		}

		else if (scoreSort[i] == scoreFourNum)
		{
			scores << scoreFour << std::endl;
		}

		else if (scoreSort[i] == scoreFiveNum)
		{
			scores << scoreFive << std::endl;
		}

		else if (scoreSort[i] == systemManager->getMaterial("Player")->getComponent("Points")->getDataInt().at(0))
		{
			scores << playerScore << std::endl;
		}
	}
	scores.close();

	//Reset score variables from file for display
	scores.open("scores.txt");
	getline(scores, scoreOne);
	getline(scores, scoreTwo);
	getline(scores, scoreThree);
	getline(scores, scoreFour);
	getline(scores, scoreFive);
	scores.close();

	//Display scores and initials
	sf::Text highScore;
	highScore.setFont(font);
	highScore.setString("High Scores:");
	highScore.setCharacterSize(18);
	window->draw(highScore);

	sf::Text scoreOneDraw;
	scoreOneDraw.setFont(font);
	scoreOneDraw.setString("\n"+scoreOne);
	scoreOneDraw.setCharacterSize(18);
	window->draw(scoreOneDraw);

	sf::Text scoreTwoDraw;
	scoreTwoDraw.setFont(font);
	scoreTwoDraw.setString("\n\n"+scoreTwo);
	scoreTwoDraw.setCharacterSize(18);
	window->draw(scoreTwoDraw);

	sf::Text scoreThreeDraw;
	scoreThreeDraw.setFont(font);
	scoreThreeDraw.setString("\n\n\n"+scoreThree);
	scoreThreeDraw.setCharacterSize(18);
	window->draw(scoreThreeDraw);

	sf::Text scoreFourDraw;
	scoreFourDraw.setFont(font);
	scoreFourDraw.setString("\n\n\n\n"+scoreFour);
	scoreFourDraw.setCharacterSize(18);
	window->draw(scoreFourDraw);

	sf::Text scoreFiveDraw;
	scoreFiveDraw.setFont(font);
	scoreFiveDraw.setString("\n\n\n\n\n"+scoreFive);
	scoreFiveDraw.setCharacterSize(18);
	window->draw(scoreFiveDraw);
	
	sf::Text proceed;
	proceed.setFont(font);
	proceed.setString("\n\n\n\n\n\nPress any key to end game...");
	proceed.setCharacterSize(18);
	window->draw(proceed);

	window->display();

	//Wait for a final keypress to end the game
	bool end = false;
	do
	{
		window->pollEvent(event);

		if (event.type == sf::Event::KeyPressed)
		{
			end = true;
		}

		else if (event.type == sf::Event::Closed)
		{
			end = true;
		}

	} while (!end);

	return;
}
