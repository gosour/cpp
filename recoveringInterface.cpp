/*
* Given a file with shapes (Circles, Triangles, Rectangles) reconstuct the objects
*/
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<memory>

using namespace std;

class Shape
{
	public:
	virtual void print() = 0;
	virtual ~Shape() {}
};

class Circle : public Shape
{
	private: 
	int radius;
	public:
	Circle(int radius): radius{radius} {}
	void print() override { cout<<"Circle with radius "<<radius<<endl; }
};

class Rectangle: public Shape
{
	private:
	int length, breadth;
	public:
	Rectangle(int l, int b): length{l}, breadth{b} {}
	void print() override { cout<<"Rectangle with area"<< length * breadth <<endl; }
};

class Triangle: public Shape
{
	private:
	int base, height;
	public:
	Triangle(int b, int h): base{b}, height{h} {}
	void print() override { cout<<"Triangle with area"<< (0.5f) * (base) * height <<endl; }
};

class IoObject {
	public: 
	int getint(istream &s) {int n; s>>n; return n;}
	virtual IoObject * clone() const = 0;
	virtual ~IoObject() {};
};
//TODO: convert to template
struct IoCircle: Circle, IoObject {
	IoCircle(istream &s): Circle{getint(s)} {};
	IoCircle * clone() const { return new IoCircle{*this}; }
	static IoObject * new_io_circle(istream &is) {
		return new IoCircle(is);
	}
};

struct IoRectangle: Rectangle, IoObject {
	IoRectangle(istream &s): Rectangle{getint(s), getint(s)} {};
	IoRectangle * clone() const { return new IoRectangle{*this}; }
	static IoObject * new_io_rectangle(istream &is) {
		return new IoRectangle(is);
	}
};

struct IoTriangle: Triangle, IoObject {
	IoTriangle(istream &s): Triangle{getint(s), getint(s)} {}; //TODO: order of function call is coupled with order of member declaration
	IoTriangle * clone() const { return new IoTriangle{*this}; }
	static IoObject * new_io_triangle(istream &is) {
		return new IoTriangle(is);
	}
};

using Pf = IoObject* (*)(istream &); //pointer to function taking an istream and returning an IoObject
map<string,Pf> ioMap;

void init()
{
	ioMap["rectangle"] = &IoRectangle::new_io_rectangle; 
	ioMap["circle"] = &IoCircle::new_io_circle; 
	ioMap["triangle"] = &IoTriangle::new_io_triangle; 
}

IoObject *getIoObject(istream &ss)
{
	string shape_type;
	ss >> shape_type;
	if(Pf f = ioMap[shape_type]){
		return f(ss);
	}
	return nullptr;
}

int main(int argc, char **argv)
{
	ifstream inFile;
	if(argc != 2) {
		cerr<<"Need file name"<<endl; 
		return 1;
	}
	inFile.open(argv[1]);
	if(!inFile) {
		cerr<<"Unable to load file"<<endl;
	} 
	init();
	string line;
	while(getline(inFile, line)){
		stringstream ss;
		ss << line;
		unique_ptr<IoObject> p{getIoObject(ss)};	
		if(auto sp = dynamic_cast<Shape *> (p.get())){
			sp->print();
		}
		else{
			cerr<<"Not a shape"<<endl;
		}
	}
	
	inFile.close();
	return 0;
}
