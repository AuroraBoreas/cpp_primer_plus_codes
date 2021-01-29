/*

SL_c++_auxiliary functions

P134

*/

#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <tuple>
#include "car.h"
#include "animal.h"
#include "dog.h"

using namespace std;

inline bool int_ptr_less(int* a, int* b)
{
    return (*a < *b);
}

void SwapNumbers(int& a, int& b)
{
    int tmp = b;
    b = a;
    a = tmp;
}

int& Add(int& a, int& b)
{
    static int tmp = a + b;
    return tmp;
}

class MyClass
{
private:
    int* m_x;
    int* m_y;
public:
    MyClass(int* x, int* y)
    : m_x(x), m_y(y)
    {}
    void increment(void)
    {
        m_x++; m_y++;
    }
    void decrement(void)
    {
        m_x--; m_y--;
    }
    void display(void) const
    {
        std::cout << "x = " << m_x << ", y = " << m_y << std::endl;
    }
};

struct Person
{
    std::string m_name;
    int m_age;

    Person(const std::string& name = "noname", int age = 1)
    : m_name(name), m_age(age)
    {}

    void display(void) const
    {
        std::cout << "name: " << m_name << ", age: " << m_age << std::endl;
        std::cout << std::endl;
    }
};

void sendAPerson(Person& p)
{
    p.m_age = 99;

    p = Person("nikki", 99); // this is final
}

void sendAPerson(Person* p)
{
    p->m_age = 999; // only this is changed
    p = new Person("nikki", 999); // no effect on arg p
}

inline void print(void)
{
    ;
}

template<typename T, typename...Types>
inline void print(const T& t1, const Types&... args)
{
    std::cout << t1 << std::endl;
    print(args...);
}

template<typename...Types>
inline int GetNumberOfVariadicArgs(const Types&... args)
{
    constexpr std::size_t n = sizeof...(Types);
    return n;
}

int main()
{
    // processing the min and max
    {
        /*
        + header file: <algorithm>

        + operation                 effect
        min(a, b)
        min(a, b, cmp)

        min(initlist)
        min(initlist, cmp)

        max(a, b)
        max(a, b, cmp)

        max(initlist)
        max(initlist, cmp)

        minmax(a, b)
        minmax(a, b, cmp)
        minmax(initlist)
        minmax(initlist, cmp)

        + definition
            namespace std
            {
                template<typename T>
                const t& min(const T& a, const T& b);

                template<typename T>
                T min(initializer_list<T> initlist);

                ...

            + note: definitions of min() and max() require that both types math
                - but explicitly qualified type of template args works

            }

        */

        int x = 17,
            y = 42,
            z = 33;
        int *px = &x,
            *py = &y,
            *pz = &z;

        // max()
        int* pmax = std::max(px, py, int_ptr_less);
        std::cout << *pmax << std::endl;

        // minmax()
        std::pair<int*, int*> extremes = std::minmax({px, py, pz}, int_ptr_less);
        std::cout << *extremes.first << " " << *extremes.second << std::endl;

        // explicitly qualified template args
        int i = 6;
        long j = 3L;
        // std::max(i, j); // not OK
        std::max<long>(i, j); // OK
    }

    // swapping two values, P137
    {
        /*

        + definition
            namespace std
            {
                // ... is used to provide an exception specification
                template<typename T>
                inline void swap(T&a, T&b) ...
                {
                    T tmp(std::move(a)); // rvalue ref, unconditionally move
                    a = std::move(b);    // rvalue ref
                    b = std::move(tmp);
                }

                // overload for arrays
                template<typename T, size_t N>
                void swap(T(&a)[N], T(&b)[N]) noexcept(noexcept(swap(*a, *b)));
            }

        */

        int x = 6, y = 42;
        std::swap(x, y);
        std::cout << x << ", " << y << std::endl;

    }

    // string is mutable in C++
    {

        std::string s1 = "Zhang Liang";

        s1[0] = 'S';

        std::cout << s1 << std::endl;

    }

    // ref as args, or return_value
    {
        int x = 12,
            y = 42;

        std::cout << "before: x = " << x << ", y = " << y << std::endl;
        SwapNumbers(x, y);
        std::cout << "after: x = " << x << ", y = " << y << std::endl;

        std::cout << Add(x, y) << std::endl;
    }

    // classes are always reference types in C++?
    {
        int x = 2, y = 3;
        MyClass* a = new MyClass(&x, &y);
        std::shared_ptr<MyClass> b(a);
        std::cout << "before increment: " << std::endl;
        a->display();
        b->display();
        std::cout << "after increment: " << std::endl;
        a->increment();
        a->display();
        b->display();
        delete a;
    }

    // passing by ref or pointer
    {
        Person p1 = Person("ZL", 35);
        std::cout << "before passing by ref\n";
        p1.display();
        sendAPerson(p1);
        std::cout << "after passing by ref\n";
        p1.display();

        Person* ptr = new Person("ZL", 35);
        std::cout << "before passing by ptr\n";
        ptr->display();
        sendAPerson(ptr);
        std::cout << "after passing by ptr\n";
        ptr->display();
    }

    // pair<>, tuple<>
    {
        std::pair<int, float> t1{42, 3.14};
        std::cout << t1.first << ", " << t1.second << std::endl;
        // or
        int a; float b;

        std::make_pair(std::ref(a), std::ref(b)) = t1;
        std::cout << a << ", " << b << std::endl;

        std::tuple<char, short, int, long, float, double, std::string> tp1{'a', 6, 42, 123L, 3.14f, 2.718, "hello"};
        char c; short s; int i;
        long l; float f; double d;
        std::string str;

        std::tie(c, s, i, l, f, d, str) = tp1;

        std::cout << c << ", "
                  << s << ", "
                  << i << ", "
                  << l << ", "
                  << f << ", "
                  << d << ", "
                  << str << std::endl;
    }

    // variadic template
    {

        print<char, short, int, long, float, double, std::string>('a', 12, 42, 123L, 3.14f, 2.718, "hello");

        // numbers of variadic args
        // using `constexpr std::size_t n = sizeof...(T);`
        int n = GetNumberOfVariadicArgs(2, 3.14, 2.718, 52.9);
        std::cout << "\nvariadic args have " << n << " args." << std::endl;

    }

    // constructor chaining in C#, or using constructor delegation in C++
    {
        /*

        + concept:
            - reduce code to enhance readability

        + syntax: constructor(...): constructor(...);

        + delegate sequence:

            ```c++
            constructor1(...){}
            constructor2(...): constructor1(...) { // member initializer; }

            ```

             You can��t do member initialization in a constructor that delegates to another constructor.

             - why: it falls into same hole of members initialization.. same pattern

        */


        Car myCar = Car("Toyota", 100);
        myCar.display();
    }

    // static kw in c++
    {
        std::cout << std::endl;
        Animal a1 = Animal();
        Animal a2 = Animal();
        Animal a3 = Animal();
        std::cout << a1.GetCounter() << std::endl;
        std::cout << a2.GetCounter() << std::endl;
        std::cout << a3.GetCounter() << std::endl;

    }

    // const data member?
    {
        Dog d1 = Dog(3); // can be compiled?

        d1.display();
        // cls-lvD:\Reference_01_code\C++\cpp_08_C++STL\src_code\SL-05-Utilities\SL_c++_auxiliary_functions\car.hl access?
//        std::cout << Dog.m_name << std::endl; // ofc NOT OK
        std::cout << d1.m_name << std::endl;  // obj-lvl OK
        // changeable?
//        d1.m_name = "SCY";  // not OK

    }

















    return 0;
}
