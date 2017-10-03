

#include <stack>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<int> &H)
{

    unsigned int count = 0;
    stack<unsigned int> mystack;
    unsigned int N = H.size();
    for(unsigned int i=0;i<N;++i)
    {
        unsigned int height = H[i];

        while ( mystack.size() != 0 && mystack.top() > height)
        {
        	mystack.pop();
        }

        if ( mystack.size() != 0 and mystack.top() == height)
        {
        	// DO nothing
        }
        else
        {
        	count++;
        	mystack.push(height);
        }
    }
    return count;
}

int main()
{

	std::vector<int> H = {8,8,5,7,9,8,7,4,8};
	cout << "solution : " << solution(H) << endl;
	return 0;
}
