

#include <stack>
#include <vector>
#include <iostream>

using namespace std;

int findLeader(vector<int> &A,uint start,uint end)
{
//	start = 0;
//	end = A.size();

	uint N = end-start;
	uint size = 0;
	int value = 0;
	for(uint i = start;i < end;++i)
	{
		if(size==0)
		{
			size++;
			value = A[i];
		}
		else
		{
			if(value!=A[i])
				size--;
			else
				size++;
		}
	}
	int candidate = -1;
	if(size>0)
		candidate = value;
	int leader = -1;
	uint count = 0;
	for(uint i = start;i < end;++i)
	{
		if(A[i]==candidate)
			count++;
	}
	if(count > (N/2))
		leader = candidate;

	return leader;
}


int solution(vector<int> &A)
{
	uint count = 0;
	for(uint i=0;i<A.size()-1;++i)
	{
		int leftLeader = findLeader(A,0,i+1);
		int rightLeader = findLeader(A,i+1,A.size());
		if( (leftLeader==rightLeader) && (leftLeader!= -1) )
			count++;
	}
	return count;
}

int main()
{
	vector<int> A = {4,3,4,4,4,2};
	cout << "solution : " << solution(A) << endl;
	return 0;
}
