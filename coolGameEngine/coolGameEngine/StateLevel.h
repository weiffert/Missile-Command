#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateLevel :
	public BaseState
{
public:
	//Takes in Game's systemManager and assetManager.
	StateLevel();
	StateLevel(SystemManager*, AssetManager *);
	virtual ~StateLevel();

	//Update function. Overloads the pure virtual update function in BaseState.
	virtual std::string update(double, sf::RenderWindow*);

	//Pause function for use in StateMenu, needed for inheritance but is useless in BaseState
	virtual void paused(sf::RenderWindow*) { return; }

	//End of game scorekeeping function for use in StateMenu, needed for inheritance
	virtual void endGame(sf::RenderWindow*) { return; }

private:
	sf::Vector2i centerCoordinates;
};

