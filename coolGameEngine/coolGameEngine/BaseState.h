#pragma once
#include <string>
#include <vector>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "Entity.h"
#include "SystemManager.h"
#include "AssetManager.h"

class BaseState
{
public:
	BaseState();
	virtual ~BaseState();

	//Returns the state identification.
	int getNumber();
	std::string getId();

	//Set the state identification
	void setId(std::string);
	void setNumber(int);

	//Set the entities contained in the state.
	void setMaterial(std::vector<Entity*>);

	//Render a state.
	void render(double, sf::RenderWindow *);

	//Update function.
	virtual std::string update(double, sf::RenderWindow *) = 0;

	//Pause function for use in StateMenu, needed for inheritance but is useless in BaseState
	virtual void paused(sf::RenderWindow*) { return; }

	//End of game scorekeeping function for use in StateMenu, needed for inheritance
	virtual void endGame(sf::RenderWindow*) { return; }

protected:
	int number;
	std::string id;
	std::vector<Entity*> material;
	SystemManager* systemManager;
	AssetManager* assetManager;

	//Conversion function
	int conversionInt(std::string s);
	float conversionFloat(std::string s);
	double conversionDouble(std::string s);
};
