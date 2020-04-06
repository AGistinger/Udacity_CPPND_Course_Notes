// CPP_Concurrency

/*
#include <thread>
to use threads

functions:
this_thread::get_id() //will return the thread ID of the current thread
std::thread t(threadFunction);  //create a thread
this_thread::sleep_for(std::chrono::milliseconds(50));  // sleep thread for a specific period of time
t.join();  //wait for thread to finish
thread::hardware_concurrency();  //displays the # of available cores
detatch();  //does not wait for a thrad to finish, joinable is set to false, cannot be used again
*/

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void thread_function()
{
	this_thread::sleep_for(chrono::milliseconds(100)); //sleep this thread for 100 milliseconds
	cout << "Finished work in thread" << endl;
}

void thread_function_2()
{
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "Finished work 1 in thread\n";

	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "Finisehd work 2 in thread\n";
}

int main()
{
	//Starting Threads
	cout << "\n---Starting Threads------------------------------------------------------------------------" << endl;
	//Display the thread ID of the current thread
	cout << "Hello concurrent world from main! Thread id = " << this_thread::get_id() << endl;

	//Display the number of available CPU cores of a system
	unsigned int nCores = thread::hardware_concurrency();
	cout << "This machine supports concurrency with " << nCores << " cores available" << endl;

	//Create thread
	std::thread t(thread_function);

	//Do something in main()
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "Finished work in main" << endl;

	//Wait for thread to finish
	t.join();

	//Randomness of Events
	cout << "\n---Randomness of Events-----------------------------------------------------------------------" << endl;
	//Create thread
	std::thread t_2(thread_function_2);

	//Do something in main()
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "Finished work 1 in main\n";

	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "Finished work 2 in main\n";

	//Wait for thread to finish
	t_2.join();

	//Using Join as a Barrier
	cout << "\n---Using Join() as a Barrier--------------------------------------------------------------------" << endl;
	//Create thread
	std::thread t_3(thread_function_2);

	//Wait for thread to finish
	t_3.join();

	//Do something in main()
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "Finished work 1 in main\n";

	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "Finished work 2 in main\n";

	//Detach a thread
	cout << "\n--Detatching a Thread--------------------------------------------------------------------" << endl;

	//Create thread
	std::thread t_4(thread_function_2);

	//Detatch thread and continue with main
	t_4.detach();

	//Do something in main()
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "Finished work in main\n";

	return 0;
}

