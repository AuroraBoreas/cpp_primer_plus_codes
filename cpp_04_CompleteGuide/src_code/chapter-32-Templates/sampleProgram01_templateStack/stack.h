#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

template<class T>
class Stack
{
private:
    T* basePtr;
    int tip;
    int max;
public:
    Stack(int n)
    {
        basePtr = new T[n];
        max = n;
        tip = 0;
    }
    ~Stack() { delete[] basePtr; }

    Stack<T>& operator=(const Stack<T>&);

    bool empty(){ return (tip==0); }
    bool push(const T& x)
    {
        if(tip < max-1)
        {
            basePtr[tip++] = x; return true;
        }
        else
            return false;
    }
    bool pop(T& x)
    {
        if(tip>0)
        {
            x = basePtr[tip--]; return true;
        }
        else
            return false;
    }
};

#endif // STACK_H_INCLUDED
