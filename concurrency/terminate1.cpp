#include<thread>
#include<chrono>
#include<iostream>

using namespace std;

void thread_func()
{
	for(int i=0; i<20; i++){
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		cout<<"Hey jude!\n";
	}		
}

int main(){
	{
		std::thread t1{thread_func};
		//t1's destructor will be called on a joinable t1
		//according to standard the destructor will be calling std::terminate();
		//But if I join, or detach this won't be happening
		//t1.join();
		t1.detach();
	}
	std::cout<<"HELLO WORLD, I should never be displayed\n";
	return 0;
}
