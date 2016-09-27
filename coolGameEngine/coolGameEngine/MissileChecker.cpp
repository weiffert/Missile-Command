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


MissileChecker::MissileChecker()
{
}


MissileChecker::MissileChecker(SystemManager * s, AssetManager * a)
{
	systemManager = s;
	assetManager = a;
}



MissileChecker::~MissileChecker()
{
}


void MissileChecker::control(sf::RenderWindow * window, SystemManager * systemManager)
{
	//Goes through each enemy missile and determines if they should explode, if they should explode call on MissileExploder

	MissileExploder exploder;
	Entity *launcherAi = systemManager->getMaterial("MissileLauncherAi");
	Entity *currentMissile = nullptr;
	Entity *currentBase = nullptr;
	Entity *temp = nullptr;
	sf::Vector2f position;
	bool collision = false;

	//Only check for missiles that have been fired.
	for (int i = launcherAi->getComponent("CurrentMissileCount")->getDataInt().at(0) - 1; i < launcherAi->getComponent("TotalMissileCount")->getDataInt().at(0); i++)
	{
		if (i >= 0)
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
					//Makes sure that explosion is happening.
					if (temp->getComponent("Explode")->getDataBool().at(0))
					{
						if (temp->hasComponent("CircleShape"))
						{
							//Check for collision.
							if (intersection(temp->getComponent("CircleShape")->getDataCircleShape().at(0), position))
							{
								collision = true;
							}
							//Add smart bomb behaviors.
							if (currentMissile->hasComponent("IsSmart"))
							{
								if (currentMissile->getComponent("IsSmart")->getDataBool().at(0))
								{
									if (currentMissile->hasComponent("DodgeCircle"))
									{
										if (intersection(currentMissile, temp->getComponent("CircleShape")->getDataCircleShape().at(0), currentMissile->getComponent("DodgeCircle")->getDataCircleShape().at(0)))
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
			currentMissile->getComponent("ShotDown")->deleteData();
			currentMissile->getComponent("ShotDown")->addData(true);
			exploder.control(systemManager, window, currentMissile);
			sf::CircleShape *c = currentMissile->getComponent("CircleShape")->getDataCircleShape().at(0);
			c->setPosition(currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0), currentMissile ->getComponent("CurrentPosition")->getDataDouble().at(1));

			//Make sound
			//Explosion sound
			sf::Sound * sound = new sf::Sound;
			sound->setBuffer(*currentMissile->getComponent("SoundMissileExplosion")->getDataSoundBuffer().at(0));
			assetManager->add(sound);
			sound->play();
		}
	}
}

bool MissileChecker::intersection(sf::CircleShape *circle, sf::Vector2f point)
{
	float radius = circle->getLocalBounds().height / 2;
	sf::Vector2f distance;
	sf::Vector2f center;
	bool intersects = false;

	//Change in x from center of sprite to outside
	center = sf::Vector2f((sf::FloatRect(circle->getGlobalBounds()).left) + (sf::FloatRect(circle->getGlobalBounds()).width / 2), (sf::FloatRect(circle->getGlobalBounds()).top) + sf::FloatRect(circle->getGlobalBounds()).height / 2);
	distance.x = point.x - center.x;
	distance.y = point.y - center.y;
	if (distance.x * distance.x + distance.y * distance.y <= radius * radius)
		intersects = true;

	return intersects;
}

bool MissileChecker::intersection(Entity *e, sf::CircleShape *circle, sf::CircleShape *other)
{
	float radius = circle->getLocalBounds().height / 2;
	float otherRadius = other->getLocalBounds().height / 2;

	sf::Vector2f point;
	point.x = e->getComponent("CurrentPosition")->getDataDouble().at(0);
	point.y = e->getComponent("CurrentPosition")->getDataDouble().at(1);

	if (intersection(circle, point))
		return true;

	return false;
}


bool MissileChecker::intersection(Entity *e, sf::CircleShape *circle, sf::Sprite *other)
{
	float radius = circle->getLocalBounds().height / 2;

	sf::Vector2f distance;
	sf::Vector2f circleCenter;
	sf::Vector2f spriteCenter;

	circleCenter = sf::Vector2f((sf::FloatRect(circle->getGlobalBounds()).left) + (sf::FloatRect(circle->getGlobalBounds()).width / 2), (sf::FloatRect(circle->getGlobalBounds()).top) + sf::FloatRect(circle->getGlobalBounds()).height / 2);
	spriteCenter = sf::Vector2f((sf::FloatRect(other->getGlobalBounds()).left) + (sf::FloatRect(other->getGlobalBounds()).width / 2), (sf::FloatRect(other->getGlobalBounds()).top) + sf::FloatRect(other->getGlobalBounds()).height / 2);
	
	distance.x = circleCenter.x - spriteCenter.x;
	distance.y = circleCenter.y - spriteCenter.y;

	double angle = atan(distance.y / distance.x);
	
	if (distance.x > 0)
		angle += 3.141592654 / 2;

	circleCenter.x += radius * cos(angle);
	circleCenter.y -= radius * sin(angle);

	if (other->getGlobalBounds().contains(circleCenter))
		return true;

	return false;
}