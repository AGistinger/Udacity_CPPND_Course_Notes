// CPP_Concurrency_Promises_Futures

/*
To allow for worker threads to send information back to the parent thread,
There is a such a mechanism available in the C++ standard that we can use for this purpose. 
This mechanism acts as a single-use channel between the threads. The sending end of the channel 
is called "promise" while the receiving end is called "future".

In the C++ standard, the class template std::promise provides a convenient way to store 
a value or an exception that will acquired asynchronously at a later time via a std::future object. 
Each std::promise object is meant to be used only a single time.

wait() - will block until the future is ready.  Once it returns, it is garenteed that data is available
and we can use get() to retrieve it without delay.

wait_for() - A method take takes a time duration as an input and also waits for a result to become available.
The method wait_for() will block either until the specified tiemout duration has elapsed or the result becomes available.

Allows you to determine when you receive data from the get functions.

Downside is you can only receive data from one direction and they are one time use only.
*/

#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <cmath>

void print_message(std::string message)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(10));  //simulat work
	std::cout << "Thread 1: " << message << std::endl;
}

void modify_message(std::promise<std::string>&& prms,std::string message)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(4000)); //simulate work
	std::string modified_message = message + " has been modified";
	prms.set_value(modified_message);
}

void compute_sqrt(std::promise<double> &&prom,double input)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(2000)); //simulate work
	double output = sqrt(input);
	prom.set_value(output);
}

void divide_by_number(std::promise<double> &&prom,double num,double denom)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500)); //simulate work
	try
	{
		if(denom == 0)
		{
			throw std::runtime_error("Exception from thread: Division by zero!");
		}
		else
		{
			prom.set_value(num / denom);
		}
	}
	catch(...)
	{
		prom.set_exception(std::current_exception());
	}
}

int main()
{
	//The example below shows the information flowing fromteh parent thread (main) to the worker threads (t1 and t2)	
	//define message
	std::string message = "My Message";

	//start thread using variadic templates
	std::thread t1(print_message, message);

	//start thread using a Lambda
	std::thread t2([message]
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));  //similat work
			std::cout << "Thread 2: " << message << std::endl;
		});

		//thread barrier
		t1.join();
		t2.join();

	//Using promises and futures to allow for worker threads to send information to the main thread
	//define message
	std::string message_to_thread = "My Message";

	//create promise and future
	std::promise<std::string> prms; //allows for the transmitting of a string between two threads and modifying it
	std::future<std::string> ftr = prms.get_future();  //gets the value  on the future for the promise

	//start thread and pass promise as agrument
	std::thread t(modify_message, std::move(prms), message_to_thread);  //must use move on promise because it cannot be copied

	//print original message to console
	std::cout << "Original message from main(): " << message_to_thread << std::endl;

	//retrieve modified message via future and print to console
	std::string message_from_thread = ftr.get();
	std::cout << "Modified message from thread(): " << message_from_thread << std::endl;

	//thread barrier
	t.join();

	//Using get() and wait()
	//define input data
	double input_data = 42.0;

	//create promise and future
	std::promise<double> prom;
	std::future<double> fut = prom.get_future();

	//start thread and pass a promise ad argument
	std::thread thd(compute_sqrt, std::move(prom), input_data);

	//wait for result to become available
	auto status = fut.wait_for(std::chrono::seconds(5));
	if(status == std::future_status::ready) //result is ready
	{
		std::cout << "Result = " << fut.get() << std::endl;
	}
	//timeout has expired or function has not yet been started
	else if(status == std::future_status::timeout || status == std::future_status::deferred)
	{
		std::cout << "Result unavailable" << std::endl;
	}

	//thread barrier
	thd.join();

	//Using exceptions in promises
	//create promise and future
	std::promise<double> proms;
	std::future<double> futs = proms.get_future();

	//start thread and pass promise as agrument
	double num = 42.0, denom = 0.0;
	std::thread thds(divide_by_number, std::move(proms), num, denom);

	//retrieve result within try-catch block
	try
	{
		double result = futs.get();
		std::cout << "Result = " << result << std::endl;
	}
	catch(std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
	}

	//thread barrier
	thds.join();
	
    return 0;
}