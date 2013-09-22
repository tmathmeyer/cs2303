#include <iostream>
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

class node
{
    public: 
        node* next;
        BankEvent data;
        node(BankEvent d);
        void append(BankEvent d);
};






node::node(BankEvent d)
{
    data = d;
    next = NULL;
}


void node::append(BankEvent d)
{
    node nw = node(d);
    if(next==NULL)
        next = &nw;
    else
    {
        node *n = next;
        while((*n).next!=NULL)
        {
            n = (*n).next;
        }
        (*n).next = &nw;
    }
}


int main()
{
    BankEvent a;
    BankEvent b;
    BankEvent c;

    a.setTime(1);
    b.setTime(3);
    c.setTime(32);

    node n = node(a);
    n.append(b);
    n.append(c);
    n = *(n.next);
    cout<< n.data.getTime() << '\n';
    n = *(n.next);
    cout<< n.data.getTime() << '\n';
}