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
	/*
	//Old checker.
	//Goes through each enemy missile and determines if they should explode, if they should explode call on MissileExploder

	MissileExploder exploder;
	Entity *launcherAi = systemManager->getMaterial("MissileLauncherAi");
	Entity *currentMissile = nullptr;
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
					Entity *temp = missiles.at(u);
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
	*/

	//New Checker.
	std::vector<std::string> idX, idY;
	std::vector<double> posX, posY;
	std::string keyword = "Explosion";
	//Store limits.
	//Store explosions.
	Entity *temp = nullptr;
	std::vector<Entity *> missiles = systemManager->getComponent("ExplodingMissiles")->getDataEntity();
	
	if (missiles.size() > 0)
	{
		for (int i = 0; i < missiles.size(); i++)
		{
			//Get new limits.
			temp = missiles.at(i);
			sf::CircleShape *c = temp->getComponent("CircleShape")->getDataCircleShape().at(0);
			double xLeft, xRight, yTop, yBottom;
			xLeft = c->getGlobalBounds().left;
			xRight = xLeft + c->getGlobalBounds().width;
			yTop = c->getGlobalBounds().top;
			yBottom = yTop + c->getGlobalBounds().height;
			std::string id = keyword + temp->getId();

			//Insert into proper locations
			storeAndSort(xLeft, xRight, id, posX, idX);
			storeAndSort(yTop, yBottom, id, posY, idY);
		}

		//Storing missiles.
		Entity *launcherAi = systemManager->getMaterial("MissileLauncherAi");
		int totalMissileCount = launcherAi->getComponent("TotalMissileCount")->getDataInt().at(0);
		for (int i = launcherAi->getComponent("CurrentMissileCount")->getDataInt().at(0); i < totalMissileCount; i++)
		{
			if (i >= 0)
			{
				temp = launcherAi->getComponent("MissilesHeld")->getDataEntity().at(i);
				if (temp->getComponent("Fired")->getDataBool().at(0) && temp->getComponent("Life")->getDataBool().at(0))
				{
					//Get new limits.
					double xLeft, xRight, yTop, yBottom;
					sf::Sprite *s = temp->getComponent("Sprite")->getDataSprite().at(0);
					xLeft = s->getGlobalBounds().left;
					xRight = xLeft + s->getGlobalBounds().width;
					yTop = s->getGlobalBounds().top;
					yBottom = yTop + s->getGlobalBounds().height;
					std::string id = temp->getId();

					//Insert into proper locations
					storeAndSort(xLeft, xRight, id, posX, idX);
					storeAndSort(yTop, yBottom, id, posY, idY);
				}
			}
		}

		/*
		//Storing Planes.
		for (int i = launcherAi->getComponent("CurrentPlaneCount")->getDataInt().at(0) - 1; i < launcherAi->getComponent("TotalPlaneCount")->getDataInt().at(0); i++)
		{
		if (i >= 0)
		{
		//Get new limits.
		double xLeft, xRight, yTop, yBottom;
		temp = launcherAi->getComponent("PlanesHeld")->getDataEntity().at(i);
		sf::Sprite *s = temp->getComponent("Sprite")->getDataSprite().at(0);
		xLeft = s->getGlobalBounds().left;
		xRight = xLeft + s->getGlobalBounds().width;
		yTop = s->getGlobalBounds().top;
		yBottom = yTop + s->getGlobalBounds().height;
		std::string id = temp->getId();

		//Insert into proper locations
		storeAndSort(xLeft, xRight, id, posX, idX);
		storeAndSort(yTop, yBottom, id, posY, idY);
		}
		}
		*/

		//Check ids.
		std::vector<std::string> checkTheseIdsX, checkTheseIdsY, triggersX, triggersY;
		checkables(keyword, idX, checkTheseIdsX);
		checkables(keyword, idY, checkTheseIdsY);

		for (int y = 0; y < checkTheseIdsY.size(); y++)
		{
			if (checkTheseIdsY.at(y).find(keyword) != std::string::npos)
			{
				for (int x = 0; x < checkTheseIdsX.size(); x++)
				{
					if (checkTheseIdsX.at(x) == checkTheseIdsY.at(y))
					{
						std::string explosionId = checkTheseIdsX.at(x);
						explosionId = explosionId.substr(keyword.length(), explosionId.length() - keyword.length());

						bool found = false;
						int increment = x + 1;
						std::vector<std::string> finalCheckX;
						while (!found && increment < checkTheseIdsX.size())
						{
							if (checkTheseIdsX.at(increment).find(keyword) != std::string::npos)
							{
								found = true;
								x = increment;
							}
							else
							{
								finalCheckX.push_back(checkTheseIdsX.at(increment));
								increment++;
							}
						}

						increment = y + 1;
						found = false;
						std::vector<std::string> finalCheckY;
						while (!found && increment < checkTheseIdsY.size())
						{
							if (checkTheseIdsY.at(increment).find(keyword) != std::string::npos)
							{
								found = true;
								y = increment;
							}
							else
							{
								finalCheckY.push_back(checkTheseIdsY.at(increment));
								increment++;
							}
						}

						for (int i = 0; i < finalCheckX.size(); i++)
						{
							for (int j = 0; j < finalCheckY.size(); j++)
							{
								if (finalCheckX.at(i) == finalCheckY.at(j))
								{
									sf::Vector2f position;
									Entity *currentMissile = systemManager->getMaterial(finalCheckX.at(i));
									position.x = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0);
									position.y = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(1);
									temp = systemManager->getMaterial(explosionId);
									if (intersection(temp->getComponent("CircleShape")->getDataCircleShape().at(0), position))
									{
										//Explode
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

										MissileExploder exploder;
										exploder.control(systemManager, window, currentMissile);
										sf::CircleShape *c = currentMissile->getComponent("CircleShape")->getDataCircleShape().at(0);
										c->setPosition(currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0), currentMissile->getComponent("CurrentPosition")->getDataDouble().at(1));

										//Make sound
										//Explosion sound
										sf::Sound * sound = new sf::Sound;
										sound->setBuffer(*currentMissile->getComponent("SoundMissileExplosion")->getDataSoundBuffer().at(0));
										assetManager->add(sound);
										sound->play();
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void MissileChecker::storeAndSort(double small, double large, std::string id, std::vector<double> & pos, std::vector<std::string> & ids)
{
	bool insertLow = false;
	bool insertHigh = false;
	int increment = 0;

	while (!insertLow && !insertHigh)
	{
		if (increment < pos.size())
		{
			if (!insertLow && small < pos.at(increment))
			{
				pos.insert(pos.begin() + increment, small);

				if (increment < ids.size())
					ids.insert(ids.begin() + increment, id);
				else
					ids.push_back(id);

				insertLow = true;
			}
			if (!insertHigh && large < pos.at(increment))
			{
				pos.insert(pos.begin() + increment, large);

				if (increment < ids.size())
					ids.insert(ids.begin() + increment, id);
				else
					ids.push_back(id);

				insertHigh = true;
			}
		}

		else
		{
			if (small < large)
			{
				pos.push_back(small);
				pos.push_back(large);
				ids.push_back(id);
				ids.push_back(id);
			}
			else
			{
				pos.push_back(large);
				pos.push_back(small);
				ids.push_back(id);
				ids.push_back(id);
			}
			insertLow = true;
			insertHigh = true;
		}
		increment++;
	}

	return;
}

void MissileChecker::checkables(std::string keyword, std::vector<std::string> list, std::vector<std::string> & checkTheseIds)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i).find(keyword) != std::string::npos)
		{
			bool foundEnd = false;
			int added = i + 1;
			bool intersects = false;
			while (!foundEnd && added < list.size())
			{
				if (list.at(added) == list.at(i))
				{
					foundEnd = true;
					if (intersects)
					{
						checkTheseIds.push_back(list.at(added));
					}
				}
				else
				{
					if (list.at(added).find(keyword) == std::string::npos)
					{
						if (!intersects)
						{
							/*
							std::string s = list.at(added);
							s = s.substr(keyword.length(), keyword.length());
							checkTheseIds.push_back(s);
							*/
							checkTheseIds.push_back(list.at(i));
							intersects = true;
						}

						checkTheseIds.push_back(list.at(added));
					}
				}
				added++;
			}
			i = added;
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

	distance.x = spriteCenter.x - circleCenter.x;
	distance.y = spriteCenter.y - circleCenter.y;

	double angle = atan(distance.y / distance.x);

	angle *= -1;
	if (distance.x < 0)
		angle += 3.141592654;

	circleCenter.x += radius * cos(angle);
	circleCenter.y -= radius * sin(angle);

	if (other->getGlobalBounds().contains(circleCenter))
		return true;

	return false;
}


bool MissileChecker::intersection(sf::CircleShape *circle, sf::Sprite *other)
{
	float radius = circle->getLocalBounds().height / 2;

	sf::Vector2f distance;
	sf::Vector2f circleCenter;
	sf::Vector2f spriteCenter;

	circleCenter = sf::Vector2f((sf::FloatRect(circle->getGlobalBounds()).left) + (sf::FloatRect(circle->getGlobalBounds()).width / 2), (sf::FloatRect(circle->getGlobalBounds()).top) + sf::FloatRect(circle->getGlobalBounds()).height / 2);
	spriteCenter = sf::Vector2f((sf::FloatRect(other->getGlobalBounds()).left) + (sf::FloatRect(other->getGlobalBounds()).width / 2), (sf::FloatRect(other->getGlobalBounds()).top) + sf::FloatRect(other->getGlobalBounds()).height / 2);

	distance.x = spriteCenter.x - circleCenter.x;
	distance.y = spriteCenter.y - circleCenter.y;

	double angle = atan(distance.y / distance.x);

	angle *= -1;
	if (distance.x < 0)
		angle += 3.141592654;

	circleCenter.x += radius * cos(angle);
	circleCenter.y -= radius * sin(angle);

	if (other->getGlobalBounds().contains(circleCenter))
		return true;

	return false;
}

