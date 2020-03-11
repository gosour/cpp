#include <iostream>
template<typename T> void P(T x) { std::cout << x; }
struct X { X() { P('0'); } ~X() { P(1); } X(const X&){ P(2);} };
int main() {    
	try {        
		P(5);
		throw X();        
		P(6);    
	} catch (X e) {
	        P(7);    
	}    P(8);
	P('\n');
}
