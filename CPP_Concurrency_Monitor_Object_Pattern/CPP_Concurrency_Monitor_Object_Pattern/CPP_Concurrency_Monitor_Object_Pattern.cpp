// CPP_Concurrency_Monitor_Object_Pattern

/*
condition variables
*/

#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <condition_variable>

class Vehicle
{
public:
	Vehicle(int id) : _id(id) {}
	int getID() { return _id; }

private:
	int _id;

};

class WaitingVehicles
{
public:
	WaitingVehicles() :_counter{0} {}

	bool dataIsAvailable()
	{
		std::lock_guard<std::mutex> myLock(_mutex);
		return !_vehicles.empty();
	}

	Vehicle popBack()  //send data
	{
		//perform vector modification under the lock
		std::unique_lock<std::mutex> uLock(_mutex);
		_cond.wait(uLock, [this] { return !_vehicles.empty(); }); //pass unqiue lock to condition variable

		//remove last vector element from queue
		Vehicle v = std::move(_vehicles.back());
		_vehicles.pop_back();
		--_counter;

		return v; //will not be copied due to return value optimization (RVO) in c++
	}

	void pushBack(Vehicle &&v)  //receive data
	{
		//perform vector modification under the lock
		std::lock_guard<std::mutex> uLock(_mutex);
		std::cout << "Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
		_vehicles.emplace_back(std::move(v));
		++_counter;
		_cond.notify_one();

		//simulate some work
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	int getCounter() { return _counter; }

private:
	std::vector<Vehicle> _vehicles; //list of all vehicles waiting to etner this intersection
	std::mutex _mutex;
	std::condition_variable _cond;
	int _counter;
};

int main()
{
	//create monitor object as a shared pointer to enable access by multiple threads
	std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

	std::cout << "Spawning threads..." << std::endl;
	std::vector<std::future<void>> futures;

	for(int i{0}; i < 10; ++i)
	{
		//create a new Vehicle instance and move it into the queue
		Vehicle v(i);
		futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	std::cout << "Collecting results..." << std::endl;
	while(true)
	{
		if(queue->dataIsAvailable())
		{
			Vehicle v = queue->popBack();
			std::cout << "Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;

			if(queue->getCounter() <= 0)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				break;
			}
		}
	}

	std::for_each(futures.begin(),futures.end(),[](std::future<void> &ftr)
		{
			ftr.wait();
		});

	std::cout << "Collecting results..." << std::endl;
	
	std::cout << "Finished processing queue" << std::endl;
	std::cout << "Remaining items in queue " << queue->getCounter() << std::endl;

    return 0;
}