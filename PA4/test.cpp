#include "events.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
    srand (time(NULL));
 
    BankEvent* a = new BankEvent();
    a->setTime(234);
    EventQueue q(a);


    for(int i = 0; i < 20; i++)
    {
        int r = rand() % 400;
        BankEvent* a = new BankEvent();
        a->setTime(r);
        q.insert(a);
    }


    while(q.hasNext())
    {
	    cout << q.getData().getTime() << endl;
	    q.getData().onCompletion(&q);
	    q = *(q.next);
    }
}



void BankEvent::onCompletion(EventQueue* e)
{
	if (rand()%2==0)
	{
		TellerEvent* be = new TellerEvent();
		be->setTime(rand()%200+getTime());
		e->insert(be);
		cout << "new event added!" << endl;
	}
}
