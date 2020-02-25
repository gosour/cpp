/* 
*Explore C++ universal references in templates
Forwarding reference is an rvalue reference to a CV unqualified template parameter
*/
#include<iostream>
using namespace std;

void overloaded(int &a) { cout<<"&a called"<<endl;}
void overloaded(const int &a) { cout<<"const &a called"<<endl;}
void overloaded(int &&a) { cout<<"&&a called"<<endl;}

template <class T>
void myfunction(T &&a) { //universal reference is used in type deduction, in all other cases lval and rval references are explicit and easily understood
	//final output of universal reference is either lval reference or rval reference
	//const T &&a is CV qualified so would not be a forwarding reference
	//But paramtype can be deduced as a const, because of const qualified type being passed to it
	cout<<&a<<endl;	
	//overloaded(a); //will always print &a called since will always be passed as a lval reference
	overloaded(std::forward<T>(a)); //forwarding is always used for deduced types that are universal references
	//std::forward simply does conditional cast to rval if a is an rval reference
}

void myfunction1(int &&a) {
	cout<<"HELLO"<<endl;
}

void myfunction2(int & a) {
	cout<<"HELLO"<<endl;
}

void myfunction3(const int & a) {
	cout<<"HELLO"<<endl;
}

void myfunction4(int a) {

	cout<<"HELLO"<<endl;
}

int main()
{
	int a = 10;
	auto &&b = a; //b is NOT a rvalue reference, 'auto' uses template deduction and similar to there this &&b is a forwarding reference 
		      //and on deduction becomes an lval reference since it is binding to an lval
	const int c = 0;

	myfunction(a);
	myfunction(b);
	myfunction(c);
	myfunction(10);

	//myfunction1(a); //cannot bind since lval
	//myfunction1(b); //cannot bind since lval
	myfunction1(10);

	myfunction2(a); 
	myfunction2(b); 
	//myfunction2(10); // cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’

	myfunction3(a); 
	myfunction3(b); 
	myfunction3(10); // can bind with const &

	myfunction4(a); 
	myfunction4(b);   //lvalue is used to create a new object
	myfunction4(10);  //rvalue is used to create a new 'object' no binding involved

	return 0;
}
