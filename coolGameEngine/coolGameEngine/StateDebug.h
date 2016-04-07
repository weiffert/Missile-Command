#pragma once
#include <string>
#include <vector>

#include "BaseState.h"

#include "SystemManager.h"
#include "AssetManager.h"

class StateDebug :
	public BaseState
{
public:
	StateDebug();
	StateDebug(SystemManager*, AssetManager*, sf::RenderWindow *);
	~StateDebug();
	//Update function. Overloads the pure virtual update function in BaseState.
	virtual void update(double, sf::RenderWindow *);

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
	void initializeController(BaseController*, std::string, std::vector<std::string>);
	void initializeState(BaseState*, std::string, int);


	sf::Vector2i centerCoordinates;
};
