// instr1.cpp -- reading more than one string
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    const int ArSize = 20;
    char name[ArSize];
    char dessert[ArSize];

    cout << "Enter your name:\n";
    cin  >> name;
    cout << "Enter your favorite dessert:\n";
    cin  >> dessert;
    cout << "I have some delicious " << dessert;
    cout << " for you, " << name << ".\n";

    return 0;
}
