// CPP_Concurrency_Mutex_Protected_Shared

/*
Mutexes
-mutex: provides the core functions lock() and unlock() and the non-blocking try_lock() method that 
 returns if the mutex is not available.
-recursive_mutex: allows multiple acquisitions of the mutex from the same thread.
-timed_mutex: similar to mutex, but it comes with two more methods try_lock_for() 
 and try_lock_until() that try to acquire the mutex for a period of time or until a moment in time is reached.
-recursive_timed_mutex: is a combination of timed_mutex and recursive_mutex.
*/

#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>
#include <mutex>

class Vehicle
{
public:
	Vehicle(int id) : _id(id) {}

private:
	int _id;
};

class WaitingVehicles
{
public:
	WaitingVehicles() : _tmpVehicles(0) {}

	//getters/setters
	void printSize()
	{
		_mut.lock();
		std::cout << "#vehicles = " << _tmpVehicles << std::endl;
		_mut.unlock();
	}

	//typical behaviour methods
	void pushBack(Vehicle &&v)
	{
		_mut.lock();
		//vehicles.push_back(std::move(v));  //data race would cause exeception
		int oldNum = _tmpVehicles;
		//std::this_thread::sleep_for(std::chrono::microseconds(1));  //wait deliberately to expose the data race
		_tmpVehicles = oldNum + 1;
		_mut.unlock();
	}

private:
	std::vector<Vehicle> _vehicles;  //list of all vehicles waiting to enter this intersection
	int _tmpVehicles;
	std::mutex _mut;
};

int main()
{
	std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
	std::vector<std::future<void>> futures;

	for(int i{0}; i < 1000; ++i)
	{
		Vehicle v(i);
		futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
	}

	std::for_each(futures.begin(),futures.end(),[](std::future<void> &fut)
		{
			fut.wait();
		});

	queue->printSize();

    return 0;
}