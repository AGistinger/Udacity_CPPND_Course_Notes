// STLVectorsAndMemory

/*
Vectors and Memory
-If you are looping through a vector you can use a const iterator to ensure that the contents inside the iterator
 cannot be changed. ex) vector<int>::const_iterator it = vec.begin();
-A Vector manages a array internally, if you add more elements to the vector it will create another array and copy elements
 to it.
-Vectors have a method called capacity(), this is the size of the interal array that the vector is using exponentially
-vector.size() shows the actual number of elements inside the vector
*/

#include <iostream>
#include <vector>

using namespace std;

//Global Template Display Function for Vectors
template <typename T>
void display(const vector<T>& vec)
{
	cout << "[ ";
	for (const T &elem : vec)
	{
		cout << elem << " ";
	}
	cout << "]" << endl;
}

int main()
{
	vector<double> numbers(20, 0);
	cout << "Size: " << numbers.size() << endl;

	int capacity = numbers.capacity();
	cout << "Capacity: " << capacity << endl;

	for (int i{ 0 }; i < 10000; i++)
	{
		if (numbers.capacity() != capacity)
		{
			capacity = numbers.capacity(); //Shows that the vectors capacity is increasing exponentially
			cout << "Capacity: " << capacity << endl;
		}
		numbers.push_back(i);
	}
	display(numbers);

	numbers.reserve(10000); //changes the capacity of the vector if the new capacity is greater than current, doesn't affect size
	cout << "Size: " << numbers.size() << endl; //number of elements in the vector
	cout << "Capacity: " << numbers.capacity() << endl; //current number of elements the vector can hold
	numbers.clear();  //removes all the elements in the vector

    return 0;
}