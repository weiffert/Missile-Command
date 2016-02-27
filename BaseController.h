#pragma once
#include <string>
#include <vector>

#include "BaseComponent.h"


class BaseController
{
public:
	BaseController();
	~BaseController();

	//Change Id.
	std::string getId();
	void setId(std::string);

	//Set required properties.
	void setRequiredProperties(std::vector<BaseComponent*> *);

protected:
	std::string id;
	std::vector<BaseComponent*> requiredProperty;
};
