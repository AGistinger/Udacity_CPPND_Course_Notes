// CPP_Concurrency_Mutex_Avoid_Deadlock

/*
Lock Guard
-std::lock_guard
-Locks and unlocks automatically
-Protects the lock in case there is an exception making sure other threads can 
 access the data again.

 Unique_Lock
 -std::unique_lock
 -allowd for more flexible control and provides support for advanced mechanisms
 -uniqe_lock allows you to
   …construct an instance without an associated mutex using the default constructor
   …construct an instance with an associated mutex while leaving the mutex unlocked at first using the deferred-locking constructor
   …construct an instance that tries to lock a mutex, but leaves it unlocked if the lock failed using the try-lock constructor
   …construct an instance that tries to acquire a lock for either a specified time period or until a specified point in time

   You can use std::lock() to ensure that the mutexes are always locked in the same order 
   regardless of the arguments.

   The std::adopt_lock option allows you to use std::lock_guard on an already locked mutex
*/

#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>

//Global Variables
std::mutex mtx;
double result;
std::mutex mutex1, mutex2;

void print_result(int denom)
{
	std::cout << "for denom = " << denom << ", the result is " << result << std::endl;
}

void divide_by_number(double num,double denom)
{
	try
	{
		//divide num by denom but throw an exception if division by zero is attempted
		if(denom != 0)
		{
			//std::lock_guard<std::mutex> lck(mtx); //Using loack_guard
			std::unique_lock<std::mutex> lck(mtx);  //Using unique_lock

			result = num / denom;
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			print_result(denom);
		}
		else
		{
			throw std::invalid_argument("Exception from thread: Division by zero!");
		}
	}
	catch(const std::invalid_argument & e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
}

void thread_a()
{
	//Ensure that locks are alwasy executed in the same order
	std::lock(mutex1, mutex2);
	std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);
	std::cout << "Thread A" << std::endl;
	std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
}

void thread_b()
{
	std::lock(mutex1, mutex2);
	std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
	std::cout << "Thread B" << std::endl;
	std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);
}

void execute_threads()
{
	std::thread t1(thread_a);
	std::thread t2(thread_b);

	t1.join();
	t2.join();

	std::cout << "Finished" << std::endl;
}

int main()
{
	//create a number of threads which execute the function "divide_by_number" with varying parameters
	std::vector<std::future<void>> futures;
	for(double i{-5}; i <= +5; ++i)
	{
		futures.emplace_back(std::async(std::launch::async, divide_by_number, 50.0, i));
	}

	//wait for the results
	std::for_each(futures.begin(),futures.end(),[](std::future<void> &fut)
		{
			fut.wait();
		});

	execute_threads();

    return 0;
}