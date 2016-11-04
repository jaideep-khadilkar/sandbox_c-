
#include <boost/scoped_ptr.hpp>
#include <iostream>

using namespace std;

int main()
{

	boost::scoped_ptr<int> p{new int{34}};
	p.reset(new int{433});
	cout << boolalpha << static_cast<bool>(p) << endl;
}
