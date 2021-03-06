#pragma once
#include <vector>
#include <string>

#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateReInit :
	public BaseState
{
public:
	StateReInit();
	//Takes in Game's systemManager and assetManager.
	StateReInit(SystemManager *, AssetManager *);
	virtual ~StateReInit();

	//Update function. Overloads the pure virtual update function in BaseState.
	virtual std::string update(double, sf::RenderWindow*);

	//Pause function for use in StateMenu, needed for inheritance but is useless in BaseState
	virtual void paused(sf::RenderWindow*) { return; }

	//End of game scorekeeping function for use in StateMenu, needed for inheritance
	virtual void endGame(sf::RenderWindow*) { return; }

private:
	//Stores filenames.
	std::vector<std::string> filenames;
	//Stores strings of function determiners.
	std::vector<std::string> substrings;

	std::vector<Property *> entityProperties;
	std::vector<std::vector<std::string>> entityPropertiesData;

	//Determines the current file to read.
	std::string fileDeterminer();

	//Sorts the substrings into the proper usage order.
	void substringSorter();
};

