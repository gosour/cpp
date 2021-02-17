/*
* Exploring RAII concepts and helper classes
*/

#include <memory>
#include <iostream>
#include <cstdio>
#include <functional>

using namespace std;

class C{
	int i;
	public:
	C() = default;
	C(int i, int j): i{i+j}{}
	void say() { cout<<"I say "<<i<<endl;}
	~C() {cout<<"C destroyed\n";}
};

void close_file(FILE *fp) { cout<<"CLOSING file\n"; std::fclose(fp);}
int main()
{
	//a new expression is used to create the object on heap unique_ptr ctor takes in a "raw" pointer of type T
	//on destruction of unique_ptr object 'delete' is called
	unique_ptr<int> pi1 = unique_ptr<int>(new int{10}); 
	//make_unique does type deduction (because it is a template function) and calls new for us
	//secondly it uses forwarding to send proper lval reference and rval reference to constructor of type T
	unique_ptr<int> pi2 = make_unique<int>(10); 
	C *pc = new C{10,50};
	{	
	unique_ptr<C> obj1 = unique_ptr<C>(new C{100,200});	
	unique_ptr<C> obj2 = unique_ptr<C>(pc);
	//template<class T, class... args>
	//unique_ptr<T> make_unique(Args &&... args)
	//the lhs cannot be used for template function type deduction
	//Arg is deduced and passed to T's constructors
	//But T can be only deduced explicitly. So we CANNOT do make_unique(C(args)) or make_unique(10)
	unique_ptr<C> obj3 = make_unique<C>(10,30);
	unique_ptr<C> obj4 = make_unique<C>(C{9,90}); //calls copy/move constructor
	}
	cout<<"BLOCK 1 ends\n";
	//What about arrays Note: use vectors best practise
	//delete[] will be called
	{
	//unique_ptr<C[]> obj4 = unique_ptr<C[]>(new C[5]);
	unique_ptr<C[]> obj5 = make_unique<C[]>(5);
	}
	//custom deleter , deleter cannot be added using make_unique
	{
		unique_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("temp","r"), &close_file);
		//unique_ptr<std::FILE> fp(std::fopen("temp","r")); //undefined behavior
		//fclose called here only if FILE * is not a null pointer
		//ie fopen succedded and a not null pointer was passed to raii object
	}
	//custom deleter with lambda function
	{
		unique_ptr<C, std::function<void(C*)>> p (new C, [](C* ptr)
			{
				cout<<"Deleting from custom lambda deleter\n";
				delete ptr;
			});
		//copy constructor for unique_ptr is "=delete"-ed
		//unique_ptr<C, std::function<void(C*)>> p1 = p; 
		unique_ptr<C, std::function<void(C*)>> p1 = std::move(p); 
	}
	cout<<"End of program\n";
	return 0;
}
