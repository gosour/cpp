/*
* 1. Explore constructors and destructors
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Member {
	public:
	int n;
	Member(int n): n(n) {}
};

class Base {
	int a; //c++ default is private in class public in struct
	string s;
	//Member m; //Inclusion leads to compiler error because compiler will try initializing (calling default ctor) but is not present
	static int Bcounter; //is the declaration not defination
	//static int Bcounter = 0; //will not work
public:
	Base():a(-1) { Bcounter++;}
	Base(int a): a(a) {} //even though we have not specified string compiler adds that
	Base(int a, string s): a(a), s(s) {}
	int get_a();
	string get_s();
	//int get_counter() { return Bcounter;} //Will look for this->Bcounter which is not available
	static int get_counter() { return Bcounter;} //will be able to write Base::get_counter() and bObj.get_counter()
	//int get_counter() { return Bcounter;} //is valid but will not be able to write Base::get_counter()
};

int Base::Bcounter = 0; //if this declaration is missed you will get a linker error

int Base::get_a(){
	//return this->a; //same thing as below
	return a;
}

string Base::get_s(){
	return s;
}

int main()
{
	Base b(10);
	//Base *bp = new Base(50, "fifty"); //Old style of intializing
	Base *bp = new Base{50, "fifty"};  //Prefer this
	Base ba[2] = {{30,"thirty"}, {40,"forty"}};
	
	//Base *bpa = new Base[2]; 
	//Base *bpa = new Base[2](100, "hundred"); //This is illegal
	Base *bpa = new Base[2]{{100, "hundred"},{30,"thirty"}}; //we can intialize using intializer list
	//But we cannot tell new [] to initialize every one with one object like we can do in vector
	//Base *bpa = new Base[2]{{100, "hundred"},{30,"thirty"},{60, "sixty"}}; //compiler will throw error
	//Base *bpa = new Base[Base::get_counter()]{{100, "hundred"},{30,"thirty"},{60, "sixty"}}; //if size is non-static then compiler will not throw error but generates runtime exception
	//Base *bpa = new Base[]{{100, "hundred"},{30,"thirty"},{60, "sixty"}}; //not allowed
	
	vector<Base> vp(2, Base(100, "hundred")); //Vector does this by calling inplace new constructor
	

	//Inplace ctor on custom memory address
	char *mem = (char *)malloc(sizeof(Base) * 2);
	Base *bc = new(mem) Base{80, "eighty"}; //by overloading new 
	Base *bc_temp = new(mem+sizeof(Base)) Base{90, "ninety"}; 

	cout << b.get_a() << " " << b.get_s() << endl;
	cout << bp->get_a() << " " << bp->get_s() << endl;
	cout << ba[1].get_a() << " " << ba[1].get_s() << endl;
	cout << vp[1].get_a() << " " << vp[1].get_s() << endl;
	cout << bpa[1].get_a() << " " << bpa[1].get_s() << endl;
	cout << bc[1].get_a() << " " << bc[1].get_s() << endl;
	delete bp;
	//delete bpa; //Legal but wrong
	delete[] bpa;
	bc->~Base();
	bc_temp->~Base();

	//cout<<"Counter "<< b.get_counter()<<endl; //if get_counter is non static -> returns correct result because the same static variable is read
	cout<<"Counter "<< Base::get_counter()<<endl;
	return 0;
}
