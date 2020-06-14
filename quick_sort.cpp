#include<iostream>
#include<vector>
#include<functional>
using namespace std;

template <class Itr, class T>
Itr partition(Itr begin, Itr end, T comp){
	typename Itr::value_type pivot = *std::prev(end, 1);
	Itr pivot_itr	= std::prev(end, 1);
	Itr i = std::prev(begin, 1);
	Itr j;

	for(j = begin; j != std::prev(end,1); j = std::next(j,1)){
		if(comp(*j, pivot)){
			i = std::next(i,1);
			swap(*j, *i);
		}
	}
	i = std::next(i,1);
	swap(*(i), *std::prev(end,1));
	return i;
}

template <class Itr, class T>
void quick_sort(Itr begin, Itr end, T comp)
{
	auto size = std::distance(begin, end);
	if(size < 2) return;
	Itr pi = partition(begin, end,comp);
	quick_sort(begin, pi, comp);
	quick_sort(pi, end, comp);

}


int main(){
	vector<int> v{4,1,7,123,5,6,10};
	quick_sort(v.begin(), v.end(),std::greater<int>());
	for(auto &i: v)
		cout<<i<<" ";
	cout<<endl;
}
