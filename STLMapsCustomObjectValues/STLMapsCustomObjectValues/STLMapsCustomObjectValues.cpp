// STLMapsCustomObjectValues

/*
-In order to create objects for use in maps as value you have to supply a default constructor
-Map will always sort the objects in order by its keys
*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

//Class for Person
class Person
{
private:
	string name;
	int age;

public:
	Person() = default;

	Person(string name, int age)
		: name{name}, age{age} {}

	//Copy Constructor
	Person(const Person &source)
		: name{source.name}, age{source.age}
	{
		cout << "Copy constructor running for: " << source.name << endl;
	}

	void print() const
	{
		cout << name << ": " << age << endl;
	}
};

int main()
{
	map<int, Person> people;

	people[0] = Person("Mike", 40);
	people[1] = Person("Vicky", 30);
	people[2] = Person("Raj", 20);
	people.insert(pair<int, Person>(3, Person("Jessica", 30)));
	people.insert(make_pair(55, Person("Gianna", 5)));

	map<int, Person>::iterator it = people.begin();
	for(it; it != people.end(); it++)
	{
		cout << it->first << ": ";
		it->second.print();
	}

    return 0;
}