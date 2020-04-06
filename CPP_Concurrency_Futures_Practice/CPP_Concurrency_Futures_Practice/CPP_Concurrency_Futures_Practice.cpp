// CPP_Concurrency_Futures_Practice

#include <iostream>
#include <future>
#include <thread>
#include <vector>

void worker_thread(std::promise<std::vector<int>>&& prom, std::vector<int> vec, int num_items, int starting_num)
{
	std::vector<int> numbers {};
	for(int i{0}; i < num_items; ++i)
	{
		if(i == 0)
		{
			numbers.emplace_back(starting_num);
		}
		else
		{
			numbers.emplace_back(++starting_num);
		}
	}
	prom.set_value(numbers);
}

int twice(const int a)
{
	return 2 * a;
}

template<typename T>
void display(const T& container)
{
	std::cout << "[ ";
	for(const auto& obj : container)
	{
		std::cout << obj << " ";
	}
	std::cout << "] \n";
}

int main()
{
	//Defining vector
	std::vector<int> numbers {};
	int num_items {25}, starting_num {1};

	//Creating promise and future
	std::promise<std::vector<int>> prom;
	std::future<std::vector<int>> fut = prom.get_future();

	//Start thread with promise as argument
	std::thread thd(worker_thread, std::move(prom), numbers, num_items, starting_num);

	display(numbers);

	numbers = fut.get();

	display(numbers);

	thd.join();

	//using async task
	std::vector<std::future<int>> futures;
	for(int i{0}; i < 20; ++i)
	{
		futures.emplace_back(std::async(std::launch::async, twice, i));
	}

	std::cout << '[';
	//print async task
	for(auto &obj : futures)
	{
		std::cout << obj.get() << " ";
	}
	std::cout << "]\n";
	
    return 0;
}