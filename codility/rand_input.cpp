

#include <stack>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void rand1()
{
	cout << "[";

	srand (time(NULL));
	for(uint i=0;i<1000;++i)
	{
		if(i!=0)
			cout <<	",";

		cout << rand() % 1000000000 + 1;
	}
	cout << "]"<< endl;
}

void randRange(int min, int max, uint length)
{
	cout << "[";

	srand (time(NULL));
	for(uint i=0;i<length;++i)
	{
		if(i!=0)
			cout <<	",";

		cout << min + ( rand() % ( max - min + 1 ) );
	}
	cout << "]"<< endl;
}




int main()
{
	randRange(-100,20,100);

	return 0;
}
