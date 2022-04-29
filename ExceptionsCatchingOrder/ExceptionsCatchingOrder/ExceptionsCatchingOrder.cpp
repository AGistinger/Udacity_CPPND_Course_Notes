// ExceptionsCatchingOrder

/*
Catching Exceptions in the right order
You must catch exceptions with the child classes before the parent classes, or polymorphism will not
allow the child class catch blocks to execute.
*/

#include <iostream>
#include <exception>

using namespace std;

void goes_wrong()
{
	bool error1_detected = true;
	bool error2_detected = false;

		if (error1_detected)
		{
			throw bad_alloc();  //child of exception class
		}

		if (error2_detected)
		{
			throw exception();
		}
}

int main()
{
	try
	{
		goes_wrong();
	}

	//bad_alloc (child of exception)
	catch (const bad_alloc & err)
	{
		cout << "Catching bad_alloc: " << err.what() << endl;
	}

	//exception (parent class)
	catch (const exception &err)
	{
		cout << "Catching exception: " << err.what() << endl;
	}

	return 0;
}