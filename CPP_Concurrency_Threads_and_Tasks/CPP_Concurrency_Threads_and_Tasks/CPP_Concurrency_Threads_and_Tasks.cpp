// CPP_Concurrency_Threads_and_Tasks

/*
std::async
using async will call the thread destructor automatically so you do not need to call join()
which reduces the risk of a concurrency bug.

std::async compared with std::thread
internally async creates a promise, gets a future from it and runs a template function that takes
the promise, calls our function and then either sets the value or the exception of that promise
depending on the function behavior.

if you use std::launch::deferred you will force synchronous execution
if you use std::launch::async you will force asynchronous execution

Task-Based Concurrencty
*/

#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>
#include <vector>
#include <chrono>

double divide_by_number(double num,double denom)
{
	//print system id of worker thread
	std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(500)); //simulate work

	if(denom == 0)
	{
		throw std::runtime_error("Exception from thread: Division by zero!");
	}
	else
	{
		return num / denom;
	}
}

void worker_function(int n)
{
	//print system id of worker thread
	std::cout << "Worker thread id = " << std::this_thread::get_id() << '\n';

	//perform work
	for(int i{0}; i < n; ++i)
	{
		sqrt(12345.6789);
	}
}

int main()
{
	//Using std::async instead of future and promise
	//print system id of main thread
	std::cout << "Main thread id = " << std::this_thread::get_id() << '\n';

	//use async to start a task
	double num {42.0}, denom {2.0};
	std::future<double> ftr = std::async(std::launch::deferred, divide_by_number, num, denom); //deferred enforces synchronous execution

	//retrieve result from within try-catch block
	try
	{
		double result = ftr.get();
		std::cout << "Result = " << result << std::endl;
	}
	catch(std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
	}

	//Parallel execution example with tasks
	//print system id of main thread
	std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

	//start time measurement
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	//launch various tasks
	std::vector<std::future<void>> futures;
	int n_loops {10}, n_threads {5};
	for(int i{0}; i < n_threads; ++i)
	{
		futures.emplace_back(std::async(std::launch::async, worker_function, n_loops));
	}

	//wait for tasks to complete
	for(const std::future<void> &ftr : futures)
	{
		ftr.wait();
	}

	//stop time measurement and print execution time
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << "Execution finished after " << duration << " microseconds" << std::endl;

    return 0;
}