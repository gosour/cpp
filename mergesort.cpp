#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

template<typename It>
std::vector<typename It::value_type> merge(const It begin, const It mid, const It end)
{
	std::vector<typename It::value_type> v; //merged vector

	It it_l{begin}, it_r{mid}; //beginning pointers of two vectors
	const It it_mid{mid}, it_end{end}; //end pointers of two

	while(it_l != it_mid && it_r != it_end){
		v.push_back((*it_l <= *it_r)? *it_l++ : *it_r++);
	}
	//any one will be there or none
	v.insert(v.end(), it_l, it_mid); //all the remaining
	v.insert(v.end(), it_r, it_end);
	return v;
}

template<typename It>
void merge_sort(It begin, It end)
{
	auto size = std::distance(begin, end);
	if(size < 2) return;

	auto mid = std::next(begin, size/2);
	merge_sort(begin, mid);
	merge_sort(mid, end);

	auto v = merge(begin, mid, end);
	//move this vector to actual
	std::move(v.cbegin(), v.cend(),begin);

}

int main()
{
	vector<int> v1 = {3,4,6,1,8,11,4,12,9};
	merge_sort(v1.begin(), v1.end());
	for(auto &i : v1){
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;

}
