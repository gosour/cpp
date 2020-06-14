#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

class Singleton
{
	private:
		static Singleton *_sinstance;
		static std::mutex _mutex;
		std::string value_;
		Singleton(string value): value_{value}{}
	public:
		~Singleton () {cout<<"Destroyed resources\n";}
		Singleton() = delete;
		Singleton(Singleton &) = delete;
		Singleton operator=(const Singleton &) = delete;
		static Singleton *GetInstance(const std::string &value){
			if(_sinstance == nullptr){
				std::lock_guard<std::mutex> lock(_mutex);
				if(_sinstance == nullptr){
					_sinstance = new Singleton(value);
				}
			}
			return _sinstance; 	
		}
		std::string value() const{
			return value_;
		}
};

Singleton* Singleton::_sinstance{nullptr};
std::mutex Singleton::_mutex;

void ThreadFoo(){
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	Singleton* singleton = Singleton::GetInstance("FOO");
	std::cout <<singleton->value() <<"\n";	
}

void ThreadBar(){
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	Singleton* singleton = Singleton::GetInstance("BAR");
	std::cout <<singleton->value() <<"\n";
}

int main(){
	std::thread t1(ThreadFoo);
	std::thread t2(ThreadBar);
	t1.join();
	t2.join();
	return 0;
}
