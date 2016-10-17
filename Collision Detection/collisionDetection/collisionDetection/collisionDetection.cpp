// collisionDetection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>


//Helper functions.
void initData(std::string &, std::string, std::vector<std::string> &, std::vector<std::string> &);
void print(std::string, std::vector<std::string>);
void print(std::string, std::string);

void initData(std::string &, std::string, std::vector<double> &, std::vector<double> &);
void print(std::string, std::vector<double>);
void print(std::string, double);


//Function being tested.
void checkables(std::string, std::vector<std::string>, std::vector<std::string> &);
void storeAndSort(double, double, std::string, std::vector<double> &, std::vector<std::string> &);


int _tmain(int argc, _TCHAR* argv[])
{
	std::string keyword;
	std::vector<std::string> idX, idY, rawIdX, rawIdY, finalX, finalY;
	std::vector<double> dataX, dataY, posX, posY;

	initData(keyword, "ids.txt", rawIdX, rawIdY);
	initData(keyword, "data.txt", dataX, dataY);
	initData(keyword, "finalIds.txt", finalX, finalY);

	//print("RawIdX", rawIdX);
	//print("RawIdY", rawIdY);
	//print("DataX", dataX);
	//print("DataY", dataY);

	int increment = 0;
	for (int i = 0; i < dataX.size() - 1; i+=2)
	{
		//Insert into proper locations
		storeAndSort(dataX.at(i), dataX.at(i + 1), rawIdX.at(increment), posX, idX);
		increment++;
	}

	increment = 0;
	for (int i = 0; i < dataY.size() - 1; i += 2)
	{
		//Insert into proper locations
		storeAndSort(dataY.at(i), dataY.at(i + 1), rawIdY.at(increment), posX, idY);
		increment++;
	}

	std::cout << "Testing idX." << std::endl;
	for (int i = 0; i < idX.size(); i++)
	{
		if (idX.at(i) == finalX.at(i))
		{
			std::cout << "Success at " << i << std::endl;
		}
	}

	std::cout << "\nTesting idY." << std::endl;
	for (int i = 0; i < idY.size(); i++)
	{
		if (idY.at(i) == finalY.at(i))
		{
			std::cout << "Success at " << i << std::endl;
		}
	}

	std::cout << "\n" << std::endl;

	print("finalX", finalX);
	print("finalY", finalY);
	print("idX", idX);
	print("idY", idY);
	/*
	//Begin testing.
	//Check ids.
	std::vector<std::string> checkTheseIdsX, checkTheseIdsY;
	checkables(keyword, idX, checkTheseIdsX);
	checkables(keyword, idY, checkTheseIdsY);

	print("checkTheseIdsX", checkTheseIdsX);
	print("checkTheseIdsY", checkTheseIdsY);

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
								std::cout << "EXPLODE " + finalCheckX.at(i) << std::endl;
								/*
								sf::Vector2f position;
								Entity *currentMissile = systemManager->getMaterial(finalCheckX.at(i));
								position.x = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0);
								position.y = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(1);
								temp = systemManager->getMaterial(explosionId);

								//Check for collision.
								if (intersection(temp->getComponent("CircleShape")->getDataCircleShape().at(0), position))
								{
									//Set proper flags.
									//No missileExploder call because that is handled in the missileLaunchers.
									//Explode
									currentMissile->getComponent("Explode")->deleteData();
									currentMissile->getComponent("Explode")->addData(true);

									//Update Explosion Position
									currentMissile->getComponent("ExplodingPosition")->deleteData();
									currentMissile->getComponent("ExplodingPosition")->addData(position.x);
									currentMissile->getComponent("ExplodingPosition")->addData(position.y);

									//Kept for knowing wheter to add points.
									currentMissile->getComponent("ShotDown")->deleteData();
									currentMissile->getComponent("ShotDown")->addData(true);
								}
							}
						}
					}
					
					//print("finalCheckX", finalCheckX);
					//print("finalCheckY", finalCheckY);
				}
			}
		}
	}
	*/
	system("pause");
	return 0;
}


//Tested function.
void checkables(std::string keyword, std::vector<std::string> list, std::vector<std::string> & checkTheseIds)
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


void storeAndSort(double small, double large, std::string id, std::vector<double> & pos, std::vector<std::string> & ids)
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

//Helpers.
void initData(std::string & keyword, std::string data, std::vector<std::string> & idX, std::vector<std::string> & idY)
{
	char file;
	std::cout << "ID DATA\nLoad from file: ";
	std::cin >> file;
	if (toupper(file) == 'Y')
	{
		std::ifstream in;
		in.open(data);
		if (in.is_open())
		{
			while (!in.eof())
			{
				std::string temp;
				in >> temp;
				if (temp.find("keyword") != std::string::npos)
				{
					in >> temp;
					keyword = temp;
				}
				if (temp.find("idX") != std::string::npos)
				{
					in >> temp;
					while (temp.find("idY") == std::string::npos && !in.eof())
					{
						idX.push_back(temp);
						in >> temp;
					}
				}
				if (temp.find("idY") != std::string::npos)
				{
					in >> temp;
					while (temp.find("idX") == std::string::npos && !in.eof())
					{
						idY.push_back(temp);
						in >> temp;
					}
				}
			}
		}
		in.close();
	}
	else
	{
		std::cout << "Enter in a keyword: ";
		std::cin >> keyword;

		int x = 0;

		std::cout << "\n\nHow many idsX?: ";
		std::cin >> x;
		for (int i = x; i > 0; i--)
		{
			std::string temp;
			std::cout << "You have " + std::to_string(i) + " ids left.\nEnter in id: ";
			std::cin >> temp;
			idX.push_back(temp);
		}

		int y = 0;
		std::cout << "\n\nHow many idsY?: ";
		std::cin >> y;
		for (int i = y; i > 0; i--)
		{
			std::string temp;
			std::cout << "You have " + std::to_string(i) + " ids left.\nEnter in id: ";
			std::cin >> temp;
			idY.push_back(temp);
		}

		std::cout << "Save to file?: ";
		std::cin >> file;
		if (toupper(file) == 'Y')
		{
			std::ofstream output;
			output.open(data, std::ios::trunc);
			if (output.is_open())
			{
				output << "keyword: " << keyword << std::endl << std::endl;
				output << "idX: " << std::endl;
				for (int i = 0; i < idX.size(); i++)
				{
					output << idX.at(i) << std::endl;
				}
				output << std::endl;
				output << "idY: " << std::endl;
				for (int i = 0; i < idY.size(); i++)
				{
					output << idY.at(i) << std::endl;
				}
			}
			output.close();
		}
	}

	std::cout << std::endl << std::endl;
	system("cls");
}

//Helpers.
void initData(std::string & keyword, std::string data, std::vector<double> & idX, std::vector<double> & idY)
{
	char file;
	std::cout << "DOUBLE DATA\nLoad from file: ";
	std::cin >> file;
	if (toupper(file) == 'Y')
	{
		std::ifstream in;
		in.open(data);
		if (in.is_open())
		{
			while (!in.eof())
			{
				std::string temp;
				in >> temp;
				if (temp.find("dataX") != std::string::npos)
				{
					in >> temp;
					while (temp.find("dataY") == std::string::npos && !in.eof())
					{
						idX.push_back(std::stod(temp));
						in >> temp;
					}
				}
				if (temp.find("dataY") != std::string::npos)
				{
					in >> temp;
					while (temp.find("dataX") == std::string::npos && !in.eof())
					{
						idY.push_back(std::stod(temp));
						in >> temp;
					}
				}
			}
		}
		in.close();
	}
	else
	{
		int x = 0;

		std::cout << "How much dataX?: ";
		std::cin >> x;
		for (int i = x; i > 0; i--)
		{
			std::string temp;
			std::cout << "You have " + std::to_string(i) + " entries left.\nEnter in id: ";
			std::cin >> temp;
			idX.push_back(std::stod(temp));
		}

		int y = 0;
		std::cout << "\n\nHow much dataY?: ";
		std::cin >> y;
		for (int i = y; i > 0; i--)
		{
			std::string temp;
			std::cout << "You have " + std::to_string(i) + " entries left.\nEnter in id: ";
			std::cin >> temp;
			idY.push_back(std::stod(temp));
		}

		std::cout << "Save to file?: ";
		std::cin >> file;
		if (toupper(file) == 'Y')
		{
			std::ofstream output;
			output.open(data, std::ios::trunc);
			if (output.is_open())
			{
				output << "dataX: " << std::endl;
				for (int i = 0; i < idX.size(); i++)
				{
					output << idX.at(i) << std::endl;
				}
				output << std::endl;
				output << "dataY: " << std::endl;
				for (int i = 0; i < idY.size(); i++)
				{
					output << idY.at(i) << std::endl;
				}
			}
			output.close();
		}
	}

	std::cout << std::endl << std::endl;
	system("cls");
}


//Helpers.
void print(std::string name, std::vector<std::string> id)
{
	std::cout << name << ": " << std::endl;
	for (int i = 0; i < id.size(); i++)
	{
		std::cout << "At " + std::to_string(i) + ": " + id.at(i) << std::endl;
	}
	std::cout << std::endl << std::endl;
}


//Helpers.
void print(std::string name, std::string id)
{
	std::cout << name << ": " << std::endl;
	std::cout << id << std::endl << std::endl;
}


//Helpers.
void print(std::string name, std::vector<double> id)
{
	std::cout << name << ": " << std::endl;
	for (int i = 0; i < id.size(); i++)
	{
		std::cout << "At " + std::to_string(i) + ": " << id.at(i) << std::endl;
	}
	std::cout << std::endl << std::endl;
}


//Helpers.
void print(std::string name, double id)
{
	std::cout << name << ": " << std::endl;
	std::cout << id << std::endl << std::endl;
}