/*
* To explore basics of C++ oop
*/
#include<iostream>
using namespace std;

class Base{ //adding final keyword will not allow base to be derived from
	private:
		int n;
	public:
		Base(int n) : n{n}{}
		int get_n() {return n;}
		void whoami() {cout<<"I am base"<<endl;}
		virtual void vwhoami() {cout <<"I am base, but can be overriden"<<endl;}

};


class Derived: public Base{
	private:
		int n;
	public:
		Derived(int n) : n{n}, Base{n}{}  //constructing base is necessary for constructing derived
		int get_n(int p) {return n*p;} //This hides all of the names from base
		//using Base::get_n; //Import the name explicitly
		void whoami() {cout<<"I am derived"<<endl;}
		void vwhoami() override {cout <<"I am derived, but can be overriden"<<endl;}
};

int main(){
	Derived d1(10);
	Base b1 = d1; //slicing happens because it is publicly inherited
	cout<<d1.get_n(10)<<endl;
	cout<<d1.Base::get_n()<<endl;
	//cout<<d1.get_n()<<endl;
	cout<<b1.get_n()<<endl;


	Base *bp = new Derived{10};
	bp->whoami(); //will print Base
	static_cast<Derived *>(bp)->whoami();
	bp->vwhoami(); //will print Derived


	void (Base::*whoami)()  = &Base::whoami;
	(bp->*whoami)(); //invoking a member function pointer needs to be associated with an object
	return 0;
}
