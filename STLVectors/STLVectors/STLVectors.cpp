// STLVectors

/*
STL Vectors
-A Vector is a resizable array
-A Vector is a template class and you have to tell it what type of object you want
-Vectors automatically manage memory for you
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Global Template Function to Display Elements in Vectors
template <typename T>
void display(const vector<T>& vec)
{
	cout << "[ ";
	for (const T &element : vec)
	{
		cout << element << " ";
	}
	cout << " ]" << endl;
}

int main()
{
	//You can pre-size the vector by putting the size in () parantheses
	//If you pre-size a vector you do not want to use the subscript or .at() methods to add
	//an element past the length of the vector ex) strings[10], behavior is undefined
	vector<string> strings(5);

	//You can set the elements using the subscript operator []
	strings[3] = "Dog";
	strings[2] = "Cat";
	strings[1] = "Bird";
	strings[4] = "Iguana";
	cout << strings[3] << endl;
	cout << strings[1] << endl;

	//You can add more objects to vectors using .push_back() method
	strings.push_back("One");
	strings.push_back("Two");
	strings.push_back("Three");

	//You can find the size of the vector by using the .size() method
	cout << strings.size() << endl;

	//Display All Elements in the Vector
	//You can display in multiple methods:
	//for(int i{0}; i < strings.size(); i++) <-Older method
	//vector<string>::iterator it = strings.begin();  <-Creates an iterator to the first element in the vector
	//You can dereference iterators like a pointer by using *it, .end() points to the element 1 past the last element in the vector
	//for(vector<string>::iterator it = strings.begin(); it != strings.end(); it++); <-Using an iterator to loop through vector
	//Iterators can be used to navigate through vectors by using it++ or it--
	display(strings);

	//Create a vector and put elements in it and iterate with it using multiple methods
	vector<int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	display(numbers);

	for (size_t i{ 0 }; i < numbers.size(); i++)
	{
		cout << numbers.at(i) << " ";
	}
	cout << endl;

	vector<int>::iterator num_it = numbers.begin();
	for (num_it; num_it != numbers.end(); num_it++)
	{
		cout << *num_it << " ";
	}
	cout << endl;


    return 0;
}