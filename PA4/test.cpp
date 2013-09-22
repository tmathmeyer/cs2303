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

    cout << q.getData().getTime() << endl;
    cout << q.getNext().getData().getTime() << endl;
    cout << q.getNext().getNext().getData().getTime() << endl;
    cout << q.getNext().getNext().getNext().getData().getTime() << endl;
    cout << q.getNext().getNext().getNext().getNext().getData().getTime() << endl;
    cout << q.getNext().getNext().getNext().getNext().getNext().getData().getTime() << endl;
    cout << q.getNext().getNext().getNext().getNext().getNext().getNext().getData().getTime() << endl;
    cout << q.getNext().getNext().getNext().getNext().getNext().getNext().getNext().getData().getTime() << endl;
    cout << q.getNext().getNext().getNext().getNext().getNext().getNext().getNext().getNext().getData().getTime() << endl;
}