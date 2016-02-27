#include "stdafx.h"

#include <vector>
#include <fstream>
#include <string>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "StateEnd.h"
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "StateLoading.h"
#include "Entity.h"



//SFML includes

StateEnd::StateEnd(SystemManager *s, AssetManager *a)
{
	//Sets defaults.
	id = "End";
	number = 4;
	systemManager = s;
	assetManager = a;

	//Reads in the filenames and substrings.
	std::ifstream file("file.txt");
	if (file.is_open())
	{
		std::string temp;
		while (!file.eof())
		{
			if (temp == "Filenames")
			{
				while (temp != "Substrings" && !file.eof())
				{
					file >> temp;
					filenames.push_back(temp);
				}
			}
			if (temp == "Substrings")
			{
				while (temp != "Filenames" && !file.eof())
				{
					file >> temp;
					filenames.push_back(temp);
				}
			}
		}
	}

	//Sorts the substrings into the proper order.
	substringSorter();
}


StateEnd::~StateEnd()
{
}


//Determines the proper file to use based off of the current substring.
//Deletes the filename once it has been determined. Deletes the substring after all of its files have been used.
std::string StateLoading::fileDeterminer()
{
	//Passes through all of the filenames.
	for (int i = 0; i < filenames.size(); i++)
	{
		//If the base substring is found in the filename...
		if (filenames.at(i).find(substrings.at(0)) != std::string::npos)
		{
			std::string temp = filenames.at(i);
			filenames.erase(i);
			return temp;
		}
	}

	//There are no filenames with this substring name, so it is done.
	substrings.erase(0);
	return nullptr;
}


//Sorts the substrings into a particular order.
void StateLoading::substringSorter()
{
	//Passes through all of the substrings.
	for (int i = 0; i < substrings.size(); i++)
	{
		//Stores the substring that is supposed to be at that position.
		std::string sub;
		switch (i)
		{
		case 0:
			sub = "png";
			break;
		case 1:
			sub = "property";
			break;
		case 2:
			sub = "entity";
			break;
		case 3:
			sub = "controller";
			break;
		case 4:
			sub = "state";
			break;
		default:
			sub = "default";
		}

		//If it is not in the proper position...
		if (substrings.at(1) != sub)
		{
			//Pass through all of the rest of the substrings.
			for (int j = i; j < substrings.size(); i++)
			{
				//If one does equal the proper substring...
				if (substrings.at(j) == sub)
				{
					//Switch positions.
					std::string temp = substrings.at(j);
					substrings.at(j) = substrings.at(i);
					substrings.at(i) = temp;
				}
			}
		}
	}
}


void StateEnd::update(double totalTime, sf::RenderWindow* window)
{
	if (substrings.size() != 0)
	{
		std::string id = " ";
		std::string filename;
		std::string word;
		int lineNumber = 1; //The line number of the file
		int wordNumber = 1; //Determines which word of the line (1st, 2nd, 3rd, words in a line or more)
		//Determine the file to parse data from.
		filename = fileDeterminer();
		std::ifstream file(filename);
		std::string type;

		//Determine the operation.
		if (substrings.at(0) == "property")
		{
			std::vector<std::string> data;
			

			//Read data and take in these values. Includes id

			//Read entire file
			while (!file.eof())
			{
				file >> word;
				while (word != ";") //Read until the end of the line
				{
					if (lineNumber == 1)
						id = word;
					if (lineNumber == 2)
						type = word;
					if (lineNumber > 2)
						data.push_back(word);
					file >> word;
				}
				//Increase line number
				lineNumber++;
			}
			BaseComponent *temp = systemManager->getComponent(id);

			if (type == "int")
			{
				temp->deleteData();
				for (int i = 0; i < data.size(); i++)
					temp->addData(std::stoi(data.at(i)));
			}

			else if (type == "char")
			{
				temp->deleteData();
				for (int i = 0; i < data.size(); i++)
					temp->addData(data.at(i).c_str());
			}

			else if (type == "double")
			{
				temp->deleteData();
				for (int i = 0; i < data.size(); i++)
					temp->addData(std::stod(data.at(i)));
			}

			else if (type == "float")
			{
				temp->deleteData();
				for (int i = 0; i < data.size(); i++)
					temp->addData(std::stof(data.at(i)));
			}

			else if (type == "bool")
			{
				temp->deleteData();
				bool tOrF = false;
				if (data.at(0) == "true")
					tOrF = true;
				temp->getComponent(properties.at(y).at(0))->addData(tOrF);
			}

			else if (type == "string")
			{
				temp->deleteData();
				for (int i = 0; i < data.size(); i++)
					temp->addData(data.at(i));
			}

			else if (type == "Entity")
			{
				temp->deleteData();
				//Get the proper data from the id in the file.
				for (int i = 0; i < data.size(); i++)
					temp->add(systemManager->getEntity(data.at(i));
			}

			else if (type == "Texture")
			{
				temp->deleteData();
				//Get the proper data from the id in the file.
				for (int i = 0; i < data.size(); i++)
					temp->add(assetManager->getTexture(std::stoi(data.at(i)));
			}

			else if (type == "Image")
			{
				temp->deleteData();
				//Get the proper data from the id in the file.
				for (int i = 0; i < data.size(); i++)
					temp->add(assetManager->getTexture(data.at(i));
			}

			else if (type == "Sound")
			{
				temp->deleteData();
				//Get the proper data from the id in the file.
				for (int i = 0; i < data.size(); i++)
					temp->add(assetManager->getSound(data.at(i));
			}

			else
			{
				temp->deleteData();
				for (int i = 0; i < data.size(); i++)
					temp->addData(data.at(i));
			}

		}
		else if (substrings.at(0) == "entity")
		{
			std::vector<std::vector<std::string>>properties;   //The first vector is for holding all properties. The second is for holding id 
			//and data of the properties.

			//Read data and take in these values. Includes id.
			while (!file.eof())
			{
				file >> word;
				while (word != ";") //Read until the end of the line
				{
					if (lineNumber == 1)
						id = word;
					if (lineNumber > 1)
					{
						if (wordNumber == 1)
							properties.at(lineNumber - 1).at(wordNumber - 1);
					}

					file >> word;
					wordNumber++;
				}
				lineNumber++;	//Increase line number
				wordNumber = 1; //Set wordNumber back to 1
			}

			//Create.
			Entity *temp = systemManager->getMaterial(id);

			//Edit.
			//Loop for the vector.
			for (int y = 0; y < properties.size(); y++)
			{
				//Loop for the vector in the vector.
				for (int x = 0; x < properties.at(y).size(); x++)
				{
					//If there is data.
					if (properties.at(y).size() > 1)
					{
						//If it is the first iteration, clone the property.
						if (x == 0)
						{
							BaseComponent *component = systemManager->getComponent(properties.at(y).at(x));
							systemManager->add(component);
							temp->remove(component);
							temp->add(component);
						}
						//Change Data.
						else
						{
							//Needs to be converted to the proper type.
							if (type == "int")
							{
								temp->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(std::stoi(properties.at(y).at(x)));
							}

							else if (type == "char")
							{
								temp->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(properties.at(y).at(x).c_str());
							}

							else if (type == "double")
							{
								temp->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(std::stod(properties.at(y).at(x)));
							}

							else if (type == "float")
							{
								temp->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(std::stof(properties.at(y).at(x)));
							}

							else if (type == "bool")
							{
								bool tOrF = false;

								if (properties.at(y).at(x) == "true")
									tOrF = true;

								temp->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(tOrF);
							}

							else if (type == "string")
							{
								temp->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(properties.at(y).at(x);
							}

							else if (type == "Entity")
							{
								temp->deleteData();
								//Get the proper data from the id in the file.
								temp->getComponent(properties.at(y).at(x))->addData(systemManager->getMaterial(properties.at(y).at(x)));
							}

							else if (type == "Texture")
							{
								temp->deleteData();
								//Get the proper data from the id in the file.
								temp->getComponent(properties.at(y).at(x))->addData(assetManager->getTexture(std::stoi(properties.at(y).at(x))));
							}

							else if (type == "Image")
							{
								temp->deleteData();
								//Get the proper data from the id in the file.
								temp->getComponent(properties.at(y).at(x))->addData(assetManager->getComponent(properties.at(y).at(x)));
							}

							else if (type == "Sound")
							{
								temp->deleteData();
								//Get the proper data from the id in the file.
								temp->getComponent(properties.at(y).at(x))->addData(assetManager->getSound(properties.at(y).at(x)));
							}

							else
							{
								temp->deleteData();
								//Get the proper data from the id in the file.
								temp->getComponent(properties.at(y).at(x)->addData(properties.at(y).at(x));
							}
						}
					}
					else //Link the property.
						temp->add(systemManager->getComponent(properties.at(y).at(x)));
				}
			}
		}
	}
}