
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class ClassA{
public:
	ClassA(int input):memberA(input){};
	bool operator==(const ClassA& other)
	{
		return this->memberA == other.memberA;
	}
	int memberA;
};

void function_pointer(const ClassA& object)
{
	cout << "for_each function_pointer : " << object.memberA << endl;
}

class Functor
{
public:
	Functor(string input):suffix(input){};
	void operator()(const ClassA& object)
		{
			cout << "for_each functor " << suffix << ": " << object.memberA << endl;
		}
	string suffix;
};

class Random
{
public:
	Random(int start, int end):start(start),mod(end-start){};
	int operator()()
		{
			return rand()%mod+start;
		}
	int mod;
	int start;
};

class Print
{
public:
	Print(){};
	void operator()(int val)
		{
			cout << val << " ";
		}
};

struct DivisibleBy
{
    const int d_;
    DivisibleBy(int d) : d_(d) {}
    bool operator()(int n) const { return n % d_ == 0; }
};

int main() {

	vector<ClassA> vecA;
	vector<ClassA>::iterator itA;

	cout << "vecA : ";
	for(int i=0;i<5;i++)
	{
		vecA.push_back(ClassA(i));
		cout << i << " ";
	}
	cout << endl;

	vector<int> vecB{11,25,-52,335,-47,25};
	vector<int>::iterator itB;
	cout << "vecB : ";
	for(itB = vecB.begin(); itB != vecB.end(); itB++)
	{
		cout << *itB << " ";
	}
	cout << endl;


    vector<int> vecC(5);
    vector<int>::iterator itC;
    generate(vecC.begin(), vecC.end(), Random(1000,1020));
	cout << "vecC : ";
	for(itC = vecC.begin(); itC != vecC.end(); itC++)
	{
		cout << *itC << " ";
	}
	cout << endl;


	for(vector<ClassA>::iterator it = vecA.begin(); it != vecA.end(); it++)
	{
		cout << "for_loop : " << it->memberA << endl;
	}

	cout << "====================" << endl;

	for_each(vecA.begin(), vecA.end(), function_pointer);

	cout << "====================" << endl;

	for_each(vecA.begin(), vecA.end(), Functor("A"));

	cout << "====================" << endl;

	for_each(vecA.begin(), vecA.end(), Functor("B"));

	cout << "====================" << endl;

	 itA = find(vecA.begin(), vecA.end(), ClassA(3));
	if(itA == vecA.end())
	{
		cout << "find : Not found 3 in the sequence !" << endl;
	}
	else
	{
		cout << "find : Found 3 in the sequence !" << endl;
	}

	itA = find(vecA.begin(), vecA.end(), ClassA(555));
	if(itA == vecA.end())
	{
		cout << "find : Not found 555 in the sequence !" << endl;
	}
	else
	{
		cout << "find : Found 555 in the sequence !" << endl;
	}

	cout << "====================" << endl;

	itB = find_if(vecB.begin(), vecB.end(), DivisibleBy(2));
	if(itB != vecB.end())
	{
		cout << "find_if : "<< *itB << " is divisible By 2 and in the sequence!" << endl;
	}
	else
	{
		cout << "find_if : "<< " Not found any number divisible By 2 and in the sequence!" << endl;
	}

	cout << "====================" << endl;

    if (any_of(vecB.begin(), vecB.end(), DivisibleBy(2))) {
        cout << "any_of : At least one number is divisible by 2\n";
    }

    cout << "====================" << endl;

    int count_size = 0;
    count_size = count(vecB.begin(), vecB.end(),25);
    cout << "count : Found " << count_size << " occurances of 25 in the sequence !" << endl;

    cout << "====================" << endl;

    count_size = count_if(vecB.begin(), vecB.end(),DivisibleBy(5));
    cout << "count_if : Found " << count_size << " numbers divisible by 5 in the sequence !" << endl;

    cout << "====================" << endl;

    reverse(vecC.begin(),vecC.end());

    cout << "reverse : vecC after : ";
	for_each(vecC.begin(), vecC.end(), [](int n) {cout << n << " "; });
	cout << endl;

	cout << "====================" << endl;

	rotate(vecC.rbegin(),vecC.rbegin()+2,vecC.rend());
    cout << "rotate to right : vecC after : ";
	for_each(vecC.begin(),vecC.end(),Print());
	cout << endl;

	rotate(vecC.begin(),vecC.begin()+2,vecC.end());
    cout << "rotate to left : vecC after : ";
	for_each(vecC.begin(),vecC.end(),Print());
	cout << endl;

	cout << "====================" << endl;

	partition(vecC.begin(), vecC.end(), [](int i){return i % 2 == 0;});
    cout << "partition : vecC after : ";
	//for_each(vecC.begin(),vecC.end(),Print());
	copy(vecC.begin(), vecC.end(), ostream_iterator<int>(std::cout, " "));
	cout << endl;

	cout << "====================" << endl;

	sort(vecC.begin(), vecC.end());
	cout << "sort : vecC after : ";
	for_each(vecC.begin(),vecC.end(),Print());
	cout << endl;

	return 1;
}
