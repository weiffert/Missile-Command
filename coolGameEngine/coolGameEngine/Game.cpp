#include "stdafx.h"

#include <string>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "Game.h"
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "StateLoading.h"
#include "StateDebug.h"
#include "StateMenu.h"


Game::Game()
{
}


//Constructor. Takes in the window width, height, and name.
Game::Game(int width, int height, std::string name)
{
	exitCode = 0;
	sf::VideoMode windowResolution;
	windowResolution.width = width;
	windowResolution.height = height;
	gameName = name;
	gameWindow.create( windowResolution, gameName);
	gameWindow.setVerticalSyncEnabled(false);
	gameWindow.setFramerateLimit(30);
	systemManager = new SystemManager();
	assetManager = new AssetManager();
}


Game::~Game()
{
	delete assetManager;
	delete systemManager;
	assetManager = nullptr;
	systemManager = nullptr;
}


//Runs the game.
//Returns the exit code.
int Game::run()
{
	//Create a state loading to start the game with.
	state = new StateLoading(systemManager, assetManager/*, &gameWindow*/);
	//Add it to the systemManager.
	systemManager->add(state);

	state->setMaterial(systemManager->getMaterial(state));

	//Seed the random number generator.
	srand(time(NULL));

	//run the game loop, which returns the exit code.
	exitCode = gameLoop();

	return exitCode;
}


//Runs the game loop.
//Returns the exit code.
int Game::gameLoop()
{
	std::string change = "constant";
	//initialize time keepers
	double totalTime = 0.0;
	double frameRate = 1;

	double lag = 0.0;
	double currentTime = time(NULL);

	sf::Clock clock;
	float lastTime = 0;

	//Run while the game window is open.
	while(gameWindow.isOpen())
	{
		//initialize current time keepers
		double newTime = time(NULL);
		double frameTime = newTime - currentTime;
		
		if (frameTime > 0.25)
			frameTime = 0.25;

		currentTime = newTime;

		lag += frameTime;
		//process input
		//while (lag >= frameRate)
		//{
			//update
			change = state->update(totalTime, &gameWindow);
			//decrement current time keepers
			totalTime += frameRate;
			lag -= frameRate;
		//}
		//render with parameters.
		state->render(lag/frameRate, &gameWindow);

		//Framerate counter
		float currentTime = clock.restart().asSeconds();
		int  fps = 1/ currentTime;
		lastTime = currentTime;

		if (change != "constant")
		{
			if (change != "next")
				state = systemManager->getState(change);
			else
				state = systemManager->getState(state->getNumber() + 1);
		}
	}

	//If a menu state hasn't been created, make one
	try
	{
		systemManager->getState("Menu");
	}
	catch (std::bad_typeid& error)
	{
		systemManager->add(new StateMenu(systemManager, assetManager));

		//Clear off the getstate warning caused by this try failing
		system("cls");
	}

	//Go into the highscore display and endgame
	systemManager->getState("Menu")->endGame(&gameWindow);

	return exitCode;
}