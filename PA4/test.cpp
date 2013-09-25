#include "events.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

int* queues;
int  queuecount;
int  clck = 0;


void testQueue();
int getShortestLine();
int increment(int place);
int decriment(int place);
int getVal(int place);
void addUsers(EventQueue* eq, int cc, int max);


int main(){
    //testQueue();
    int max = 100;

    CustomerEvent* a = new CustomerEvent(0,0);
    a->setTime(rand() % max);
    EventQueue eq(a);

    //insert all customers as entering events
    addUsers(&eq, 99, max);

    //while(eventQueue.hasNext())
        //oncompletion the event, remove it
    while(eq.hasNext())
    {
        cout << eq.getData().getTime() << endl;
        BankEvent be = eq.getData();
        if (be.kty == 1)
        { //teller
            TellerEvent* te = &be;
            te->onCompletion(&eq);
        }
        else if (be.kty == 2)
        {
            CustomerEvent* ce = &be;
            ce->onCompletion(&eq);
        }
        eq = *(eq.next);
        getchar();
    }

    //run stats
    //???
    //profit





}



void TellerEvent::onCompletion(EventQueue* e)
{
    if (getVal(queue) == 0)
    { //there is nobody in line!
        TellerEvent* te = new TellerEvent(queue);
        int ra = clck+1+rand()%150;
        te->setTime(ra);
        e->insert(te);
        cout << "Due to lack of customers, a teller has gone idle!" << endl;
    }
    else
    { //there is a customer in line
        int avg;
        int ra = rand()%avg + clck;
        CustomerEvent* ce = new CustomerEvent(1, queue);
        ce->setTime(ra);
        e->insert(ce);
        cout << "a customer is being serviced by the bank" << endl;
    }
}

void CustomerEvent::onCompletion(EventQueue* e)
{
    if (type == 0)
    { //entering
        increment(getShortestLine());
        cout << "a new customer has entered" << endl;
    }
    else
    { //leaving
        TellerEvent* te = new TellerEvent(queue);
        te->setTime(clck);
        e->insert(te);
        cout << "a customer has left the bank" << endl;
    }
}

void BankEvent::onCompletion(EventQueue* e)
{
    cout << "this should never be called!" << endl;
}


int getShortestLine()
{
    int minVal= *queues;
    int minPla=0;
    for(int i = 1; i < queuecount; i++)
    {
        if (*(queues+i) < minVal)
        {
            minVal = *(queues+1);
            minPla = i;
        }
    }
    return minPla;
}

int increment(int place)
{
    queues[place]++;
    return getVal(place);
}

int decriment(int place)
{
    queues[place]--;
    return getVal(place);
}

int getVal(int place)
{
    return queues[place];
}







void addUsers(EventQueue* eq, int cc, int max)
{
    for(int i = 0; i < cc; i++)
    {
        int r = rand() % max;
        CustomerEvent* a = new CustomerEvent(0,0);
        a->setTime(r);
        eq->insert(a);
    }
}










void testQueue()
{
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
