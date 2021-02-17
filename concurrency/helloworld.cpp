#include<iostream>
#include<thread>

void hello()
{
	std::cout<<"Hello concurrent world\n";
}

int main()
{
	std::thread t{hello}; //prefer {} to avoid C++'s most vexing parse
	t.join(); //causes calling thread (in main) to wait for thread t
	//if join is not called the main thread 
	//continue and the t object gets destructed
	//the std::thread destructor calls terminate
	//if we detach the thread, then it may continue running long after 
	//the object is destroyed
	//if we don't wait for the thread to finish then we need to take
	//care of the data the thread accesses and prevent them from
	//becoming invalid
	//Act of calling join() also cleans up any storage associated with 
	//the thread.
	//you can call join on a thread only once, joinable will return false
	//
}
