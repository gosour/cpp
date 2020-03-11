/*
* Explore std::function
*/
#include<iostream>
#include<functional>

using namespace std;

/*
template<class T> 
struct function; //not defined

template<class R, class... A>
class function <R (A...)> {...} //Partial template specialization
Meaning the class is specialized for the function pointer type <R (A...)>
it is unpacked as type R and type A

similar example
template<class T>
class myclass <T[]> //specialized only for array type
*/
struct Foo {
	Foo(int num) : num(num) {}
	void print_add(int i) const { cout<<num + i<<endl;}
	int num;
};

void print_num(int i)
{
	cout<<i<<endl;
}

int main()
{
	int value = 5;
	using fun = std::function<void()> ;
	fun f1 = [=]() mutable {std::cout<<value++<<std::endl;};
	fun f2 = f1;
	f1();
	fun f3 = f1; //when this is being copied the captured value has been incremented
	f2();
	f3();
	//prints 5 5 6
	cout<<value<<endl; //value of 5 has not changed

	//store a free function
	function<void(int)> f_display = print_num;
	f_display(0);

	//store a lambda
	function<void(int)> l_display = [](int n) { cout<<n<<endl;};
	
	//store result of a bind
	function<void()> f_display_42 = std::bind(print_num, 42);
	f_display_42();

	//store member function
	function<void(const Foo&, int)> f_add_display = &Foo::print_add;
	Foo foo(50);
	f_add_display(foo, 30);
	return 0;
}
