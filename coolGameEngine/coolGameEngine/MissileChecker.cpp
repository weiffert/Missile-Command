#include "MissileChecker.h"

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "SFML/Graphics.hpp"

#include "SystemManager.h"
#include "Property.h"
#include "Entity.h"

//Controllers
#include "MissileExploder.h"
#include "SmartBombControl.h"
#include "ScoreKeeper.h"

MissileChecker::MissileChecker()
{
}

MissileChecker::~MissileChecker()
{
}

void MissileChecker::control(sf::RenderWindow * window, SystemManager * systemManager, ScoreKeeper scoreKeeper)
{
  //Goes through each enemy missile and determines if they should explode, if they should explode call on MissileExploder
	
	MissileExploder exploder;
	Entity *currentMissile = nullptr;
	Entity *currentBase = nullptr;
	Entity *temp = nullptr;
	sf::Vector2f position;
	bool collision = false;

	Entity *launcherAi = systemManager->getMaterial("MissileLauncherAi");
	for (int i = launcherAi->getComponent("CurrentMissileCount")->getDataInt().at(0); i < launcherAi->getComponent("TotalMissileCount")->getDataInt().at(0); i++)
	{
		currentMissile = launcherAi->getComponent("MissilesHeld")->getDataEntity().at(i);
		position.x = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0);
		position.y = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(1);
		collision = false;
		
		//Go through each active missile and see if it is colliding with a circle shape from any missile explosion
		if (currentMissile->getComponent("Fired")->getDataBool().at(0) && currentMissile->getComponent("Life")->getDataBool().at(0))
		{
			//Check to see if it is colliding with a user fired missile explosion
			std::vector<Entity *> missiles = systemManager->getComponent("ExplodingMissiles")->getDataEntity();
			for (int u = 0; u < missiles.size(); u++)
			{
				temp = missiles.at(u);
				//Makes sure that explosion is not done and has not started
				if (temp->getComponent("Explode")->getDataBool().at(0))
				{
					if (temp->hasComponent("CircleShape"))
					{
						if (this->intersection(*temp->getComponent("CircleShape")->getDataCircleShape().at(0), position))
						{
							collision = true;
						}
						if (currentMissile->hasComponent("IsSmart"))
						{
							if (currentMissile->getComponent("IsSmart")->getDataBool().at(0))
							{
								if (currentMissile->hasComponent("DodgeCircle"))
								{
									if (this->intersection(currentMissile, *temp->getComponent("CircleShape")->getDataCircleShape().at(0), *currentMissile->getComponent("DodgeCircle")->getDataCircleShape().at(0)))
									{
										SmartBombControl smartBombControl(systemManager);
										smartBombControl.control(currentMissile, temp);
									}
								}
							}
						}
					}
				}
			}
		}
		if (collision)
		{
			currentMissile->getComponent("Life")->deleteData();
			currentMissile->getComponent("Life")->addData(false);
			currentMissile->getComponent("DrawSprite")->deleteData();
			currentMissile->getComponent("DrawSprite")->addData(false);
			currentMissile->getComponent("DrawCircleShape")->deleteData();
			currentMissile->getComponent("DrawCircleShape")->addData(true);
			currentMissile->getComponent("DrawRectangleShape")->deleteData();
			currentMissile->getComponent("DrawRectangleShape")->addData(false);
			currentMissile->getComponent("Move")->deleteData();
			currentMissile->getComponent("Move")->addData(false);
			currentMissile->getComponent("Explode")->deleteData();
			currentMissile->getComponent("Explode")->addData(true);
			exploder.control(systemManager, window, currentMissile);
			sf::CircleShape *c = currentMissile->getComponent("CircleShape")->getDataCircleShape().at(0);
			c->setPosition(currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0), currentMissile ->getComponent("CurrentPosition")->getDataDouble().at(1));

			if (currentMissile->hasComponent("IsSmart"))
			{
				if (currentMissile->getComponent("IsSmart")->getDataBool().at(0))
				{
					scoreKeeper.increaseScore(125, systemManager->getMaterial("Player"));
				}
			}
			else
			{
				scoreKeeper.increaseScore(25, systemManager->getMaterial("Player"));
			}

		}
	}
}


bool MissileChecker::intersection(sf::CircleShape circle, sf::Vector2f point)
{
	float radius = circle.getLocalBounds().height / 2;
	sf::Vector2f distance;
	sf::Vector2f center;
	bool intersects = false;

	//Change in x from center of sprite to outside
	center = sf::Vector2f((sf::FloatRect(circle.getGlobalBounds()).left) + (sf::FloatRect(circle.getGlobalBounds()).width/2), (sf::FloatRect(circle.getGlobalBounds()).top) + sf::FloatRect(circle.getGlobalBounds()).height /2);
	distance.x = point.x - center.x;
	distance.y = point.y - center.y;
	if (distance.x * distance.x + distance.y * distance.y <= radius * radius)
		intersects = true;

	return intersects;
}


bool MissileChecker::intersection(Entity *e, sf::CircleShape circle, sf::CircleShape other)
{
	float radius = circle.getLocalBounds().height / 2;
	float otherRadius = other.getLocalBounds().height / 2;
	sf::Vector2f distance;
	sf::Vector2f center;
	sf::Vector2f point;
	point.x = e->getComponent("CurrentPosition")->getDataDouble().at(0);
	point.y = e->getComponent("CurrentPosition")->getDataDouble().at(1);

	for (double theta = 0; theta < 2 * 3.141592654; theta += 3.141592654 / 6)
	{
		for (int i = 1; i < otherRadius; i++)
		{
			//Set point on the radius.
			point.x += i * cos(theta);
			point.y += i * sin(theta);

			if (intersection(circle, point))
				return true;

			point.x -= i*cos(theta);
			point.y -= i*sin(theta);
		}
	}
	return false;
}


bool MissileChecker::intersection(Entity *e, sf::CircleShape circle, sf::RectangleShape other)
{
	float radius = circle.getLocalBounds().height / 2;
	float x = other.getLocalBounds().width;
	float y = other.getLocalBounds().height;
	other.setOrigin(0, 0);

	sf::Vector2f distance;
	sf::Vector2f center;
	sf::Vector2f point;
	point.x = e->getComponent("CurrentPosition")->getDataDouble().at(0);
	point.y = e->getComponent("CurrentPosition")->getDataDouble().at(1);

	for (double theta = 0; theta < 2 * 3.141592654; theta += 3.141592654 / 6)
	{
		//Set point on the radius.
		point.x += radius * cos(theta);
		point.y += radius * sin(theta);

		if (other.getGlobalBounds().contains(point))
			return true;

		point.x -= radius * cos(theta);
		point.y -= radius * sin(theta);
	}
	return false;
}