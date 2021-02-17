#include<iostream>
#include<thread>
#include<chrono>
#include<vector>
#include<algorithm>
#include<numeric>
#include<functional>

using namespace std;
template<class T>
struct accumulate_block{
	void operator()(T begin , T end, typename T::value_type &accum)
	{
		accum = std::accumulate(begin, end, accum);
	}
};

template <class T>
typename T::value_type parallel_accumulate(T begin, T end, typename T::value_type &accum)
{
	size_t size = std::distance(begin, end);
	if(size == 0)
		return 0;
	const int min_block_size = 128;
	const int max_threads = (size + min_block_size - 1) / min_block_size;
	const int hardware_thread_count = std::thread::hardware_concurrency();
	const int thread_count = min( (hardware_thread_count == 0)? 2: hardware_thread_count, max_threads);
	const int block_size = size/thread_count;
	
	cout<<"thread_count: "<< thread_count<<" block_size "<<block_size<<endl;

	vector<typename T::value_type> results(thread_count);
	vector<std::thread> threads(thread_count-1);
	T block_begin = begin;
	T block_end = begin;
	for(int i=0; i<thread_count-1; i++){
		std::advance(block_end, block_size);
		threads[i] = std::thread(accumulate_block<T>(), block_begin, block_end, std::ref(results[i]));
		block_begin = block_end;
	}
	accumulate_block<T>()(block_begin, end, results[thread_count-1]);
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

	return accum = std::accumulate(results.begin(), results.end(), accum);
}
int main()
{
	int testlist_size = 90000000;
	long testlist_accum = 0;
	vector<long> testlist(testlist_size);
	for(int i=0 ; i<testlist_size; i++){
		testlist[i] = i;
	}	
	testlist_accum = parallel_accumulate(testlist.begin(), testlist.end(), testlist_accum);
	//testlist_accum = std::accumulate(testlist.begin(), testlist.end(), testlist_accum);
	cout<<"ACCUM value is: "<<testlist_accum<<"\n";
	return 0;
}
