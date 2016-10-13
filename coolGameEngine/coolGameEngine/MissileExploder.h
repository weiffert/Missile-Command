#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"

class MissileExploder
{
public:
	MissileExploder(SystemManager *, AssetManager *);
	~MissileExploder();
	void control(sf::RenderWindow *, Entity *);

private:
	SystemManager *systemManager = nullptr;
	AssetManager *assetManager = nullptr;
};
