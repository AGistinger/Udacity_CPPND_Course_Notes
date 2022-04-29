// STLLists

/*
STL - Lists
-Lists allow insertion of items anywhere, where vectors only allow adding items at the back of the vector (index)
-Lists contain a bunch of nodes which store each element
-The Nodes are linked to each other by pointers
-The Nodes/Elements have a pointer to the previous node/element and the next node/element
-This is a double-linked list
-You cannot use the index .at or []
-You cannot use += with iterators, you can only use (++) and (--)
*/

#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Recipe.h"
#include "Functions.h"

using namespace std;

int main()
{
	//Creating a list of ints
	list<int> numbers {};

	//Can use the .push_back() method
	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	//Can use the .push_front() method
	numbers.push_front(4);
	numbers.push_front(5);
	numbers.push_front(6);

	//Adding elements from various positions in the list
	list<int>::iterator modify_it = numbers.begin();
	modify_it++;
	numbers.insert(modify_it, 100); //inserts new element before the iterator
	cout << "Element: " << *modify_it << endl;  //Iterator that points to an element in the list

	//Erasing elements from positions in the list
	modify_it = find(numbers.begin(), numbers.end(), 100);
	cout << "Element: " << *modify_it << endl;
	modify_it = numbers.erase(modify_it); //Changes iterator to next element so it doesn't become invalid
	cout << "Element: " << *modify_it << endl;

	//Loooping for inserting and deleting
	modify_it = numbers.begin(); //Changing iterator back to start
	for (modify_it; modify_it != numbers.end(); modify_it++)
	{
		if (*modify_it == 2)
		{
			numbers.insert(modify_it, 1234);
		}
		if (*modify_it == 1)
		{
			modify_it = numbers.erase(modify_it);
		}
	}

	//Using an Iterator to navigate a list
	list<int>::iterator it = numbers.begin();
	for (it; it != numbers.end(); it++)
	{
		cout << *it << endl;
	}

	//Use a while loop to modify elements in the list, write a program that presents a menu, 
	//allows you to add or remove items from the list.  Use files to save/remove items from the list
	list<Recipe> recipes {};
	load_recipe(recipes);
	list<Recipe>::iterator location = recipes.begin();
	char selection {};

	while (selection != 'Q')
	{
		menu();
		selection = select_option();

		if (selection == 'A')
		{
			add_recipe(recipes, location);
		}
		else if (selection == 'R')
		{
			remove_recipe(recipes, location);
		}
		else if (selection == 'N')
		{
			next_recipe(recipes, location);
		}
		else if (selection == 'P')
		{
			previous_recipe(recipes, location);
		}
		else if (selection == 'D')
		{
			display_list(recipes);
		}
		else if (selection == 'S')
		{
			display(recipes, location);
		}
		else
		{
			cout << "Invalid Selection" << endl;
		}
	}
	
    return 0;
}