#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateMenu :
	public BaseState
{
public:
	StateMenu();
	//Takes in Game's systemManager and assetManager.
	StateMenu(SystemManager *, AssetManager *);
	virtual ~StateMenu();

	//Update function. Overloads the pure virtual update function in BaseState.
	virtual std::string update(double, sf::RenderWindow *);

	//Function to control pause menu
	void paused(sf::RenderWindow*);

	//Function to control the end of game scorekeeping
	void endGame(sf::RenderWindow*);


private:
	sf::Mouse mouse;
	sf::Vector2i centerCoordinates;
};

