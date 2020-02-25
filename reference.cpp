/* 
*Explore C++ references
*/
#include<iostream>
using namespace std;

struct mystruct_with_ref{
	char &cref;
	char &cref1;
	char &cref2;
	char &cref3;
};

struct mystruct{
	char c;
	char c1;
	char c2;
	char c3;
};

void function(int n){
	cout<<n<<" "<<&n<<endl; //since copy by value address is different
}

void function1(int &n){
	cout<<n<<" "<<&n<<endl; //address is same as actual, so no copying is happening GREAT for passing big objects as parameters
}

int main()
{
	int a = 10;
	int &aref = a;
	cout<<&a <<" "<<&aref <<" "<< (&a == &aref)<<endl; //The addresses of the variable and the reference to it is same
	function1(a);
	function1(aref);	

	char c = 'a';
	//int &cref = (int &)c; //Can forcibly cast
	char &cref = c; 
	cout<<sizeof(c) <<" "<<sizeof(cref)<<endl; //The cref is an alias to a char so size is also same, don't think it as an equivalent to pointers	
	cout<<sizeof(mystruct) <<" "<<sizeof(mystruct_with_ref)<<endl; //Prints 4 and 32 [This is a gotcha] Hint: If the compiler can propagate actual value where alias is used size will remain same
	//otherwise compiler has to rely on some mechanism to support that (pointers)
	return 0;
}
