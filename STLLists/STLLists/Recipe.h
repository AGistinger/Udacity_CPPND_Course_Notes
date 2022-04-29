#ifndef _RECIPE_H_
#define _RECIPE_H_

#include <string>
#include <vector>

using namespace std;

//Struct to store data
struct Recipe
{
	string name;
	vector<string> ingredients;

	Recipe()
		: name{ "Unknown" }, ingredients{ "None" }
	{}

	Recipe(string& name, vector<string>& ingredients)
		: name{ name }, ingredients{ ingredients }
	{}

	bool operator<(const Recipe& rhs) const
	{
		return this->name < rhs.name;
	}

	bool operator==(const Recipe& rhs) const
	{
		return this->name == rhs.name;
	}
};

#endif