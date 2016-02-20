#pragma once
#include "BaseState.h"
#include "SystemManager.h"
class StateWelcome :
	public BaseState
{
private: 

	SystemManager* systemManager;

public:
	StateWelcome(SystemManager *);
	~StateWelcome();

	int welcomeUpdate(double);
	void render(double, sf::RenderWindow)
};

