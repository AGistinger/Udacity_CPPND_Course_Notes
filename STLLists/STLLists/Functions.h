#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include "Recipe.h"
#include <iostream>

using namespace std;

//Function Prototypes
ostream& operator<<(ostream &out, const Recipe &r);
void display(const list<Recipe> &l, list<Recipe>::iterator &it);
void menu();
char select_option();
void add_recipe(list<Recipe> &l, list<Recipe>::iterator &it);
vector<string> create_ingredients(string& ingr);
void display_list(const list<Recipe> &l);
void next_recipe(list<Recipe> &l, list<Recipe>::iterator &it);
void previous_recipe(list<Recipe> &l, list<Recipe>::iterator &it);
void save_recipe(Recipe &r);
void load_recipe(list<Recipe> &l);
Recipe get_recipe(ifstream &load);

//Overloaded << operator
ostream& operator<<(ostream &out, const Recipe &r)
{
	out << r.name;
	return out;
}

//Display the Recipe name and ingredients
void display(const list<Recipe> &l, list<Recipe>::iterator &it)
{
	if(!l.empty())
	{ 
		cout << "\nRecipe: " << endl;
		cout << " " << it->name << endl;
		cout << "Ingredients:" << endl;
		for (const string &element : it->ingredients)
		{
			cout << " " << element << endl;
		}
		cout << endl;
	}
	else
	{
		cout << "Unable to display recipe, List is empty" << endl;
	}
}

//Menu
void menu()
{
	cout << "\n==========Menu============== " << endl;
	cout << "A - Add Recipe" << endl;
	cout << "R - Remove Recipe" << endl;
	cout << "N - Next Recipe" << endl;
	cout << "P - Previous Recipe" << endl;
	cout << "D - Display List of Recipes" << endl;
	cout << "S - Show Recipe Details" << endl;
	cout << "Q - Quit" << endl;
}

//Selection
char select_option()
{
	char selection{};
	cout << "Enter your selection: ";
	cin >> selection;
	return toupper(selection);
}

//Add Recipe
void add_recipe(list<Recipe> &l, list<Recipe>::iterator &it)
{
	string name{};
	string temp_ingr;
	cin.ignore();

	cout << "Enter the name of your recipe: " << endl;
	getline(cin, name);

	cout << "Enter your ingredients (separated by spaces):" << endl;
	getline(cin, temp_ingr);
	vector<string> ingredients = create_ingredients(temp_ingr);

	l.insert(it, Recipe(name, ingredients));
	it--;
	save_recipe(*it);
	display(l, it);
}

//Create Vector from string
vector<string> create_ingredients(string &ingr)
{
	stringstream ss{ingr};
	string ingr_name {};
	vector<string> ingredients{};
	while (ss >> ingr_name)
	{
		ingredients.emplace_back(ingr_name);
	}
	return ingredients;
}

//Remove Recipe
void remove_recipe(list<Recipe> &l, list<Recipe>::iterator &it)
{
	if (!l.empty())
	{
		it = l.erase(it);
		if (it == l.end())
		{
			it = l.begin();
		}
	}
	else
	{
		cout << "\nNothing to delete" << endl;
	}
}

//Next Recipe
void next_recipe(list<Recipe> &l, list<Recipe>::iterator &it)
{
	if (*it == l.back())
	{
		it = l.begin();
	}
	else
	{
		it++;
	}
	display(l, it);
}


//Previous Recipe
void previous_recipe(list<Recipe> &l, list<Recipe>::iterator &it)
{
	if (*it == l.front())
	{
		it = l.end();
		it--;
	}
	else
	{
		it--;
	}
	display(l, it);
}

//Display List
void display_list(const list<Recipe>& l)
{
	if(!l.empty())
	{
		cout << "=======Recipes======" << endl;
		for (const Recipe& element : l)
		{
			cout << element << endl;
		}
	}
	else
	{
		cout << "Unable to display list, list is empty" << endl;
	}
}

//Save File
void save_recipe(Recipe &r)
{
	ofstream save_file{"recipe.txt", ios::app};
	if(save_file.is_open())
	{
		save_file << "\n" << r.name << endl;
		for(string &element : r.ingredients)
		{
			save_file << element << " ";
		}
		save_file.close();
	}
	else
	{
		cout << "File did not open properly" << endl;
	}
}

//Load File
void load_recipe(list<Recipe> &l)
{
	ifstream load {"recipe.txt"};
	if(load.is_open())
	{
		while(!load.eof())
		{
			l.emplace_back(get_recipe(load));
		}
		load.close();
	}
	else
	{
		cout << "File did not open properly" << endl;
	}
}

//Get Recipe From File
Recipe get_recipe(ifstream &load)
{
	string name;
	string temp_ingr;

	getline(load, name);
	getline(load, temp_ingr);
	vector<string> ingredients = create_ingredients(temp_ingr);

	return Recipe(name, ingredients);
}

#endif