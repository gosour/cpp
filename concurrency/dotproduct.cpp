//Concurrent calculation of dot products
#include<iostream>
#include<future>
#include<random>
#include<vector>
#include<numeric>

using namespace std;

static const int NUM = 100000000;

long long getDotProduct(vector<int>& v, vector<int> &w) 
{
	auto vsize = v.size();
	auto future1 = async(std::launch::async,[&]{
		cout<<"FUTURE1\n";
		return inner_product(&v[0], &v[vsize/4], &w[0],0LL);
	});
	auto future2 = async(std::launch::async,[&]{
		cout<<"FUTURE2\n";
		return inner_product(&v[vsize/4], &v[vsize/2], &w[vsize/4],0LL);
	});
	auto future3 = async(std::launch::async,[&]{
		cout<<"FUTURE3\n";
		return inner_product(&v[vsize/2], &v[vsize * 3/4], &w[vsize/2],0LL);
	});
	auto future4 = async(std::launch::async,[&]{
		cout<<"FUTURE4\n";
		return inner_product(&v[vsize*3/4], &v[vsize], &w[vsize*3/4],0LL);
	});

	return future1.get() + future2.get() + future3.get() + future4.get();
}

int main() {
	random_device seed;
	//generator
	mt19937 engine(seed());
	//distribution
	uniform_int_distribution<int> dist(0,100);

	//fill the vectors
	vector<int> v,w;
	v.reserve(NUM);
	w.reserve(NUM);

	for(int i=0; i<NUM; ++i){
		v.push_back(dist(engine));
		w.push_back(dist(engine));
	}
	
	cout<<"getDotProduct(v,w): "<<getDotProduct(v,w) <<endl;
}
