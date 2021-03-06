#include "MissileLauncherAi.h"

#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "MissileExploder.h"
#include "SmartBombControl.h"
#include "Property.h"
#include "Entity.h"


MissileLauncherAi::MissileLauncherAi(AssetManager *a, SystemManager *s)
{
	assetManager = a;
	systemManager = s;
}


MissileLauncherAi::~MissileLauncherAi()
{
	
}


void MissileLauncherAi::setTargets(bool cities[6])
{
	//Determine how many cities are left
	std::vector<bool> alive;
	std::vector<int> corresponding;
	int counter = 0;
	int number = 0;
	for (int i = 0; i < 6; i++)
	{
		if (cities[i])
		{
			alive.push_back(true);
			corresponding.push_back(i + 1);
		}
	}

	targetOne = 1;
	targetTwo = 1;
	targetThree = 1;

	while (targetOne == targetTwo && alive.size() > 1)
	{
		targetOne = rand() % alive.size() + 1;
	}
	while (targetOne == targetThree && alive.size() > 1)
	{
		targetThree = rand() % alive.size() + 1;
	}
	while (targetTwo == targetThree && alive.size() > 1)
	{
		targetTwo = rand() % alive.size() + 1;
	}

	targetOne = corresponding.at(targetOne - 1);
	targetTwo = corresponding.at(targetTwo - 1);
	targetThree = corresponding.at(targetThree - 1);

	Property *temp = systemManager->getMaterial("MissileLauncherAi")->getComponent("TargetOne");
	temp->deleteData();
	temp->addData(targetOne);

	temp = systemManager->getMaterial("MissileLauncherAi")->getComponent("TargetTwo");
	temp->deleteData();
	temp->addData(targetTwo);

	temp = systemManager->getMaterial("MissileLauncherAi")->getComponent("TargetThree");
	temp->deleteData();
	temp->addData(targetThree);
}


int MissileLauncherAi::launchMissiles(Entity *currentMissile, sf::RenderWindow *window)
{
	if (currentMissile->hasComponent("Sprite") && currentMissile->hasComponent("Draw") && currentMissile->hasComponent("Fired"))
	{
		if (!currentMissile->getComponent("Draw")->getDataBool().at(0) && !currentMissile->getComponent("Fired")->getDataBool().at(0))
		{
			sf::Sprite *s = currentMissile->getComponent("Sprite")->getDataSprite().at(0);
			sf::RectangleShape *r = currentMissile->getComponent("RectangleShape")->getDataRectangleShape().at(0);
			sf::Color *c = currentMissile->getComponent("ColorEnemy")->getDataColor().at(0);
			r->setFillColor(*c);
			r->setOutlineColor(*c);

			currentMissile->getComponent("DrawSprite")->deleteData();
			currentMissile->getComponent("DrawSprite")->addData(false);
			
			s->setOrigin(s->getLocalBounds().width, s->getLocalBounds().height);
		}
	}

	if (currentMissile->hasComponent("Move"))
	{
		currentMissile->getComponent("Move")->deleteData();
		currentMissile->getComponent("Move")->addData(true);
	}

	if (currentMissile->hasComponent("DrawRectangleShape"))
	{
		currentMissile->getComponent("DrawRectangleShape")->deleteData();
		currentMissile->getComponent("DrawRectangleShape")->addData(true);
	}

	if (currentMissile->hasComponent("Draw"))
	{
		currentMissile->getComponent("Draw")->deleteData();
		currentMissile->getComponent("Draw")->addData(true);
	}


	//Delete data for exploding position and starting position for missile
	currentMissile->getComponent("ExplodingPosition")->deleteData();
	currentMissile->getComponent("Target")->deleteData();

	targetOne = systemManager->getMaterial("MissileLauncherAi")->getComponent("TargetOne")->getDataInt().at(0);
	targetTwo = systemManager->getMaterial("MissileLauncherAi")->getComponent("TargetTwo")->getDataInt().at(0);
	targetThree = systemManager->getMaterial("MissileLauncherAi")->getComponent("TargetThree")->getDataInt().at(0);

	int missileTarget = rand() % 4 + 1;

	if (missileTarget % 2 == 0)
	{

		int currentTarget = rand() % 3 + 1;

		if (currentTarget == 1)
		{
			currentTarget = targetOne;
		}
		else if (currentTarget == 2)
		{
			currentTarget = targetTwo;
		}
		else
		{
			currentTarget = targetThree;
		}


		//Push back new values with starting and ending positions
		if (currentTarget == 1)
		{
			std::string target = "City1";
			currentMissile->getComponent("Target")->addData(target);
			//set position to the first city
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City1")->getComponent("CurrentPosition")->getDataDouble().at(0));
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City1")->getComponent("CurrentPosition")->getDataDouble().at(1));
		}

		else if (currentTarget == 2)
		{
			std::string target = "City2";
			currentMissile->getComponent("Target")->addData(target);
			//set position to the second city
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City2")->getComponent("CurrentPosition")->getDataDouble().at(0));
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City2")->getComponent("CurrentPosition")->getDataDouble().at(1));
		}

		else if (currentTarget == 3)
		{
			std::string target = "City3";
			currentMissile->getComponent("Target")->addData(target);
			//set position to the third city
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City3")->getComponent("CurrentPosition")->getDataDouble().at(0));
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City3")->getComponent("CurrentPosition")->getDataDouble().at(1));
		}

		else if (currentTarget == 4)
		{
			std::string target = "City4";
			currentMissile->getComponent("Target")->addData(target);
			//set position to the fourth city
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City4")->getComponent("CurrentPosition")->getDataDouble().at(0));
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City4")->getComponent("CurrentPosition")->getDataDouble().at(1));
		}

		else if (currentTarget == 5)
		{
			std::string target = "City5";
			currentMissile->getComponent("Target")->addData(target);
			//set position to the fifth city
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City5")->getComponent("CurrentPosition")->getDataDouble().at(0));
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City5")->getComponent("CurrentPosition")->getDataDouble().at(1));
		}

		else if (currentTarget == 6)
		{
			std::string target = "City6";
			currentMissile->getComponent("Target")->addData(target);
			//set position to the sixth city
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City6")->getComponent("CurrentPosition")->getDataDouble().at(0));
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("City6")->getComponent("CurrentPosition")->getDataDouble().at(1));
		}
		//Sometimes currentTarget does not == anything.  If this is the case, make it target a missile base
		else
		{
			int x = rand() % 3 + 1;

			if (x == 1)
			{
				std::string target = "Base1";
				currentMissile->getComponent("Target")->addData(target);
				currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base1")->getComponent("CurrentPosition")->getDataDouble().at(0)); //x for Base1
				currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base1")->getComponent("CurrentPosition")->getDataDouble().at(1)); //y for Base1
			}
			else if (x == 2)
			{
				std::string target = "Base2";
				currentMissile->getComponent("Target")->addData(target);
				currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base2")->getComponent("CurrentPosition")->getDataDouble().at(0)); //x for Base2
				currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base2")->getComponent("CurrentPosition")->getDataDouble().at(1)); //y for Base2
			}
			else
			{
				std::string target = "Base3";
				currentMissile->getComponent("Target")->addData(target);
				currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base3")->getComponent("CurrentPosition")->getDataDouble().at(0)); //x for Base3
				currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base3")->getComponent("CurrentPosition")->getDataDouble().at(1)); //y for Base3
			}
		}
	}
	else
	{
		int x = rand() % 3 + 1;

		if (x == 1)
		{
			std::string target = "Base1";
			currentMissile->getComponent("Target")->addData(target);
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base1")->getComponent("CurrentPosition")->getDataDouble().at(0)); //x for Base1
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base1")->getComponent("CurrentPosition")->getDataDouble().at(1)); //y for Base1
		}
		else if (x == 2)
		{
			std::string target = "Base2";
			currentMissile->getComponent("Target")->addData(target);
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base2")->getComponent("CurrentPosition")->getDataDouble().at(0)); //x for Base2
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base2")->getComponent("CurrentPosition")->getDataDouble().at(1)); //y for Base2
		}
		else
		{
			std::string target = "Base3";
			currentMissile->getComponent("Target")->addData(target);
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base3")->getComponent("CurrentPosition")->getDataDouble().at(0)); //x for Base3
			currentMissile->getComponent("ExplodingPosition")->addData(systemManager->getMaterial("Base3")->getComponent("CurrentPosition")->getDataDouble().at(1)); //y for Base3
		}

	}

	//Set missile launch location.
	Entity *launcherAi = systemManager->getMaterial("MissileLauncherAi");
	std::vector<Entity *> viablePlanes;
	//Tests if a plane is active.
	if (launcherAi->getComponent("CurrentPlaneCount")->getDataInt().at(0) < launcherAi->getComponent("TotalPlaneCount")->getDataInt().at(0))
	{
		std::vector<Entity *> planes = launcherAi->getComponent("PlanesHeld")->getDataEntity();
		for (int i = 0; i < planes.size(); i++)
		{
			if (planes.at(i)->getComponent("Fired")->getDataBool().at(0) && planes.at(i)->getComponent("Life")->getDataBool().at(0))
			{
				if (planes.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) > 0 && planes.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) < window->getSize().x)
					viablePlanes.push_back(planes.at(i));
			}
		}
	}

	bool notFiredFromPlane = true;
	//If there is at least one plane to fire from, and repeat if there are planes.
	for (int i = 0; i < viablePlanes.size(); i++)
	{
		//Random chance to fire missiles
		if (rand() % launcherAi->getComponent("MissileFireRate")->getDataInt().at(0) == 0)
		{
			notFiredFromPlane = false;

			//sets missile to have been split
			currentMissile->getComponent("Split")->deleteData();
			currentMissile->getComponent("Split")->addData(true);

			currentMissile->getComponent("SplitFired")->deleteData();
			currentMissile->getComponent("SplitFired")->addData(true);

			//Fire from plane
			currentMissile->getComponent("StartingPosition")->deleteData();
			currentMissile->getComponent("StartingPosition")->addData(viablePlanes.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0));
			currentMissile->getComponent("StartingPosition")->addData(viablePlanes.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));

			currentMissile->getComponent("CurrentPosition")->deleteData();
			currentMissile->getComponent("CurrentPosition")->addData(viablePlanes.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0));
			currentMissile->getComponent("CurrentPosition")->addData(viablePlanes.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));
		}
	}

	if (notFiredFromPlane)
	{
		//Sets missiles start to on top of screen
		if (currentMissile->getComponent("SplitFired")->getDataBool().at(0) == false)
		{
			int y = -5;
			int x = rand() % window->getSize().x + 1;

			currentMissile->getComponent("StartingPosition")->deleteData();
			currentMissile->getComponent("StartingPosition")->addData(x);
			currentMissile->getComponent("StartingPosition")->addData(y);

			currentMissile->getComponent("CurrentPosition")->deleteData();
			currentMissile->getComponent("CurrentPosition")->addData(x);
			currentMissile->getComponent("CurrentPosition")->addData(y);
		}
	}

	//Sets slope (Which is y/x)
	double changeX = 0;
	double changeY = 0;
	if (currentMissile->hasComponent("ExplodingPosition") && currentMissile->hasComponent("StartingPosition"))
	{
		changeX = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(0) - currentMissile->getComponent("StartingPosition")->getDataDouble().at(0);
		changeY = -1 * currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(1) - -1 * currentMissile->getComponent("StartingPosition")->getDataDouble().at(1);
	}

	if (currentMissile->hasComponent("Slope"))
	{
		currentMissile->getComponent("Slope")->deleteData();
		currentMissile->getComponent("Slope")->addData(changeY / changeX);
	}

	Property *vel = currentMissile->getComponent("Velocity");
	double velX = vel->getDataDouble().at(1);
	double curX = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0);
	double expX = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(0);
	double velY = vel->getDataDouble().at(2);
	double curY = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(1);
	double expY = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(1);

	double theta = atan((currentMissile->getComponent("CurrentPosition")->getDataDouble().at(1) - currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(1)) / (currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(0) - currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0)));

	if (theta > 0)
	{
		double temp = currentMissile->getComponent("Velocity")->getDataDouble().at(0);
		temp *= -1;
		vel->deleteData();
		vel->addData(temp);
		vel->addData(velX);
		vel->addData(velY);
	}

	if (currentMissile->hasComponent("Fired"))
	{
		currentMissile->getComponent("Fired")->deleteData();
		currentMissile->getComponent("Fired")->addData(true);
	}

	//Makes sure it wasn't split or shot from a plane
	if (currentMissile->getComponent("SplitFired")->getDataBool().at(0) == false)
	{
		if (rand() % systemManager->getMaterial("MissileLauncherAi")->getComponent("SmartBombChance")->getDataInt().at(0) == 0)
		{
			currentMissile->getComponent("IsSmart")->deleteData();
			currentMissile->getComponent("IsSmart")->addData(true);

			sf::Sprite *s = currentMissile->getComponent("Sprite")->getDataSprite().at(0);
			sf::Texture *t = new sf::Texture;
			if (!t->loadFromFile("smartBomb.png"))
				std::cout << "Failed to load smartBomb.png" << std::endl;
			s->setTexture(*t, true);

			s->setOrigin(s->getLocalBounds().width / 2, s->getLocalBounds().height / 2);

			assetManager->add(t);

			currentMissile->getComponent("DrawRectangleShape")->deleteData();
			currentMissile->getComponent("DrawRectangleShape")->addData(false);
			currentMissile->getComponent("DrawSprite")->deleteData();
			currentMissile->getComponent("DrawSprite")->addData(true);
			currentMissile->getComponent("Split")->deleteData();
			currentMissile->getComponent("Split")->addData(true);
			currentMissile->getComponent("SplitFired")->deleteData();
			currentMissile->getComponent("SplitFired")->addData(true);

			sf::RectangleShape *r = currentMissile->getComponent("RectangleShape")->getDataRectangleShape().at(0);
			sf::Color *c = new sf::Color(0, 0, 225);
			r->setFillColor(*c);
			r->setOutlineColor(*c);

		}
	}

	//Decrease missiles left
	Property *count = systemManager->getMaterial("MissileLauncherAi")->getComponent("CurrentMissileCount");
	int oldMissileCount = count->getDataInt().at(0);
	count->deleteData();
	count->addData(--oldMissileCount);

	return 1;
}


int MissileLauncherAi::launchPlanes(Entity *currentPlane, sf::RenderWindow *window)
{
	int yHeight = 0;
	std::string direction;

	//Determines plane direction (left or right)
	currentPlane->getComponent("CurrentPosition")->deleteData();

	//Left
	if (rand() % 2 == 0)
	{
		direction = "Left";
		currentPlane->getComponent("Direction")->changeData(direction, 0);

		//Give correct x value
		//A variable is used to remedy unsigned int error.
		int width = window->getSize().x;
		currentPlane->getComponent("CurrentPosition")->addData(width + 50);
	}

	//Right
	else
	{
		direction = "Right";
		currentPlane->getComponent("Direction")->changeData(direction, 0);

		//Give correct x value
		currentPlane->getComponent("CurrentPosition")->addData(-50);
	}

	//Give "random" y height above window height * 5 / 6 and belows than window height / 4.
	do 
	{
		yHeight = rand() % window->getSize().y * 4 / 5;
	} while (yHeight > window->getSize().y / 3 * 2);

	currentPlane->getComponent("CurrentPosition")->addData(yHeight);

	//Make it either a satellite or a plane.
	sf::Sprite *s = new sf::Sprite;
	s->setPosition(currentPlane->getComponent("CurrentPosition")->getDataDouble().at(0), currentPlane->getComponent("CurrentPosition")->getDataDouble().at(1));
	sf::Texture *texture = new sf::Texture;
	if (rand() % 2 == 0)
	{
		if (!texture->loadFromFile("satellite.png"))
			std::cout << "Failed to load satellite.png" << std::endl;
	}
	else
	{
		if (direction == "Right")
		{
			if (!texture->loadFromFile("plane.png"))
				std::cout << "Failed to load plane.png" << std::endl;
		}
		else
		{
			if (!texture->loadFromFile("plane-other-direction.png"))
				std::cout << "Failed to load plane-other-direction.png" << std::endl;
		}
	}

	s->setTexture(*texture, true);
	s->setOrigin(s->getLocalBounds().width / 2, s->getLocalBounds().height / 2);
	currentPlane->getComponent("Sprite")->deleteData();
	currentPlane->getComponent("Sprite")->addData(s);

	assetManager->add(texture);

	//Set other values
	//Sets draw to true which shows it is on the screen
	currentPlane->getComponent("Draw")->deleteData();
	currentPlane->getComponent("Draw")->addData(true);
	currentPlane->getComponent("Life")->deleteData();
	currentPlane->getComponent("Life")->addData(true);
	currentPlane->getComponent("DrawSprite")->deleteData();
	currentPlane->getComponent("DrawSprite")->addData(true);
	currentPlane->getComponent("DrawCircleShape")->deleteData();
	currentPlane->getComponent("DrawCircleShape")->addData(false);
	currentPlane->getComponent("Fired")->deleteData();
	currentPlane->getComponent("Fired")->addData(true);
	currentPlane->getComponent("Move")->deleteData();
	currentPlane->getComponent("Move")->addData(true);
	currentPlane->getComponent("Explode")->deleteData();
	currentPlane->getComponent("Explode")->addData(false);


	//Decrease missiles left
	Property *count = systemManager->getMaterial("MissileLauncherAi")->getComponent("CurrentPlaneCount");
	int oldPlaneCount = count->getDataInt().at(0);
	count->deleteData();
	count->addData(--oldPlaneCount);

	return 1;
}


double MissileLauncherAi::setSlope(double pathX, double pathY)
{
  double speedX;
  
  speedX = pathX / pathY;
  
  return speedX;
}


void MissileLauncherAi::update(sf::RenderWindow *window, Entity *launcherAi)
{
	double slope;
	double temp1, temp2;
	double length;
	sf::Vector2f rectLength;
	sf::RectangleShape *temp = nullptr;
	//SmartBombControl smartBombControl;

	std::vector<Entity*> missiles = launcherAi->getComponent("MissilesHeld")->getDataEntity();
	//Goes through all the missiles
	for (int i = launcherAi->getComponent("TotalMissileCount")->getDataInt().at(0) - 1; i > -1; i--)
	{
		if (missiles.at(i)->hasComponent("Fired") && missiles.at(i)->hasComponent("Life"))
		{
			if (missiles.at(i)->getComponent("Fired")->getDataBool().at(0) && missiles.at(i)->getComponent("Life")->getDataBool().at(0))
			{
				if (missiles.at(i)->hasComponent("Slope"))
					slope = missiles.at(i)->getComponent("Slope")->getDataDouble().at(0);

				if (missiles.at(i)->hasComponent("CurrentPosition") && missiles.at(i)->hasComponent("Velocity"))
				{
					if (!missiles.at(i)->getComponent("BeenMoved")->getDataBool().at(0))
					{
						double theta = atan((missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) - missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1)) / (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) - missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0)));
						double velocity = missiles.at(i)->getComponent("Velocity")->getDataDouble().at(0);
						double lengthX = velocity * cos(theta);
						double lengthY = velocity * sin(theta);

						temp1 = missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) + lengthX;
						temp2 = slope * (temp1 - missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0)) + -1 * missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1);
						temp2 *= -1;

						missiles.at(i)->getComponent("Velocity")->deleteData();
						missiles.at(i)->getComponent("Velocity")->addData(velocity);
						missiles.at(i)->getComponent("Velocity")->addData(lengthX);
						missiles.at(i)->getComponent("Velocity")->addData(lengthY);

						missiles.at(i)->getComponent("CurrentPosition")->deleteData();
						missiles.at(i)->getComponent("CurrentPosition")->addData(temp1);
						missiles.at(i)->getComponent("CurrentPosition")->addData(temp2);


						sf::Sprite *s = missiles.at(i)->getComponent("Sprite")->getDataSprite().at(0);
						s->setPosition(temp1, temp2);

						if (missiles.at(i)->getComponent("IsSmart")->getDataBool().at(0))
						{
							sf::CircleShape *c = missiles.at(i)->getComponent("DodgeCircle")->getDataCircleShape().at(0);
							c->setPosition(temp1, temp2);
						}

						if (missiles.at(i)->getComponent("DrawRectangleShape")->getDataBool().at(0))
						{
							//Update the chem trails, set the chem trail length to the velocity
							double curX = missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0);
							double staX = missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(0);
							double curY = missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1);
							double staY = missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(1);

							length = sqrt(pow(staX - curX, 2) + pow(staY - curY, 2));
							temp = missiles.at(i)->getComponent("RectangleShape")->getDataRectangleShape().at(0);
							rectLength = temp->getSize();
							rectLength.x = length;
							temp->setSize(rectLength);
							if (missiles.at(i)->getComponent("Velocity")->getDataDouble().at(0) < 0)
								temp->setRotation(-1 * theta * 180 / 3.141592654 + 180);
							else
								temp->setRotation(-1 * theta * 180 / 3.141592654);
							temp->setPosition(missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(0), missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(1));
							temp->setOrigin(0, temp->getLocalBounds().height);
						}
					}
					else
					{
						//Reset Variables
						missiles.at(i)->getComponent("BeenMoved")->deleteData();
						missiles.at(i)->getComponent("BeenMoved")->addData(false);

						//Fix slope to remedy the move.
						double changeX = missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) - missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0);
						double changeY = -1 * missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) - -1 * missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1);

						missiles.at(i)->getComponent("Slope")->deleteData();
						missiles.at(i)->getComponent("Slope")->addData(changeY / changeX);
					}
				}

				//If the current Missile is positioned on its explosion point, (give an error of the velocity amount)
				double velocity = missiles.at(i)->getComponent("Velocity")->getDataDouble().at(0);
				velocity = abs(velocity);

				//Check x values
				if (!(missiles.at(i)->getComponent("Explode")->getDataBool().at(0)))
				{
					if (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) - velocity <=
						missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) &&
						missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) + velocity >=
						missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0))
					{
						//check y values
						if (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) - velocity <=
							missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) &&
							missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) + velocity >=
							missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1))
						{
							//Make the missile explode
							missiles.at(i)->getComponent("Explode")->deleteData();
							missiles.at(i)->getComponent("Explode")->addData(true);

							//Do whatever to what was exploded.
							std::string targetString = missiles.at(i)->getComponent("Target")->getDataString().at(0);
							Entity *target = systemManager->getMaterial(targetString);
							if (target->getComponent("Life")->getDataBool().at(0))
							{
								target->getComponent("Life")->deleteData();
								target->getComponent("Life")->addData(false);

								if (targetString.find("Base") != std::string::npos)
								{
									target->getComponent("Text")->getDataText().at(0)->setString("Out");
									target->getComponent("Draw")->deleteData();
									target->getComponent("Draw")->addData(true);
									for (int i = 0; i < target->getComponent("CurrentMissileCount")->getDataInt().at(0); i++)
									{
										Entity *missile = target->getComponent("MissilesHeld")->getDataEntity().at(i);
										missile->getComponent("Life")->deleteData();
										missile->getComponent("Life")->addData(false);
										missile->getComponent("Draw")->deleteData();
										missile->getComponent("Draw")->addData(false);
										missile->getComponent("DrawSprite")->deleteData();
										missile->getComponent("DrawSprite")->addData(false);
									}

									target->getComponent("CurrentMissileCount")->deleteData();
									target->getComponent("CurrentMissileCount")->addData(0);
								}
								else
								{
									sf::Sprite *s = target->getComponent("Sprite")->getDataSprite().at(0);
									sf::Texture *t = new sf::Texture;

									if (!t->loadFromFile("ruin.png"))
										std::cout << "Failed to load ruin.png" << std::endl;
									s->setTexture(*t, true);

									assetManager->add(t);
								}
							}
						}
					}
				}
				//checks if missile already split and is high enough
				if (missiles.at(i)->getComponent("Split")->getDataBool().at(0) == false && missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) < 340)
				{
					//random chance to not split
					if (rand() % launcherAi->getComponent("SplitChance")->getDataInt().at(0) == 0)
					{
						int decrement = launcherAi->getComponent("CurrentMissileCount")->getDataInt().at(0) - 1;
						bool found = false;
						Entity *missile = nullptr;
						while (!found && decrement >= 0)
						{
							if (missiles.at(decrement)->hasComponent("Fired"))
							{
								if (missiles.at(decrement)->getComponent("Fired")->getDataBool().at(0) == false)
								{
									found = true;
									missile = missiles.at(decrement);
								}
							}
							decrement--;
						}
						if (found)
						{
							//sets missile to have been split
							missiles.at(i)->getComponent("Split")->deleteData();
							missiles.at(i)->getComponent("Split")->addData(true);

							missile->getComponent("SplitFired")->deleteData();
							missile->getComponent("SplitFired")->addData(true);

							missile->getComponent("StartingPosition")->deleteData();
							missile->getComponent("StartingPosition")->addData(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0));
							missile->getComponent("StartingPosition")->addData(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));

							missile->getComponent("CurrentPosition")->deleteData();
							missile->getComponent("CurrentPosition")->addData(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0));
							missile->getComponent("CurrentPosition")->addData(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));

							launchMissiles(missile, window);
						}
					}
				}
			}
		}

		if (missiles.at(i)->hasComponent("Explode"))
		{
			if (missiles.at(i)->getComponent("Explode")->getDataBool().at(0))
			{
				MissileExploder exploder(systemManager, assetManager);
				exploder.control(window, missiles.at(i));
			}
		}
	}

	//Go through all planes.
	std::vector<Entity*> planes = launcherAi->getComponent("PlanesHeld")->getDataEntity();
	//Goes through all the missiles
	for (int i = launcherAi->getComponent("TotalPlaneCount")->getDataInt().at(0) - 1; i > -1; i--)
	{
		Entity *currentPlane = planes.at(i);
		if (currentPlane->hasComponent("Fired") && currentPlane->hasComponent("Life"))
		{
			if (currentPlane->getComponent("Fired")->getDataBool().at(0) && currentPlane->getComponent("Life")->getDataBool().at(0))
			{
				//Moves current plane
				if (currentPlane->getComponent("Direction")->getDataString().at(0) == "Right")
					temp1 = currentPlane->getComponent("CurrentPosition")->getDataDouble().at(0) + currentPlane->getComponent("Velocity")->getDataDouble().at(0);
				else
					temp1 = currentPlane->getComponent("CurrentPosition")->getDataDouble().at(0) - currentPlane->getComponent("Velocity")->getDataDouble().at(0);

				//Set plane location
				sf::Sprite *s = currentPlane->getComponent("Sprite")->getDataSprite().at(0);
				s->setPosition(sf::Vector2f(temp1, currentPlane->getComponent("CurrentPosition")->getDataDouble().at(1)));

				currentPlane->getComponent("CurrentPosition")->changeData(temp1, 0);

				//If it's off the screen kill the plane
				if ((temp1 > window->getSize().x + currentPlane->getComponent("Sprite")->getDataSprite().at(0)->getLocalBounds().width / 2 
					&& currentPlane->getComponent("Direction")->getDataString().at(0) == "Right") 
					|| (temp1 < 0 - currentPlane->getComponent("Sprite")->getDataSprite().at(0)->getLocalBounds().width / 2 
					&& currentPlane->getComponent("Direction")->getDataString().at(0) == "Left"))
				{
					currentPlane->getComponent("Life")->deleteData();
					currentPlane->getComponent("Life")->addData(false);
					currentPlane->getComponent("Draw")->deleteData();
					currentPlane->getComponent("Draw")->addData(false);
				}
			}
			
			if (!(currentPlane->getComponent("Fired")->getDataBool().at(0)))
			{
				if (currentPlane->getComponent("Life")->getDataBool().at(0))
				{
					if (rand() % launcherAi->getComponent("PlaneFireRate")->getDataInt().at(0) == 0)
					{
						launchPlanes(currentPlane, window);
					}
				}
			}
		}

		if (planes.at(i)->hasComponent("Explode"))
		{
			if (planes.at(i)->getComponent("Explode")->getDataBool().at(0))
			{
				MissileExploder exploder(systemManager, assetManager);
				exploder.control(window, planes.at(i));
			}
		}
	}
}
