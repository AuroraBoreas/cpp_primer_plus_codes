#include <iostream>
#include <queue>
#include "parcel.h"
using namespace std;

int main()
{
    priority_queue<Parcel> pq;
    pq.push(Parcel(7, "ZL"));
    pq.push(Parcel(1, "SCY"));
    pq.push(Parcel(4, "ZZ"));
    pq.push(Parcel(5, "LL"));

    while(!pq.empty())
    {
        cout << pq.top() << endl;
        pq.pop();
    }

    return 0;
}
