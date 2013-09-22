#include <iostream>
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
 
 
class EventQueue
{
    public:
        BankEvent* data;
        EventQueue* next;
        BankEvent getData();
        EventQueue getNext();
        int insert(BankEvent* e);
        int hasNext();
        EventQueue(BankEvent* e)
        {
            data = e;
            next = NULL;
        }
};
 
BankEvent EventQueue::getData()
{
    return *data;
}
 
EventQueue EventQueue::getNext()
{
    return *next;
}
 
int EventQueue::insert(BankEvent* e)
{
    if (e->getTime() < getData().getTime())
    {
        BankEvent* t = data;
        data = e;
        return insert(t);
    }
    EventQueue* th = new EventQueue(e);
    if(next == NULL)
    {
        next = th;
        return 1;
    }
    else
    {
        next->insert(e);
        return 2;
    }
    return 0;
}
 
int EventQueue::hasNext()
{
    return next != NULL;
}
 
 
 
 
 
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
}