/*
two's complement

- borrowing mechanism
- N-bit, extra bits are ignored(no matter adding or borrowing)
- adding mechanism

*/

#include <iostream>

using namespace std;

int main()
{
    int a = 0xF; // 0000 1111, 15
    cout << a << endl;
    cout << ~a << endl; // 1111 0000,

//    int a, b;
//    const int L = 10;
//    // (a + b) * 2 = L;
//    int s;
//
//    s = a * (L/2 - a);

    return 0;
}
