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
void MissileExploder::control(sf::RenderWindow * window, Entity *missile)
{
	//Explosion Rate.
	double rate;
	rate = 2;
	double tempRadius;
	if (missile->getComponent("Explode")->getDataBool().at(0)) //Makes sure the explosion didn't already happen
	{
		//If it doesn't already have an explosion, create one (property "ExplosionPhase" is 0)
		if (missile->getComponent("ExplosionPhase")->getDataInt().at(0) == 0)
		{
			//Add missile to exploding missiles for missileChecker.
			systemManager->getComponent("ExplodingMissiles")->addData(missile);

			//In the first part of the explosion phase.
			missile->getComponent("ExplosionPhase")->deleteData();
			missile->getComponent("ExplosionPhase")->addData(1);

			//Set Explosion circle location.
			sf::CircleShape *c = missile->getComponent("CircleShape")->getDataCircleShape().at(0);
			c->setPosition(missile->getComponent("ExplodingPosition")->getDataDouble().at(0), missile->getComponent("ExplodingPosition")->getDataDouble().at(1));

			//Change Missile Properties
			missile->getComponent("Life")->deleteData();
			missile->getComponent("Life")->addData(false);
			missile->getComponent("DrawSprite")->deleteData();
			missile->getComponent("DrawSprite")->addData(false);
			missile->getComponent("DrawCircleShape")->deleteData();
			missile->getComponent("DrawCircleShape")->addData(true);
			missile->getComponent("DrawRectangleShape")->deleteData();
			missile->getComponent("DrawRectangleShape")->addData(false);
			missile->getComponent("Move")->deleteData();
			missile->getComponent("Move")->addData(false);

			//Make Explosion sound
			sf::Sound * sound = new sf::Sound;
			sound->setBuffer(*missile->getComponent("SoundMissileExplosion")->getDataSoundBuffer().at(0));
			assetManager->add(sound);
			sound->play();
			
			//Points handling.
			if (missile->hasComponent("ShotDown"))
			{
				if (missile->getComponent("ShotDown")->getDataBool().at(0))
				{
					ScoreKeeper scoreKeeper;
					//If its a missile.
					//Handling for satellite?
					if (missile->getId().find("Plane") == std::string::npos)
					{
						if (missile->getId().find("Enemy") != std::string::npos)
						{
							if (missile->hasComponent("IsSmart"))
							{
								if (missile->getComponent("IsSmart")->getDataBool().at(0))
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
		if (missile->getComponent("ExplosionRadius")->getDataDouble().at(0) >= 30)
		{
			missile->getComponent("ExplosionPhase")->deleteData();
			missile->getComponent("ExplosionPhase")->addData(-1);
		}

		//Check to see if the explosion disappears
		if (missile->getComponent("ExplosionRadius")->getDataDouble().at(0) < 0)
		{
			missile->getComponent("ExplosionRadius")->deleteData();
			missile->getComponent("ExplosionRadius")->addData(0);
			missile->getComponent("ExplosionPhase")->deleteData();
			missile->getComponent("ExplosionPhase")->addData(-2);
			missile->getComponent("Explode")->deleteData();
			missile->getComponent("Explode")->addData(false);
			missile->getComponent("DrawCircleShape")->deleteData();
			missile->getComponent("DrawCircleShape")->addData(false);
			systemManager->getComponent("ExplodingMissiles")->deleteDataPosition(missile->getId());
		}

		//Change the explosion circle.
		tempRadius = missile->getComponent("ExplosionRadius")->getDataDouble().at(0);
		tempRadius += rate * missile->getComponent("ExplosionPhase")->getDataInt().at(0);
		missile->getComponent("ExplosionRadius")->deleteData();
		missile->getComponent("ExplosionRadius")->addData(tempRadius);
		sf::CircleShape *c = missile->getComponent("CircleShape")->getDataCircleShape().at(0);
		c->setRadius(tempRadius);
		c->setOrigin(c->getRadius(), c->getRadius());
	}
}
