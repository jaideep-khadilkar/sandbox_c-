

#include <iostream>

#include <vector>

using namespace std;

// 'aggregate' class - no user-declared constructor, no private/protected members,
// no base, no virtual function
struct ClassA {
   int x;
   double y;
};

// non-aggregate class
class ClassB {
private:
   int x;
   double y;
public:
   ClassB(int _x, double _y):x(_x),y(_y) {}
};

std::pair<double, double> multiplyVectors(
   std::pair<double,double> v1,
   std::pair<double,double> v2) {
   return { v1.first*v2.first, v1.second*v2.second };
}

int main()
{
	int i {3};
	int j {}; // empty braces initialize the object to it's default (0)
	std::string s {"hello"};

	ClassA objA1 {};
	ClassA objA2 {1, 2.0};
	ClassB objB1 {1, 2.0};
	ClassA arrOfAs[] = { {1,1.0}, {2,2.0}, {3,3.0} };

	// ouch, the theory is that this should work in C++11, however this doesn't compile, at least
	// with clang, comments?
	ClassB arrOfBs[] = { {1,1.0}, {2,2.0}, {3,3.0} };

	// however, this does work
	vector<ClassB> vectorOfBs = { {1,1.0}, {2,2.0}, {3,3.0} };

	auto result = multiplyVectors({1.0,2.0}, {3.0,4.0});

	cout << "TEST" << endl;
}
