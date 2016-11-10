/*
Authors: William Eiffert, Adam Sawyer, Zane Durante, Kendrick Austin
Date Begin: 3 February 2016
Last Edit: 22 September 2016
Purpose: This is a game engine designed to use entities and component based design.
The implementation of the engine will be missile command.
*/

//includes
#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <time.h>

#include "Game.h"

#include<stdlib.h>

int conversion(std::string);

int main()
{
	int exitCode = 0;
	//Log run
	std::ofstream file;
	file.open("log.txt", std::ios::app);

	if (file.is_open())
		file << "Program run at: " << time(NULL) << "\nExit Code: ";

	//Read from file.
	std::ifstream read;
	std::vector<std::string> data;

	read.open("game.txt", std::ios::app);
	
	if (read.is_open())
	{
		while (!read.eof())
		{
			std::string temp;
			read >> temp;
			data.push_back(temp);
		}
		read.close();

		//Convert the first two strings to ints.
		int one = conversion(data.at(0));
		int two = conversion(data.at(1));

		Game game(one, two, data.at(3));
		try
		{
			//run the game
			exitCode = game.run();
		}
		catch (std::bad_typeid error)
		{
			std::cout << error.what() << std::endl;
			std::cout << "Error code saved in game log" << std::endl;
			file << error.what();
			system("pause");
			file.close();
			return 0;
		}

		//log exit code
		if (file.is_open())
			file << exitCode;

	}

	else if (file.is_open())
	{
		file << "404. Could not open game.txt";
	}

	file << std::endl;

	//clean up
	file.close();
<<<<<<< HEAD

=======
	
>>>>>>> refs/remotes/origin/master
	return 0;
}


int conversion(std::string s)
{
	int temp = 0;

	//Repeat until the number has been extracted.
	for (int i = 0; i < s.length(); i++)
	{
		//Conversion from string to base 10.
		temp *= 10;
		temp += static_cast<int>(s.at(i) - 48);
	}

	return temp;
}