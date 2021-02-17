#include<future>
#include<thread>
#include<iostream>

int main(){
	int res;
	std::thread t([&]{std::cout<<"In thread\n"; res = 2000+1;});
	t.join();

	std::cout<<"res: "<<res<<"\n";

	auto fut = std::async([]{std::cout<<"In future\n"; return 2000 + 11;});
	//fut type is future<int> templatized according to the return type
	//std::async returns a future object
	//if we are not specifying any start policy the cruntime decides
	//whether a thread will be used for the task
	
	std::cout<<"fut.get(): "<<fut.get()<<"\n"; //fut.get() call is blocking
	
	//By default std::async executes the work package eagerly -> eager evaluation
	//For fut2 if std::launch::deferred was not provided, it would execute it (ie print)
	//even though .get is not called 
	auto fut2 = std::async(std::launch::deferred,[]{std::cout<<"In future2\n"; return 9999 + 10;});
	
	//Fire and forget
	/*std::async(std::launch::async, []{
			std::this_thread::sleep_for(std::chrono::seconds(3));
			std::cout<<"Fire and forget\n";});
	*/
	//The future blocks the program in it's destructor until the promise is done
	//if no lhs the temp object gets destroyed then "End" is printed
	//fut3 occurs concurrently but the above will result in sequential execution
	auto fut3 = std::async(std::launch::async, []{
			std::this_thread::sleep_for(std::chrono::seconds(3));
			std::cout<<"Fire and forget\n";});

	std::cout<<"End\n";
}
