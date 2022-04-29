// STLTwoDimentionalVectors

/*
Two-Dimentional Vectors
-Create a Vector with 2 or more dimentions]
-You create a vector of vectors and you can supply the inital size as arguments ex) vector<vector<int>> grid(3, vector<int>(4, 0));
*/

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

//Display  using range based for loop
void display(const vector<vector<int>> &vec)
{
	cout << "\n============[ Multiplication Table ]===============" << endl;
	for (const vector<int> &row : vec)
	{
		for (const int& col : row)
		{
			cout << setw(3) << left << col << " ";
		}
		cout << endl;
	}
}

int main()
{
	//Creates a vector with 3 vectors of 4 ints set to 0
	vector<vector<int>> grid(3, vector<int>(4, 0));

	//push_back() items to 2D Vector
	grid.at(1).push_back(8);  //.at() method
	grid[1].push_back(10);  //[] subscript operator

	//Displaying Grid 2D vector
	for (int row{ 0 }; row < grid.size(); row++)
	{
		for (int col{ 0 }; col < grid.at(row).size(); col++)
		{
			cout << grid.at(row).at(col) << flush;  //or grid[row][col]
		}
		cout << endl;
	}

	//Create a 2D vector for a 12X Multiplication table
	const int size {12};
	vector<vector<int>> table{};

	for (int i{0}; i <= size; i++)
	{
		table.push_back(vector<int>{});
		for (int j{0}; j <= size; j++)
		{
			table[i].push_back(i * j);
		}
	}
	display(table);

    return 0;
}