#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"

class MissileLauncherAi
{
public:
	MissileLauncherAi(AssetManager *, SystemManager *);
	~MissileLauncherAi();
	void setTargets(bool[6]); //Takes an array of bools respresenting which cities are alive
	double setSlope(double, double);
	int launchMissiles(Entity *, sf::RenderWindow *); //Returns 0 if it fails to launch, 1 if it successfully launches
	int launchPlanes(Entity *, sf::RenderWindow *); //Returns 0 if it fails to launch, 1 if it successfully launches
	void update(sf::RenderWindow *, Entity *);

private:
	int targetOne, targetTwo, targetThree;
	SystemManager *systemManager;
	AssetManager *assetManager;
};
