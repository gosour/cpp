#include<iostream>
#include<thread>
#include<mutex>
#include<stdlib.h>
#include<condition_variable>
#include<vector>

using namespace std;

static const int MAXSIZE = 10;
std::mutex mtx;
//condition_variable list_full;
//condition_variable list_empty;
condition_variable list_cond;
int elems = 0;
vector<int> mylist;

void producer(){
	while(1){
		std::unique_lock<mutex> lck(mtx); 			
		/*while(elems == MAXSIZE)
			wait(lck,list_empty);
		*/
		cout<<"PRODUCING\n";
		list_cond.wait(lck,[]{return elems != MAXSIZE;});
		mylist.push_back(rand()%100);
		elems++;
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if(elems == MAXSIZE){
			/*signal(list_full);*/
			list_cond.notify_one();
		}
	}
}

void consumer(){
	while(1){
		std::unique_lock<mutex> lck(mtx);		//unique_lock instead of lock_guard because we also want it to be unlocked
											    //lock_guard only allows locking once when construction (more restrictive)
		/*while(elems != MAXSIZE){
			wait(lck, list_full);
		}*/
		list_cond.wait(lck,[]{return elems == MAXSIZE;});
		cout<<"CONSUMING\n";
		for(auto n: mylist) cout<<n<<" ";
		cout<<endl;
		mylist.clear();
		elems = 0;
		/*signal(list_empty);*/
		lck.unlock();//for reducing spurious wakeup
		list_cond.notify_one();
	}
}

int main(){
	thread producer_thread{producer};
	thread consumer_thread{consumer};

	producer_thread.join();
	consumer_thread.join();
}
