#include "stdafx.h"

#include <string>
#include <vector>

#include "BaseController.h"
#include "BaseComponent.h"


BaseController::BaseController()
{
	//Autoset id to BaseController
	id = "BaseController";
}


BaseController::~BaseController()
{
}


//Returns id
std::string BaseController::getId()
{
	return id;
}


//Sets id
//Takes in a string.
void BaseController::setId(std::string a)
{
	id = a;
	return;
}


//Sets the required properties.
//Takes in a pointer of a vector of BaseComponent pointers.
void BaseController::setRequiredProperties(std::vector<BaseComponent*> *a)
{
	for (int i = 0; i < a->size(); i++)
		requiredProperty.push_back(a->at(i));
}