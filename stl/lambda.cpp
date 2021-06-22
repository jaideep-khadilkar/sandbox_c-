

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> vecA = {1,52,-41,63,2};

	int mult = 10;

	for(auto it = vecA.begin(), end = vecA.end(); it != end; ++it)
	{
		cout << *(it) * mult << endl;
	}

	cout << "====================" << endl;

	for_each(vecA.begin(),vecA.end(),[mult](int val)
	{
		cout << val * 100 << endl;
	});

}
