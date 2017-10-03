

#include <stack>
#include <vector>
#include <iostream>

using namespace std;

int solution(string &S)
{
	stack<char> mystack;

	for(char& c : S)
	{
//		cout << " c :" << c << endl;
		if(c=='(')
			mystack.push('(');
		else
		{
			if(mystack.top()!='(')
				return 0;
			else
				mystack.pop();
		}
	}

	if(mystack.size()!=0)
		return 0;
	else
		return 1;
}

int main()
{

	std::string S = "(()(())())";
//	cout << "solution : " << solution(S) << endl;
	return 0;
}
