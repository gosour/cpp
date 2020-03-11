/*
* Explore lambda functions
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<memory>
#include<functional>

using namespace std;

int main()
{
	vector<int> vec{1,2,3,4,5};
	vector<int> vec2(5);
	vector<int> vec3(5);
	//for_each accepts unary function whose return value if any is ignored
	//transform parameters are begin, end, writeBegin (where transformation is applied
	//transform return type is often deduced
	transform(vec.begin(), vec.end(), vec2.begin(), [](int &n){
		return n*n;
	});
	
	//explicitly mentioning return type, needed for cases when return type cannot be deduced
	transform(vec.begin(), vec.end(), vec3.begin(), [](int &n) -> int {
		return n*n*n;
	});
	
	//for_each can also be used for "transforming" the current vector by using non-const reference
	for_each(vec.begin(), vec.end(), [](const int &n){
		cout<<n<<" ";
	});
	cout<<endl;
	for_each(vec2.begin(), vec2.end(), [](const int &n){
		cout<<n<<" ";
	});
	cout<<endl;
	for_each(vec3.begin(), vec3.end(), [](const int &n){
		cout<<n<<" ";
	});
	
	cout<<endl;
	//Usually a functor is constructed with parameters passed to it in constructors 
	//this can also be achieved in lambdas by using the capture list to "capture" values
	int multiplier = 5;
	int metoo = 13;	
	//for_each(vec3.begin(), vec3.end(), [](const int &n) { //ERROR
//	for_each(vec3.begin(), vec3.end(), [&](const int &n) { //capture all variables used in lambda by reference 
	//for_each(vec3.begin(), vec3.end(), [=](const int &n) { //capture all used by value
	//for_each(vec3.begin(), vec3.end(), [=, const &metoo](const int &n) { //capture all used by value
	for_each(vec3.begin(), vec3.end(), [=, &metoo](const int &n) { //capture all used by value
		cout<<n*multiplier<<" ";
		metoo++;
		//n++; //ERROR! increment of read only copy
		//capture list by value is const by default to protect programmers
		//if [=]() mutable {} then we can do that
	});
	cout<<"\nMETOO :"<<metoo<<endl;
	
	//The above was C++11 lambda support
	//Only copy by value and pass by reference was supported
	//In C++14 capture members can be arbitary expressions
	//support by value-move
	//Also lambdas are now generic
	
	auto l1 = [](auto x, auto y){return x+y;};
	cout<<l1(10,20)<<endl;
	unique_ptr<int> ptr(new int{10});
	*ptr = 666;
	//The declared capture's type is deduced from the expression as in auto 
	auto ret = [value = std::move(ptr)](int param) -> float {
			*value = param * 0.5f; return *value;
			}(999);
	cout<<ptr.get()<<endl; //will return 0 and the initial object is destroyed
	cout<<ret<<endl;
	int x = 4;
	auto y = [&r = x, x = x+1]()->int {
		r += 2;
		return x+2;
	}();
	cout<<x <<" "<<y<<endl; //should output 6 7
	//Lambdas can be wrapped inside std::function
	std::function<void(int a)> lprint = [](int a){cout<<a<<endl;};
	std::function<int(int a, int b, int c)> lsum = [](int a, int b, int c) { return a+b+c;};
	lprint(lsum(50,60,70));
	return 0;
}
