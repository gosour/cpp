#include<iostream>
#include<thread>

struct func{
	int &state;
	func(int &_state): state{_state}{}
	void operator() ()
	{
		long sum = 0;
		for (unsigned j = 0; j<100000; j++)
		{
			sum = (sum+j)%31;
		}
		std::cout<<sum<<"\n";
	}
};

class thread_guard
{
	std::thread &&t;
	public:
	explicit thread_guard(std::thread &&t_): t{std::move(t_)}{}
	~thread_guard(){
		if(t.joinable())
			t.join();
	}
	thread_guard(thread_guard const &)=delete;
	thread_guard& operator=(thread_guard const &)=delete;

};

int main()
{
	int some_local_state = 42;
	func my_func(some_local_state);
	std::thread t(my_func);
	//std::thread is not-copyable but reference can be kept
	//but if we do as below and keep reference the thread is lost
	//because the temporary object is lost
	thread_guard g(std::thread(my_func));
	//thread_guard g(t);
}
