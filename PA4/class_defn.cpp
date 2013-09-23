#include "events.h";

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
void BankEvent::onCompletion(EventQueue* eq, int v, int clock)
{
    //nothing here :D
}

void TellerEvent::onCompletion()
{
    

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

EventQueue(BankEvent* e);
{
    data = e;
    next = NULL;
}