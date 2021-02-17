#include<iostream>
#include<mutex>

class MySingleton{
	public:
		static MySingleton& getInstance(){
			std::call_once(initInstanceFlag,
					&MySingleton::initSingleton);
			return *instance;
		}
	private:
		MySingleton() = default;
		~MySingleton() = default;
		MySingleton(const MySingleton&) = delete;
		MySingleton& operator=(const MySingleton &) = delete;

		static MySingleton *instance;
		static std::once_flag initInstanceFlag;

		static void initSingleton(){
			instance = new MySingleton;
		}
};
