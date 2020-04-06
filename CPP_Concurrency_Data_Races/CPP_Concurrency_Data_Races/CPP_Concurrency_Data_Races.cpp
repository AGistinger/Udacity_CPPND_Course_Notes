// CPP_Concurrency_Data_Races

/*
Data races are when two tasks/threads are racing to get to the same data
One of those tasks could be modifying the data while the other is trying to read it,
This could potentialy cause a data breach if sensitive information, like a password is being read.

You can use futures to force the threads to wait for the information so that data races do not happen,
you can also make copies of the argument to be passed in so that the information it is expecting is correct.
*/

#include <iostream>
#include <thread>
#include <future>
#include <memory>

class Vehicle
{
public:
	//default constructor
	Vehicle() : _id(0), _name(new std::string("Default Name"))
	{
		std::cout << "Vehicle ID# " << _id << " Default Constructor Called" << std::endl;
	}

	//initializing constructor
	Vehicle(int id, std::string name)
		: _id(id), _name(new std::string(name))
	{
		std::cout << "Vehicle ID# " << _id << " Initializing Constructor Called" << std::endl;
	}

	//deep copy constructor
	Vehicle(const Vehicle& source)
	{
		_id = source._id;
		if(source._name != nullptr)
		{
			*_name = *(source._name);
		}
		std::cout << "Vehicle ID# " << _id << " Copy Constructor Called" << std::endl;
	}

	//move constructor
	Vehicle(Vehicle&& source) noexcept
		:_name(std::move(source._name))
	{
		_id = source.get_id();
		source.set_id(0);
		std::cout << "Vehicle ID# " << _id << " Move Constructor Called" << std::endl;
	}

	//move assignement operator (=)
	Vehicle& operator=(Vehicle&& rhs) noexcept
	{
		if(this == &rhs)
		{
			return *this;
		}
		this->_id = std::move(rhs._id);
		this->_name = std::move(rhs._name);
		std::cout << "Vehicle ID# " << this->_id << " Move Assignement Called" << std::endl;
	}

	//getter and seeter
	void set_id(int id) { _id = id; }
	int get_id() { return _id; }
	void set_name(std::string name) { *_name = name; }
	std::string get_name() { return *_name; }

private:
	int _id;
	std::unique_ptr<std::string> _name;
};

int main()
{
	//---Race Condition Example-----------------------------------------------------
	//create instance of class Vehicle
	Vehicle v0; //default constructor
	Vehicle v1 {1, "Vehicle 1"}; //iinitializing constructor

	//read and write name in different threads (which one causes a data race?)
	std::future<void> fut = std::async([] (Vehicle v) 
		{
			std::cout << "Future was called\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			v.set_id(2);
			v.set_name("Vehicle 2");
			std::cout << "Vehicle ID# set to " << v.get_id() << std::endl;
		}, std::move(v0));

	v0.set_id(3);
	v0.set_name("Vehicle 3");

	fut.wait(); 

	std::cout << "Vehicle ID# " << v0.get_id() << std::endl;
	std::cout << "Vehicle Name: " << v0.get_name() << std::endl;

    return 0;
}