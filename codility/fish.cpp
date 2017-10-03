

#include <stack>
#include <vector>
#include <iostream>

using namespace std;

struct Fish
{
	int size;
	int dir;
};

int solution(vector<int> &A, vector<int> &B)
{
	stack<Fish> mystack;
	unsigned int N = A.size();

	for(unsigned int i=0; i < N;++i)
	{
		Fish curFish;
		curFish.size = A[i];
		curFish.dir = B[i];

		if(mystack.size()==0)
			mystack.push(curFish);
		else
		{
			Fish topFish = mystack.top();
			if( (topFish.dir==1) && (curFish.dir==0) )
			{
				if(topFish.size > curFish.size)
				{
					// Current Fish dies.Do nothing.
				}
				else
				{
					mystack.pop();
					mystack.push(curFish);
				}
			}
			else
			{
				mystack.push(curFish);
			}
		}
	}

	return mystack.size();
}

int main()
{
	vector<int> A = {4,3,2,1,5};
	vector<int> B = {0,1,0,0,0};
	cout << "solution : " << solution(A,B) << endl;
	return 0;
}
