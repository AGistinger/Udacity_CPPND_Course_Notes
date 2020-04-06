// CPP_Concurrency_Function_objects

/*
There are three ways of forcing the compiler to consider the line as the 
-a variable definition for variable t of class std::thread, initialized with an anonymous instance of class Vehicle
	* Add an extra pair of parentheses
	* Use copy initialization
	* Use uniform initialization with braces
*/

#include <iostream>
#include <thread>

using namespace std;

class Vehicle
{
public:
	Vehicle(int id)
		: _id{id} {};

	void operator()()
	{
		cout << "Vehicle object has been created\n";
	}

private:
	int _id;
};

int main()
{
    //Starting Threads with Function Objects
	cout << "\n---Starting Threads with Function Objects------------------------" << endl;

	//Create a thread
	std::thread t1((Vehicle(1)));  //Add an extra pair of parantheses
	std::thread t2 = std::thread(Vehicle(2));  //Use copy initialization
	std::thread t3 {Vehicle(3)}; //Use uniform initialization with braces

	//Do something in main
	std::cout << "Finished work in main\n";

	//Wait for thread to finish
	t1.join();
	t2.join();
	t3.join();

	//Lambdas
	cout << "\n---Lambdas---------------------------------" << endl;

	//Create lambdas
	int id = 0;

	//auto f0 = [] () { cout << "ID = " << id << endl; }  //Error: 'id' cannot be accessed

	id++;
	auto f1 = [id] () { cout << "ID = " << id << endl; };  //OK, 'id' is captured by value

	id++;
	auto f2 = [&id] () { cout << "ID = " << id << endl; };

	//auto f3 = [id] () { cout << "ID = " << ++id << endl; };  //Error: 'id' will not be modified

	auto f4 = [id] () mutable { cout << "ID = " << ++id << endl; };  //OK, 'id' may be modified by mutable

	//Execute lambdas
	f1();
	f2();
	f4();

	//Staring Threads with Lambdas
	cout << "\n---Starting Threads with Lambdas-----------------" << endl;

	//Define an integer variable
	int num = 0;

	//Starting a first thread (by reference)
	auto func0 = [&num]()
	{
		this_thread::sleep_for(chrono::milliseconds(100));
		cout << "a) ID in Thread (call-by-reference) = " << num << endl;
	};
	std::thread thread1(func0);

	//Starting a second thread (by value)
	std::thread thread2([num]() mutable
		{
			this_thread::sleep_for(chrono::milliseconds(50));
			cout << "b) ID in Thread (call-by-value) = " << num << endl;
		});

	//Increment and print id in main
	++num;
	cout << "c) ID in Main (call-by-value) = " << num << endl;

	//Wait for threads before returning
	thread1.join();
	thread2.join();

	return 0;
}
