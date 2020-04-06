// CPP_Concurrency_Variadic_Template

/*
Variadic Template
-C++11, allow the definition of functions that take a variable amount of arguments

Member Functions
-Running member functions of already existing objects

References with threads
-When passing the string variable name to the thread function, we need to explicitly 
mark it as a reference, so the compiler will treat it as such. This can be done 
by using the std::ref function. In the console output it becomes clear that 
the string has been successfully modified within the thread function before being passed to main.
*/

#include <iostream>
#include <string>
#include <thread>
#include <memory>

using namespace std;

class Vehicle
{
public:
	Vehicle() : _id(0) {}
	void add_id(int id) {_id = id;}
	void print_id()
	{
		cout << "Vehicle ID = " << _id << endl;
	}

private:
	int _id;
};

void print_id(int id)
{
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "ID = " << id << endl;
}

void print_id_and_name(int id,string name)
{
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << "ID = " << id << ", Name = " << name << endl;
}

void print_name(string name,int wait_time)
{
	this_thread::sleep_for(chrono::milliseconds(wait_time));
	cout << "Name (from Thread) = " << name << endl;
}

void print_name_ref(string &name,int wait_time)
{
	this_thread::sleep_for(chrono::milliseconds(wait_time));
	name += " (from Thread)";
	cout << name << endl;
}

int main()
{
	//Example 1 Using Variadic Templates--------------------------------------
	int id = 0;  //Define an integer variable

	//Starting threads using variadic templates
	std::thread t1(print_id, id);
	std::thread t2(print_id_and_name, ++id, "MyString");

	//Wait for threads to finish before returning
	t1.join();
	t2.join();

	//Example 2 Using Variadic Templates with by value/move----------------------
	string name1 = "MyThread1";
	string name2 = "MyThread2";

	//Starting threads using value-copy and move semantics
	std::thread t3(print_name, name1, 50);  //by value
	std::thread t4(print_name, move(name2), 100);  //using move

	//Wait for threads before returning
	t3.join();
	t4.join();

	//print name from main
	cout << "Name (from Main) = " << name1 << endl;
	cout << "Name (from Main) = " << name2 << endl;

	//Example 3 Using Variadic Templates with references------------------------
	string name {"MyThread"};

	//Starting thread
	std::thread t(print_name_ref, std::ref(name), 50);

	//Wait for thread to join before returning
	t.join();

	//print name from main
	name += " (from Main)";
	cout << name << endl;

	//Example 4 Staring Threads with Member Functions----------------------------
	Vehicle v1, v2;

	//Create thread
	std::thread t5 = std::thread(&Vehicle::add_id, v1, 1);  //call member function on object v
	std::thread t6 = std::thread(&Vehicle::add_id, &v2, 2);  //call member function on object v

	//Wait for thread to finish
	t5.join();
	t6.join();

	//print vehicle id
	v1.print_id();
	v2.print_id();

	//Example 5 Making sure object outlives the completion of the thread----------------
	shared_ptr<Vehicle> v = make_shared<Vehicle>();

	//Create thread
	std::thread t7 = std::thread(&Vehicle::add_id, v, 1);  //Call member function on object v

	//Wait for thread to finish
	t7.join();

	//Print vehicle id
	v->print_id();
	
    return 0;
}
