// ExceptionsCustom

/*
Creating custom derived exceptions classes from the default public exception class
You need to override the what method from the exception class for your own class
*/

#include <iostream>
#include <exception>

using namespace std;

class My_Exception : public exception
{
public:
	//This method cannot throw an exception, const throw will cause your program to halt at runtime
	virtual const char *what() const throw()
	{
		return "Soemthing bad happened!";
	}
};

class Broken : public exception
{
public:
	virtual const char *what() const throw()
	{
		return "I am returning an exception";
	}
};

struct Test
{
	void goes_wrong()
	{
		throw My_Exception();
	}
};

struct Test_Two
{
	void goes_wrong()
	{
		throw Broken();
	}
};

int main()
{

	Test test;
	Test_Two test_var;

	try
	{
		test.goes_wrong();
	}

	catch (const My_Exception &err)
	{
		cout << err.what() << endl;
	}

	try
	{
		test_var.goes_wrong();
	}

	catch (const Broken & err)
	{
		cout << err.what() << endl;
	}
    
	return 0;
}
