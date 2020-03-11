/*
* Explore vtable vptr and inheritance
*/
#include<iostream>

using namespace std;
struct A{
	int a;
	void say() {cout<<"a"<<endl;}
	virtual void f() {cout<<"a f"<<endl;}
};

struct B{
	int b;
	void say() {cout<<"b"<<endl;}
	virtual void g() {cout<<"b g"<<endl;}
};

struct C : public A, public B{
	int c;
	void say() {cout<<"c"<<endl;}
	void f() {cout<<"c f"<<endl;}
	void g() {cout<<"c g"<<endl;}
};

void myfunction(A* a, B* b){
	cout<<a<<" "<<b<<endl;
	a->say();
	b->say();
	a->f();
	b->g();
}

int main()
{
	C *c = new C;
	c->f();
	c->g();	
	cout<<c<<endl;
	
	B *b = c; //This cast produces a new address 
	b->g();	
	cout<<b<<endl; //address of b != c
	myfunction(c,c);
	return 0;
}
