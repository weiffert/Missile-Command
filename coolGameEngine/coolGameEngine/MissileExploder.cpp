#include "MissileExploder.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "SystemManager.h"
#include "Property.h"
#include "Entity.h"
#include "ScoreKeeper.h"


MissileExploder::MissileExploder(SystemManager *s, AssetManager *a)
{
	systemManager = s;
	assetManager = a;
}


MissileExploder::~MissileExploder()
{
}


//This function currently explodes a missile, and creates a circle explosion
//This function is called from MissileLauncher
void MissileExploder::control(sf::RenderWindow * window, Entity *explodable)
{
	//Explosion Rate.
	double rate;
	rate = 2;
	double tempRadius;
	if (explodable->getComponent("Explode")->getDataBool().at(0)) //Makes sure the explosion didn't already happen
	{
		//If it doesn't already have an explosion, create one (property "ExplosionPhase" is 0)
		if (explodable->getComponent("ExplosionPhase")->getDataInt().at(0) == 0)
		{
			//Add explodable to exploding missiles for missileChecker.
			systemManager->getComponent("ExplodingMissiles")->addData(explodable);

			//In the first part of the explosion phase.
			explodable->getComponent("ExplosionPhase")->deleteData();
			explodable->getComponent("ExplosionPhase")->addData(1);

			//Set Explosion circle location.
			sf::CircleShape *c = explodable->getComponent("CircleShape")->getDataCircleShape().at(0);
			c->setPosition(explodable->getComponent("ExplodingPosition")->getDataDouble().at(0), explodable->getComponent("ExplodingPosition")->getDataDouble().at(1));

			//Change Missile Properties
			explodable->getComponent("Life")->deleteData();
			explodable->getComponent("Life")->addData(false);
			explodable->getComponent("DrawSprite")->deleteData();
			explodable->getComponent("DrawSprite")->addData(false);
			explodable->getComponent("DrawCircleShape")->deleteData();
			explodable->getComponent("DrawCircleShape")->addData(true);
			explodable->getComponent("DrawRectangleShape")->deleteData();
			explodable->getComponent("DrawRectangleShape")->addData(false);
			explodable->getComponent("Move")->deleteData();
			explodable->getComponent("Move")->addData(false);

			//Make Explosion sound
			sf::Sound * sound = new sf::Sound;
			sound->setBuffer(*explodable->getComponent("SoundMissileExplosion")->getDataSoundBuffer().at(0));
			assetManager->add(sound);
			sound->play();
			
			//Points handling.
			if (explodable->hasComponent("ShotDown"))
			{
				if (explodable->getComponent("ShotDown")->getDataBool().at(0))
				{
					ScoreKeeper scoreKeeper;
					//If its a missile.
					//Handling for satellite?
					if (explodable->getId().find("Plane") == std::string::npos)
					{
						if (explodable->getId().find("Enemy") != std::string::npos)
						{
							if (explodable->hasComponent("IsSmart"))
							{
								if (explodable->getComponent("IsSmart")->getDataBool().at(0))
								{
									scoreKeeper.increaseScore(125, systemManager->getMaterial("Player"));
								}
								else
								{
									scoreKeeper.increaseScore(25, systemManager->getMaterial("Player"));
								}
							}
							else
							{
								scoreKeeper.increaseScore(25, systemManager->getMaterial("Player"));
							}
						}
					}
					//Its a plane
					else
					{
						scoreKeeper.increaseScore(50, systemManager->getMaterial("Player"));
					}
				}
			}

		}

		//Check radius. 30 is the explosion radius max.
		if (explodable->getComponent("ExplosionRadius")->getDataDouble().at(0) >= 30)
		{
			explodable->getComponent("ExplosionPhase")->deleteData();
			explodable->getComponent("ExplosionPhase")->addData(-1);
		}

		//Check to see if the explosion disappears
		if (explodable->getComponent("ExplosionRadius")->getDataDouble().at(0) < 0)
		{
			explodable->getComponent("ExplosionRadius")->deleteData();
			explodable->getComponent("ExplosionRadius")->addData(0);
			explodable->getComponent("ExplosionPhase")->deleteData();
			explodable->getComponent("ExplosionPhase")->addData(-2);
			explodable->getComponent("Explode")->deleteData();
			explodable->getComponent("Explode")->addData(false);
			explodable->getComponent("DrawCircleShape")->deleteData();
			explodable->getComponent("DrawCircleShape")->addData(false);
			systemManager->getComponent("ExplodingMissiles")->deleteDataPosition(explodable->getId());
		}

		//Change the explosion circle.
		tempRadius = explodable->getComponent("ExplosionRadius")->getDataDouble().at(0);
		tempRadius += rate * explodable->getComponent("ExplosionPhase")->getDataInt().at(0);
		explodable->getComponent("ExplosionRadius")->deleteData();
		explodable->getComponent("ExplosionRadius")->addData(tempRadius);
		sf::CircleShape *c = explodable->getComponent("CircleShape")->getDataCircleShape().at(0);
		c->setRadius(tempRadius);
		c->setOrigin(c->getRadius(), c->getRadius());
	}
}
