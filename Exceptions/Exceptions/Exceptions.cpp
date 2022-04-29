// Exceptions
/*
 Exceptions should only be used in error conditions that are really serious
 Used in conditions that your program cannot recover from.
 Example) if you are not able to allocate enough memory.
 You can throw anything as an exception including objects.
*/

#include <iostream>
#include <string>

using namespace std;

//Function Prototypes
void might_go_wrong();
void use_might_go_wrong();

void use_might_go_wrong()
{
	might_go_wrong();
}

void might_go_wrong()
{
	bool error1 = false;
	bool error2 = true;
	if (error1)
	{
		throw "Something went wrong";
	}

	if (error2)
	{
		throw string("Something else went wrong");  //creates a string object
	}
}

int main()
{
	//Try to execute what is in the try block
	try
	{ 
		might_go_wrong();
	}

	//Catch and handle the errors from the try block
	catch (int &err)
	{
		cerr << "Error code: " << e << endl;
	}

	catch (const char *err)
	{
		cerr << "Error message" << endl;
	}

	catch (string &err)
	{
		cerr << "String error message: " << e << endl;
	}

	cout << "Still running" << endl;

	return 0;
}

