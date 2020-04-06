// CPP_Concurrency_Running_Multiple_Threads

/*
Fork-Join Parallelism
	-Split the flow of execution into a parallel thread ("fork")
	-Perform some work in both the main thread and the parallel thread
	-Wait for the parallel thread to finish and unite the split flow of execution again ("join")
*/

#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void print_hello()
{
	//perform work
	cout << "Hello from Worker thread # " << this_thread::get_id() << endl;
}

int main()
{
	//Example 1 - Multiple Threads--------------------------------------------------
	//Create threads
	vector<std::thread> threads;
	for(size_t i{0}; i < 5; i++)
	{
		//Copying thread objects causes a compile error (cannot copy threads)
		/*
		std::thread t(print_hello);
		threads.push_back(t);
		*/

		//Moving thread objects will work
		threads.emplace_back(std::thread(print_hello));
	}

	//Do something in main()
	cout << "Hello from Main thread # " << this_thread::get_id() << endl;

	//Call join on all thread objects using a range-based for loop
	for(auto &t : threads)
	{
		t.join();
	}

	//Example 2 - Using a Lambda Instead of a Function-------------------------------
	vector<std::thread> more_threads;

	//create threads
	for(size_t i{0}; i < 10; i++)
	{
		//create new thread from a lambda
		more_threads.emplace_back([i]()
			{
				//Wait for a certain amount of time
				this_thread::sleep_for(chrono::milliseconds(10 * i));

				//perform work
				cout << "Hello from Worker thread #" << i << endl;
			});
	}

	//Do something in main()
	cout << "Hello from Main thread" << endl;

	//Call join on all thread objects using a range-based for loop
	for(auto &t : more_threads)
	{
		t.join();
	}

    return 0;
}