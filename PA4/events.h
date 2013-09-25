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
        int kty;
};

//subclass for teller-based events
class TellerEvent : public BankEvent
{
    public:
        int queue;
        void onCompletion(EventQueue* eq);
        TellerEvent(int q)
        {
            queue = q;
            kty = 1;
        }
};

//sub class for customer-based events
class CustomerEvent : public BankEvent
{
    public:
        int type; //0=entering, 1=leaving
        int queue;
        int getType()
        {
            return type;
        }
        void onCompletion(EventQueue* eq);
        CustomerEvent(int t, int q)
        {
            type = t;
            queue = q;
            kty = 2;
        }
};








//a sorted queue of events
//THIS SHOULD BE A HEAP >.<
class EventQueue
{
    public:
        BankEvent* data;
        EventQueue* next;
        BankEvent* getData();
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
BankEvent* EventQueue::getData()
{
    return data;
}
 
EventQueue EventQueue::getNext()
{
    return *next;
}

int EventQueue::insert(BankEvent* e)
{
    if (e->getTime() < getData()->getTime())
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
