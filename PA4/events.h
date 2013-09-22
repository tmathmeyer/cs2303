#include <stdlib.h>

//parent class for events
class BankEvent
{
    private: 
        int time;
    public:
        int getTime();
        int setTime(int t);
        BankEvent();
        void onCompletion(EventQueue* eq, int v, int clock);
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