// StructsAndPadding

/*
Structs and Padding
-Structs are like classes but all their members are public by default
-Structs are commonly used to writing to files, you can map bytes to 1 or more structs
-When you declare variables in C++ they are stored in an area of memory known as the stack
-The String class uses a pointer with (new) to allocate memory on the heap, so if you write a string to a binary file
 you will not write the text, but the pointer to that text.
-C++ pads structs, to write to binary files you need to turn off padding.
-To do this you can use a preproccessor directive (#pragma pack(push, 1))
-The 1 tells the program to align this data on single byte boundaries, (removes padding)
-If you want to undo this directive so it does not affect everything that you type after it you can type
 #pragma pack(pop)
*/

#include <iostream>

using namespace std;

#pragma pack(push, 1) //removes extra struct padding
struct Person
{
public:
	char name[50]; //Creating a character array of 50 characters max
	int age;
	double weight;
};
#pragma pack(pop)

int main()
{
	cout << sizeof(Person) << " bytes" << endl; //64 bytes

    return 0;
}