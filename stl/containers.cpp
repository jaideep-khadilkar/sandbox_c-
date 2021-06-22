
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Job
{
public :
	Job(string input_name,int input_submit_time,float input_priority=0)
	:name(input_name),submit_time(input_submit_time),priority(input_priority)
	{}

	friend bool operator< (const Job& lhs, const Job& rhs)
	{
		if (lhs.priority < rhs.priority)
			return true;

		if (lhs.priority == rhs.priority)
		{
			return lhs.submit_time >= rhs.submit_time;
		}

		//lhs.priority > rhs.priority
		return false;
	}
	string name;
	int submit_time;
	float priority;
};

class JobCompare
{
public:
	// Is JobA less in priority than JobB ?
	bool operator()(const Job& jobA,const Job& jobB)
	{
		if(jobA.priority < jobB.priority)
			return true;

		if(jobA.priority == jobB.priority)
		{
			return jobA.submit_time >= jobB.submit_time;
		}

		//jobA.priority > jobB.priority
		return false;
	}
};

int main()
{
	queue<int> qA;
	qA.push(10);
	qA.push(1);
	qA.push(200);
	qA.push(7);
	qA.push(300);
	while(!qA.empty())
	{
		cout << qA.front() << endl;
		qA.pop();
	}

	cout << "====================" << endl;

	priority_queue<int> pqA;
	pqA.push(10);
	pqA.push(1);
	pqA.push(200);
	pqA.push(7);
	pqA.push(300);
	while(!pqA.empty())
	{
		cout << pqA.top() << endl;
		pqA.pop();
	}

	cout << "====================" << endl;

	queue<Job> qB;
	qB.push(Job("render_A",1));
	qB.push(Job("render_B",2,10));
	qB.push(Job("render_C",3,-1));
	qB.push(Job("render_D",4));
	qB.push(Job("render_E",5,11.5));
	qB.push(Job("render_F",6));
	while(!qB.empty())
	{
		cout << qB.front().name << " : priority " << qB.front().priority << " : submit_time : " << qB.front().submit_time << endl;
		qB.pop();
	}

	cout << "====================" << endl;

	//priority_queue<Job,vector<Job>,JobCompare> pqB;
	priority_queue<Job> pqB;
	pqB.push(Job("render_A",1));
	pqB.push(Job("render_B",2,10));
	pqB.push(Job("render_C",3,-1));
	pqB.push(Job("render_D",4));
	pqB.push(Job("render_E",5,11.5));
	pqB.push(Job("render_F",6));
	while(!pqB.empty())
	{
		auto top = pqB.top();
		cout << top.name << " : priority " << top.priority << " : submit_time : " << top.submit_time << endl;
		pqB.pop();
	}

	cout << "====================" << endl;
}
