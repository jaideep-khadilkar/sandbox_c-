#include <iostream>
#include <stack>
using namespace std;

void printStack(stack<int> mystack)
{
	while(!mystack.empty())
	{
		cout << mystack.top() << ",";
		mystack.pop();
	}
	cout << endl;
	return;
}

void operation(stack<int>& mystack,char op)
{
	int top1 = mystack.top();
	mystack.pop();
	int top2 = mystack.top();
	mystack.pop();

	int result = 0;
	if(op=='+')
		result = top1+top2;
	if(op=='*')
		result = top1*top2;
	mystack.push(result);
}

int solution(string &S)
{
	stack<int> mystack;

	for(char& c : S)
	{
		switch(c)
		{
			case '+':
			{
				if(mystack.size()<2)
					return -1;
				operation(mystack,'+');
				break;
			}
			case '*':
			{
				if(mystack.size()<2)
					return -1;
				operation(mystack,'*');
				break;
			}
			default:
			{
				mystack.push(int(c)-int('0'));
				printStack(mystack);
				break;
			}
		}
	}
	if(mystack.empty())
		return -1;
	else
		return mystack.top();
}

int main()
{
	std::string S = "13+62*7+*";
    return 0;
}
