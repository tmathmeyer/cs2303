#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class BankEvent
{
	private: 
		int time;
	public:
		int getTime()
		{
			return time;
		}
		int setTime(int t)
		{
			return time = t;
		}
		BankEvent()
		{
			time = 0;
		}
};


class SortedEventQueue
{
	private:
		BankEvent* data;
		SortedEventQueue* next;
	public:
		BankEvent getData();
		SortedEventQueue getNext();
		int isEmpty();
		int hasNext();
		int insert(BankEvent e);
		SortedEventQueue()
		{
			data = 0;
			next = 0;
		}
};


int SortedEventQueue::isEmpty()
{
	return &data == 0;
}

int SortedEventQueue::insert(BankEvent e)
{
	if (data == 0)
	{
		*data = e;
		return 0;
	}
	else
	{
		int a = getData().getTime();
		int b = e.getTime();
		if (a < b)
		{
			BankEvent* temp = data;
			*data = e;
			insert(*temp);
			return 1;
		}
		else if (next == 0)
		{
			next = new SortedEventQueue;
			next->insert(e);
			return 2;
		}
		else
		{
			next->insert(e);
			return 3;
		}	
	}
}	

int SortedEventQueue::hasNext()
{
	return next != 0;
}

BankEvent SortedEventQueue::getData()
{
	return *data;
}

SortedEventQueue SortedEventQueue::getNext()
{
	if (hasNext())
	{
		return *next;
	}
	else
	{
		return *(new SortedEventQueue());
	}
}


int main()
{
	srand (time(NULL));
	SortedEventQueue seq;
	//for(int i = 0; i < 20; i++)
	//{
//		BankEvent* be = new BankEvent();
//		cout << be->setTime(rand() % 100) << " ";
//		cout << seq.insert(*be) << endl;
//	}

	BankEvent a;
	BankEvent b;
	BankEvent c;
	BankEvent d;

	//cout << a.setTime(5) << " " << seq.insert(a) << endl;
	a.setTime(5);
	seq.insert(a);

	b.setTime(34);
	seq.insert(b);
	
	
	//cout << b.setTime(34) << " " << seq.insert(b) << endl;

	//cout << c.setTime(2) << " " << seq.insert(c) << endl;

	//cout << d.setTime(3) << " " << seq.insert(d) << endl;

	while(! seq.isEmpty())
	{
		cout << seq.getData().getTime() << endl;
		seq = seq.getNext();
	}
}
