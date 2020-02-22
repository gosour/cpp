/* Explore move semantics along with copy ctor and assignment operator*/
#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

class Base {
	int *resource;
	int count;
	public:
	Base(int count, int n): count(count), resource(new int[count]) {updateResource(n);}
	void dumpResource();
	void updateResource(int n);
};


void Base::dumpResource(){
	for(int i=0; i<count; i++)
		cout<<resource[i]<<" ";
	cout<<endl;
}

void Base::updateResource(int n){
	for(int i=0; i<count; i++)
		resource[i] = n;
}

class Base1 {
	int *resource;
	int count;
	public:
	Base1(int count, int n): count(count), resource(new int[count]) {
		cout<<"ctor called"<<endl;
		updateResource(n);
	}

	Base1(const Base1 &b): count{b.count}, resource(new int[b.count])  //Constructor signature no return type if 'const' is removed we cannot take in rvalue objects like Base1(Base1(10))
	{
		cout<<"lval copy ctor called"<<endl;
		//Do a deep copy
		//memcpy(resource, b.resource, count * sizeof(int)); 
		std::copy(b.resource, b.resource+b.count, resource);
		//IMPORTANT: Notice that we are accessing private members of other instance
		//In c++ protection is class level not object level
		//Since copy ctor needs to copy all levels not allowing that would be disastrous 
		//The compiler/language checks whether it is the same class accessing the private member irrespective of the object
		//https://stackoverflow.com/questions/3247671/accessing-protected-members-in-a-derived-class
		//In the context of inheritance a class can only access protected members of this class or a derived class not of a parent class
	}

	Base1(Base1 &&b) noexcept: count{0}, resource{NULL}  //Move constructor
	{
		//noexcept is needed because std containers will not use "throwing" move ctor
		//for eg when vector resizes it will want to "move" objects from old buffer to new buffer
		//if "move" can throw it might leave old buffer in invalid state
		//so will fallback to copy ctor taking const T& so not modifying old buffer

		cout <<"rval copy ctor called"<<endl;
		swap(count, b.count); //swap might be overkill in this case, just assignment would have worked better
		swap(b.resource, resource); 
		//Note: For swapping make sure you leave the swapped from temp object in a proper/complete state
		// Complete state: meaning that the destructor call should be correct
	}
	~Base1() {
		delete[] resource;
	}
	
	//assignment operator 1	
	/*Base1& operator=(const Base1 &rhs) { //is not exception safe, but might be faster
		if(this != &rhs){
			delete[] resource; //can fail
			resource = nullptr; //even if new int[] fails resource has been modified
			count = rhs.count;
			resource = new int[rhs.count]; //can fail and leave the object in undefined state
			std::copy(rhs.resource, rhs.resource + rhs.count, resource);
		}
		return *this;
	}*/
	
	//assignment operator 2
	//can take rvalue as well as lvalue
	Base1& operator=(Base1 rhs) { //take by value & return type is "non-const" according to standard/implicit implementations 
		//if obj = base1(); ie rval, our rhs will be constructed using the rval copy ctor from the temporary passed to it
		cout<<"= operator called"<<endl;
		swap(rhs.resource, resource);
		swap(rhs.count, count);
		return *this;	
	}
	//assignment operator 3
	//Below if defined will lead to compiler error due to ambiguity on a = std::move(b) if 2 is present but not if 1 is present
	/*Base1& operator=(Base1 &&rhs) { 
		cout<<"= operator called"<<endl;
		swap(rhs.resource, resource);
		swap(rhs.count, count);
		return *this;	
	}*/

	void dumpResource();
	void updateResource(int n);
};


void Base1::dumpResource(){
	for(int i=0; i<count; i++)
		cout<<resource[i]<<" ";
	cout<<endl;
}

void Base1::updateResource(int n){
	for(int i=0; i<count; i++)
		resource[i] = n;
}

void myswap(Base1 &b1, Base1 &b2)
{
	//copy assignment from temporary will work even if rval copy assignment is not defined
	//but it does extra work. It uses the move ctor to construct the functions formal object
	//IMPORTANT: pass by value can take both lvalue and rvalue
	//But pass by lval-reference can only take lval-reference
	//and similarly rval-reference can only take rval-reference
	//So if move assignment is defined it will not compile along side with copy by value assignment in the below case
	Base1 temp = std::move(b1);
	b1 = std::move(b2); 
	b2 = std::move(temp);
}

int main()
{	cout<<"===Normal ctors==="<<endl;
	Base b(2,99);
	Base c = b; //no deep copy with default ctor
	b.dumpResource();
	c.dumpResource();
	b.updateResource(10);
	c.dumpResource(); //with default copy ctor the pointer is copied so both point to same resource
	cout<<"====Copy ctors==="<<endl;
	Base1 b1(3,33);
	Base1 c1 = b1;
	b1.dumpResource();
	c1.dumpResource();
	b1.updateResource(10);
	c1.dumpResource(); 
	
	cout<<"===Copy ctors with rval reference==="<<endl;
	//Base1 a1(Base1(5,-1)); //Copy ctor with rvalue is not called because of ellision
	Base1 a1(std::move(Base1(5,-1))); //Passed an rvalue object
	a1.dumpResource();
	
	cout<<"===assignment operator==="<<endl;
	Base1 b2(7,100);	
	Base1 c2(11,500);
	Base1 c3(13,333);
	cout<<"==="<<endl;
	(b2 = c2) = c3; //default assignment operator is implicitly declared as deleted because ‘Base1’ declares a move constructor or move assignment operator
	//for the above if = operator returns constant that constant object is passed to the next = operator which will cause compiler error
	cout<<"==="<<endl;
	c3 = std::move(Base1(4,444)); 
	//above will call ctor to create temp rval -> 
	//then will call rval copy ctor to construct parameter of operator '=' function
	b2.dumpResource();
	c3.dumpResource();
	
	cout<<"===swap==="<<endl;
	myswap(b2,c3);
	b2.dumpResource();
	c3.dumpResource();
	
	cout<<"==lval+rval==="<<endl;
	Base1 &lvalref = b2;
	Base1 &&rvalref = std::move(b2);
	c2 = lvalref;
	c3 = rvalref; //lval copy ctor called and then = operator called because rvalref is a lval
	c3 = std::move(lvalref); //rval copy ctor called and then = operator called
	return 0;
}
