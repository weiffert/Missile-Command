//includes
#include "Game.h"
#include "SystemManager.h"
#include <time.h>
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

Game::Game(int width, int height, std::string name)
{
	windowResolution.x = width;
	windowResolution.y = height;
	gameName = name;
}

Game::~Game()
{

}


//Functions
int Game::run()
{
	//Enter Desired Game name and resolution into the render window functions
	//Considering reading window name and resolution from a file.
	sf::RenderWindow gameWindow(sf::VideoMode(windowResolution.x, windowResolution.y), gameName)

	state = new *StateLoading (systemManager);
	systemManager->addState(state);
	exitCode = gameLoop();
	//cleanup
	return exitCode;
}


int Game::gameLoop()
{
	bool running = true;
	int changeStateFlag = 1;
	//initialize time keepers
	double totaltime = 0.0;
	double frameRate = 0.01;

	double lag = 0.0;
	double currentTime = time(NULL);

	while(window.isOpen())
	{
		//initialize current time keepers
		double newTime = time(NULL);
		double frameTime = newTime - currentTime;
		
		if (frameTime > 0.25)
			frameTime = 0.25;

		currentTime = newTime;

		lag += frameTime;
		//process input
		while (lag >= frameRate)
		{
			//update
			changeStateFlag = state->update();
			//decrement current time keepers
			totalTime += frameRate;
			lag -= frameRate;
		}
		//render with parameters.
		state->render(lag/frameRate, &gameWindow);
		
		enum changeState { last = -1, stay = 0, next = 1};
		switch(changeStateFlag)
		{
		case next:
			state = changeState(state);
			break;
		case last:
			state = changeState(state, state.getNumber() - 1);
		}
	}
	return exitCode;
}


//Exceptions are thrown in the getState.
*Basestate Game::changeState(BaseState *b)
{
	int tempInt = b->getNumber();
	b = systemManager->getState(tempInt+1);

	return b;
}


//Exceptions are thrown in the getState.
*Basestate Game::changeState(BaseState *b, std::string s)
{
	b = systemManager->getState(s);

	return b;
}


//Exceptions are thrown in the getState.
*Basestate Game::changeState(BaseState *b, int i)
{
	b = systemManager->getState(i);

	return b;
}
