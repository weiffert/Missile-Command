#pragma once
#include <string>
#include <iostream>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"

class LevelChange
{
public:
	LevelChange();
	~LevelChange();

	std::string control(SystemManager *, AssetManager *, sf::RenderWindow *);
	std::string end(SystemManager *, AssetManager *);
};

