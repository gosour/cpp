/*
*Explore templates
*/

#include<iostream>
using namespace std;

class Iter{
	private:
	int n;
	public:
	Iter(const int n): n{n} {}
	template <class T>
	void operator() (T *elem){
		for(int i = 0; i<n; i++)
			cout<<elem[i]<<" ";
		cout<<endl;
	}
	template <class T>
	void operator() (T *elem, T val){
		for(int i = 0; i<n; i++)
			elem[i] = val;
	}
};

template <class T>
class A{
	T *arr;
	int count;
	public:
	A(int c): count{c}, arr{c? new T[c]: NULL} {}
	A(int c, T val): A{c} {
		Iter iter(count);
		iter(arr,val);
	}
	void iterate() {
		Iter iter(count);
		iter(arr);
	}
};

int main()
{
	A<int> a(10);
	a.iterate();
	A<int> b(10, 5);
	b.iterate();
	A<char> c(10, 's');
	c.iterate();
}
