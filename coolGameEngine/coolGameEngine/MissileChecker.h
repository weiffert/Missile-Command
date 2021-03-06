#pragma once
#include <string>

#include "SystemManager.h"
#include "AssetManager.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Entity.h"

class MissileChecker
{
public:
  MissileChecker(SystemManager *, AssetManager *);
  ~MissileChecker();
  void control(sf::RenderWindow *);
  bool intersection(sf::CircleShape*, sf::Vector2f); //Checks to see if a point is inside a circle
  bool intersection(sf::CircleShape*, sf::CircleShape*); //Checks to see if two circles intersect.
  bool intersection(sf::CircleShape*, sf::Sprite*); //Checks to see if a point is inside a rectangleshape

private:
	SystemManager *systemManager = nullptr;
	AssetManager *assetManager = nullptr;

	void storeAndSort(double, double, std::string, std::vector<double> &, std::vector<std::string> &);
	void storeAndSort(double, std::string, std::vector<double> &, std::vector<std::string> &);
	void checkables(std::string, std::vector<std::string>, std::vector<std::string> &);
};
