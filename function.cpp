#include<map>
#include<string>
	int * f(char &) {}
     
    int main()
    {
        using FunctionPtr = int * (*)(char &);
     	std::map<std::string, FunctionPtr> m;
	m["hello"] = f;
        //FunctionPtr ptr = f;
    }
