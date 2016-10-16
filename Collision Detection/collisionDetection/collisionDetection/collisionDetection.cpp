// collisionDetection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>


//Helper functions.
void initData(std::string &, std::vector<std::string> &, std::vector<std::string> &);
void print(std::string, std::vector<std::string>);
void print(std::string, std::string);


//Function being tested.
void checkables(std::string, std::vector<std::string>, std::vector<std::string> &);


int _tmain(int argc, _TCHAR* argv[])
{
	std::string keyword;
	std::vector<std::string> idX, idY;

	initData(keyword, idX, idY);

	print("keyword", keyword);
	print("idX", idX);
	print("idY", idY);

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
					std::vector<std::string> finalCheckX;
					//Repeat while the other end is not found and we have not stepped out of bounds.
					while (!found && increment < checkTheseIdsX.size())
					{
						//If the other explosion limit is found.
						if (checkTheseIdsX.at(increment) == checkTheseIdsX.at(x))
						{
							found = true;
							//Update the x value from the for loop so that the same values are not rechecked.
							//x = increment;
						}
						else
						{
							//Push back the missile ids.
							if (checkTheseIdsX.at(increment).find(keyword) == std::string::npos)
								finalCheckX.push_back(checkTheseIdsX.at(increment));
							increment++;
						}
					}

					increment = y + 1;
					found = false;
					std::vector<std::string> finalCheckY;
					//Repeat while the other end is not found and we have not stepped out of bounds.
					while (!found && increment < checkTheseIdsY.size())
					{
						//If the other explosion limit is found.
						if (checkTheseIdsY.at(increment) == checkTheseIdsY.at(y))
						{
							found = true;
							//Update the y value from the for loop so that the same values are not rechecked.
							//y = increment;
						}
						else
						{
							//Push back the missile ids.
							if (checkTheseIdsY.at(increment).find(keyword) == std::string::npos)
								finalCheckY.push_back(checkTheseIdsY.at(increment));
							increment++;
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
							}
						}
					}

					print("finalCheckX", finalCheckX);
					print("finalCheckY", finalCheckY);
				}
			}
		}
	}

	system("pause");
	return 0;
}


//Tested function.
void checkables(std::string keyword, std::vector<std::string> list, std::vector<std::string> & checkTheseIds)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i).find(keyword) != std::string::npos)
		{
			bool foundEnd = false;
			int added = i + 1;
			bool intersects = false;

			checkTheseIds.push_back(list.at(i));

			while (!foundEnd && added < list.size())
			{
				if (list.at(added) == list.at(i))
				{
					foundEnd = true;
					checkTheseIds.push_back(list.at(added));
				}
				else
				{
					checkTheseIds.push_back(list.at(added));
				}
				added++;
			}
			i = added;
		}
	}
}



//Helpers.
void initData(std::string & keyword, std::vector<std::string> & idX, std::vector<std::string> & idY)
{
	char file;
	std::cout << "Load from file: ";
	std::cin >> file;
	if (toupper(file) == 'Y')
	{
		std::ifstream in;
		in.open("data.txt");
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
			output.open("data.txt", std::ios::trunc);
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