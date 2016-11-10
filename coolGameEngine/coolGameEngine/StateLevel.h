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

	virtual void paused(sf::RenderWindow*) { return; }
	virtual void endGame(sf::RenderWindow*) { return; }

private:
	sf::Vector2i centerCoordinates;
};

