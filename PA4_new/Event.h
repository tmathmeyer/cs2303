class BankEvent;

// the singly linked list
class EventQueue
{
    public:
        BankEvent* data;
        EventQueue* next;
        BankEvent* getData();
        EventQueue getNext();
        int insert(BankEvent* e);
        int hasNext();
        EventQueue (BankEvent* e);
};



class BankEvent
{
	public:
        virtual int  getTime()                    =0;
        virtual int  setTime(int t)               =0;
        virtual void onCompletion(EventQueue* eq) =0;
};


//sub class for teller based events
class TellerEvent : public BankEvent
{
	private:
		int queue; //the queue that the teller takes clients from
        int time;
    public:
    	int  getTime();
    	int  setTime(int t);
        void onCompletion(EventQueue* eq);
        int  getQueue() { return queue; }
        TellerEvent(int q)
        {
            queue = q;
        }
};

//sub class for customer-based events
class CustomerEvent : public BankEvent
{
	private:
		int type;   //0=entering, 1=leaving
		int queue;  //the queue the client is in
        int time;
    public:
        int getType () { return type;  }
        int getQueue() { return queue; }
        int getTime();
    	int setTime(int t);

        void onCompletion(EventQueue* eq);
        CustomerEvent(int t, int q, int i)
        {
            type = t;
            queue = q;
        }
};