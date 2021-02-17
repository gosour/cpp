#include<iostream>

using namespace std;

class MySingleton{
	private:
		MySingleton() = default;
		~MySingleton() = default;
		MySingleton(const MySingleton &) = delete;
		MySingleton& operator=(const MySingleton &) = delete;
		//MySingleton *instance; //in the other pattern (non-thread safe init)
	public:
		static MySingleton& getInstance(){
			static MySingleton instance;
			volatile int dummy{}; //just so that compiler does not optimizes it away
			return instance;
		}
		int num = 42;
		int printHelloWorld(){
			return num * num * num;
		}
};


int main(){
	cout<<"SINGLETON SAYS: "<<MySingleton::getInstance().printHelloWorld()<<"\n";
	MySingleton::getInstance().num = 10;
	cout<<"SINGLETON again SAYS: "<<MySingleton::getInstance().printHelloWorld()<<"\n";
	return 1;
}
