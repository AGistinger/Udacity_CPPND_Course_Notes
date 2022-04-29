// STLMaps

/*
Maps
-Allows you to save Key/Value pairs
-Has methods to get the first(key) and second(value) elements  from the map pair
-When using iterators to access the first and second methods you have to use the -> operator
-The Key must be unique, there cannot be any duplicates
-You will often want to use a custom class as the value
-You will not often use a custom class as the key in the map
*/

#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

//Function Prototypes
void display_menu();
char select_option();
void add_element(map<string, int> &m);
void search_map(map<string, int> &m);
void display_map(const map<string, int> &m);
int create_pop(string &s);

//Display Menu
void display_menu()
{
	cout << "\n======Menu======" << endl;
	cout << "A - Add new Value" << endl;
	cout << "D - Display map" << endl;
	cout << "S - Search map" << endl;
	cout << "Q - Quit" << endl;
}

//Select Option
char select_option()
{
	char selection {};
	cout << "Enter your selection: ";
	cin >> selection;
	return toupper(selection);
}

//Add/Update new key/value pair
void add_element(map<string,int> &m)
{
	string country_name {};
	string temp_pop {};
	cin.ignore();

	cout << "Enter the Country name you would like to add: " << endl;
	getline(cin, country_name);
	cout << "Enter the population for the Country: " << endl;
	getline(cin, temp_pop);

	int population = create_pop(temp_pop);
	m[country_name] = population;
}

//Create Population
int create_pop(string &s)
{
	stringstream ss {s};
	int population {};
	if(ss >> population)
	{
		return population;
	}
	else
	{
		return 0;
	}
}

//Display all elements in the map
void display_map(const map < string,int> &m)
{
	if(!m.empty())
	{
		cout << "\nCountry Information:" << endl;
		for(const pair<string,int> &element : m)
		{
			cout << "[" << element.first << ": " << element.second << "]" << endl;
		}
	}
	else
	{
		cout << "Map is Empty" << endl;
	}
}

//Search map
void search_map(map<string,int> &m)
{
	cin.ignore();
	string name {};
	cout << "\nEnter a Country name to search for: ";
	getline(cin, name);
	map<string, int>::iterator it = m.find(name);

	if(it != m.end())
	{
		cout << "\nFound:" << endl;
		cout << "[" << it->first << ": " << it->second << "]" << endl;
	}
	else
	{
		cout << "\n" << name << " not found" << endl;
	}

}

int main()
{
	//Creating a Map that has a string for the Key and an int for the Value
	map<string, int> ages {};

	//Add elements to the map
	ages["Mike"] = 40;  //adds Key/Value pair to the map
	ages["Raj"] = 20;
	ages["Vicky"] = 30;
	pair<string, int> add_map("Peter", 100);
	ages.insert(add_map);
	ages.insert(pair<string, int>("Alex", 22));
	ages.insert(make_pair("Jessica", 30));

	//Change Value of pair
	ages["Mike"] = 70;  //age is now 70

	//Retrieve elements from the map
	cout << ages["Raj"] << endl;  //20

	//Test if an element is in a map
	if(ages.find("Vicky1") != ages.end())  //Will not add Vicky1 to the Map
	{
		cout << "Found Vicky" << endl;
	}
	else
	{
		cout << "Key not found" << endl;
	}

	//Iterate through a map
	map<string, int>::iterator it = ages.begin();
	for(it; it != ages.end(); it++)
	{
		cout << it->first << ": " << it->second << endl;   //Iterator accessing the first(key) and second(value) elements
	}
	cout << endl;

	it = ages.begin();
	for(it; it != ages.end(); it++)
	{
		pair<string, int> age = *it;  //Creates a pair from what the Iterator is pointing to
		cout << age.first << ": " << age.second << endl;
	}

	//Create a menu that uses maps to insert and add
	map<string, int> country_data {};
	char selection {};

	while(selection != 'Q')
	{
		display_menu();
		selection = select_option();
		switch(selection)
		{
			case 'A' : {add_element(country_data);}
				break;
			case 'D' : {display_map(country_data);}
				break;
			case 'S' : {search_map(country_data);}
				break;
			case 'Q' : {cout << "Closing Program..." << endl;}
				break;
			default : {cout << "Invalid Selection" << endl;}
		}
	}

	cout << endl;
    return 0;
}