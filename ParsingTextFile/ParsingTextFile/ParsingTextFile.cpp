// ParsingTextFile

/*
Parsing Text Data
Getting multiple different types of different information from a file
C++ is not ideal for parsing text
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	ifstream input;
	string file_name {"stats.txt"};
	input.open(file_name);

	if (!input.is_open())
	{
		return 1;
	}

	string line{};
	while (!input.eof())
	{
		int population{};
		string temp_pop{};
		getline(input, line, ':');
		getline(input, temp_pop, '\n');
		istringstream iss{temp_pop};

		//validate entry
		if (iss >> population)
		{
			cout << line << " -- " << population << endl;
		}
		else
		{
			cout << "Population input not a valid integer" << endl;
		}

		//input.get(); //get extra \n char and throw it out
		//input >> ws;  //check for whitespace and remove it
	}
	input.close();

    return 0;
}