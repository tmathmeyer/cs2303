#include <stdlib.h>


class EventQueue;

//parent class for events
class BankEvent
{
    private: 
        int time;
    public:
        int getTime();
        int setTime(int t);
        BankEvent();
        void onCompletion(EventQueue* eq);
};

//subclass for teller-based events
class TellerEvent : public BankEvent
{};

//sub class for customer-based events
class CustomerEvent : public BankEvent
{};








//a sorted queue of events
//THIS SHOULD BE A HEAP >.<
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






























//Functions for Events
int BankEvent::getTime()
{
    return time;
}
int BankEvent::setTime(int t)
{
    return time = t;
}
BankEvent::BankEvent()
{
    time = 0;
}









//Queue functions
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
