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


MissileChecker::MissileChecker(SystemManager * s, AssetManager * a)
{
	systemManager = s;
	assetManager = a;
}



MissileChecker::~MissileChecker()
{
}


void MissileChecker::control(sf::RenderWindow * window)
{
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
					if (temp->getComponent("IsSmart")->getDataBool().at(0))
					{
						sf::CircleShape *c = temp->getComponent("DodgeCircle")->getDataCircleShape().at(0);
						double xLeft, xRight, yTop, yBottom;
						xLeft = c->getGlobalBounds().left;
						xRight = xLeft + c->getGlobalBounds().width;
						yTop = c->getGlobalBounds().top;
						yBottom = yTop + c->getGlobalBounds().height;

						std::string id = "DodgeCircle" + temp->getId();

						//Insert into proper locations
						storeAndSort(xLeft, xRight, id, posX, idX);
						storeAndSort(yTop, yBottom, id, posY, idY);

						sf::Sprite *s = temp->getComponent("Sprite")->getDataSprite().at(0);
						xLeft = s->getGlobalBounds().left;
						xRight = xLeft + s->getGlobalBounds().width;
						yTop = s->getGlobalBounds().top;
						yBottom = yTop + s->getGlobalBounds().height;

						id = temp->getId();

						//Insert into proper locations
						storeAndSort(xLeft, xRight, id, posX, idX);
						storeAndSort(yTop, yBottom, id, posY, idY);
					}
					else
					{
						//Get new limits.
						sf::Sprite *s = temp->getComponent("Sprite")->getDataSprite().at(0);
						double x, y;
						x = s->getGlobalBounds().left + s->getGlobalBounds().width / 2;
						y = s->getGlobalBounds().top + s->getGlobalBounds().height / 2;
						//For all conventional purposes, it is basically a point.
						std::string id = temp->getId();

						//Insert into proper locations
						storeAndSort(x, id, posX, idX);
						storeAndSort(y, id, posY, idY);
					}
				}
			}
		}

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

		//Check ids.
		std::vector<std::string> checkTheseIdsX, checkTheseIdsY;
		checkables(keyword, idX, checkTheseIdsX);
		checkables(keyword, idY, checkTheseIdsY);

		//Pass through y values.
		for (int y = 0; y < checkTheseIdsY.size(); y++)
		{
			//Find explosion.
			if (checkTheseIdsY.at(y).find(keyword) != std::string::npos)
			{
				//Pass through x values.
				for (int x = 0; x < checkTheseIdsX.size(); x++)
				{
					//If the other explosion limit is found
					if (checkTheseIdsX.at(x) == checkTheseIdsY.at(y))
					{
						//Save the explosion id.
						std::string explosionId = checkTheseIdsX.at(x);
						explosionId = explosionId.substr(keyword.length(), explosionId.length() - keyword.length());

						//Find missiles that are inside of the explosion.
						bool found = false;
						int increment = x + 1;
						std::vector<std::string> finalCheckX, tempX;
						//Repeat while the other end is not found and we have not stepped out of bounds.
						while (!found && increment < checkTheseIdsX.size())
						{
							//If the other explosion limit is found.
							if (checkTheseIdsX.at(increment) == checkTheseIdsX.at(x))
							{
								found = true;
								checkTheseIdsX.erase(checkTheseIdsX.begin() + increment);
								//Update the y value from the for loop so that the same values are not rechecked.
								//y = increment;
							}
							else
							{
								//Push back the missile ids.
								if (checkTheseIdsX.at(increment).find(keyword) == std::string::npos)
									tempX.push_back(checkTheseIdsX.at(increment));
								increment++;
							}
						}

						if (found)
						{
							for (int i = 0; i < tempX.size(); i++)
							{
								finalCheckX.push_back(tempX.at(i));
							}
						}

						increment = y + 1;
						found = false;
						std::vector<std::string> finalCheckY, tempY;
						//Repeat while the other end is not found and we have not stepped out of bounds.
						while (!found && increment < checkTheseIdsY.size())
						{
							//If the other explosion limit is found.
							if (checkTheseIdsY.at(increment) == checkTheseIdsY.at(y))
							{
								found = true;
								//Update the y value from the for loop so that the same values are not rechecked.
								//y = increment;
								checkTheseIdsY.erase(checkTheseIdsY.begin() + increment);
							}
							else
							{
								//Push back the missile ids.
								if (checkTheseIdsY.at(increment).find(keyword) == std::string::npos)
									tempY.push_back(checkTheseIdsY.at(increment));
								increment++;
							}
						}

						if (found)
						{
							for (int i = 0; i < tempY.size(); i++)
							{
								finalCheckY.push_back(tempY.at(i));
							}
						}

						//Pass through the missile ids that are in the explosion.
						for (int i = 0; i < finalCheckX.size(); i++)
						{
							for (int j = 0; j < finalCheckY.size(); j++)
							{
								//If it is in both...
								if (finalCheckX.at(i) == finalCheckY.at(j))
								{
									sf::Vector2f position;
									Entity *currentExplodable;
									std::string dodge = "DodgeCircle";
									bool smart = false;
									if (finalCheckX.at(i).find(dodge) == std::string::npos)
										currentExplodable = systemManager->getMaterial(finalCheckX.at(i));
									else
									{
										currentExplodable = systemManager->getMaterial(finalCheckX.at(i).substr(dodge.length()));
										smart = true;
									}
									position.x = currentExplodable->getComponent("CurrentPosition")->getDataDouble().at(0);
									position.y = currentExplodable->getComponent("CurrentPosition")->getDataDouble().at(1);
									temp = systemManager->getMaterial(explosionId);

									//Check for collision.
									if (intersection(temp->getComponent("CircleShape")->getDataCircleShape().at(0), currentExplodable->getComponent("Sprite")->getDataSprite().at(0)) 
										|| intersection(temp->getComponent("CircleShape")->getDataCircleShape().at(0), position))
									{
										if (smart)
										{
											SmartBombControl smartBombControl;
											std::cout << "SMART BOMB CONTROL" << std::endl;
											smartBombControl.control(currentExplodable, temp);
										}
											//Set proper flags.
										//No missileExploder call because that is handled in the missileLaunchers.
										//Explode
										currentExplodable->getComponent("Explode")->deleteData();
										currentExplodable->getComponent("Explode")->addData(true);

										//Update Explosion Position
										currentExplodable->getComponent("ExplodingPosition")->deleteData();
										currentExplodable->getComponent("ExplodingPosition")->addData(position.x);
										currentExplodable->getComponent("ExplodingPosition")->addData(position.y);

										//Kept for knowing wheter to add points.
										currentExplodable->getComponent("ShotDown")->deleteData();
										currentExplodable->getComponent("ShotDown")->addData(true);
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

	while (!insertLow || !insertHigh)
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

void MissileChecker::storeAndSort(double value, std::string id, std::vector<double> & pos, std::vector<std::string> & ids)
{
	bool insert = false;
	int increment = 0;

	while (!insert)
	{
		if (increment < pos.size())
		{
			if (value < pos.at(increment))
			{
				pos.insert(pos.begin() + increment, value);

				if (increment < ids.size())
					ids.insert(ids.begin() + increment, id);
				else
					ids.push_back(id);

				insert = true;
			}
		}

		else
		{
			pos.push_back(value);
			ids.push_back(id);
			insert = true;
		}
		increment++;
	}

	return;
}


void MissileChecker::checkables(std::string keyword, std::vector<std::string> list, std::vector<std::string> & checkTheseIds)
{
	for (int i = list.size() - 1; i >= 0; i--)
	{
		if (list.at(i).find(keyword) != std::string::npos)
		{
			int decrement = list.size() - 2;
			std::vector<std::string> tempList;
			while (decrement >= 0 && list.at(decrement) != list.at(list.size() - 1))
			{
				if (list.at(decrement).find(keyword) == std::string::npos)
					tempList.push_back(list.at(decrement));
				decrement--;
			}
			if (tempList.size() > 0 && decrement >= 0)
			{
				checkTheseIds.push_back(list.at(list.size() - 1));

				for (int i = 0; i < tempList.size(); i++)
				{
					checkTheseIds.push_back(tempList.at(i));
				}

				checkTheseIds.push_back(list.at(list.size() - 1));
			}
		}
		list.pop_back();
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