
// Note that I am growing the queue when we head reaches the end.
// No looping-around is being done. 
// Another valid solution is when we do a linear shift back on deleting elements
// However, this provides no meaningful improvement in time complexity.


#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty()
{
    return size() == 0;
}

template <typename T> bool DynamicQueue<T> :: isFull()
{
    return tail == N;
}

template <typename T> void DynamicQueue<T> :: grow()
{
    if(isFull())
    {
        unsigned int old_size = N;
        N = nextSize();
        T* new_queue = new T[N];

        for(int i=0;i<old_size;i++)
        {
            new_queue[i] = A[i];
        }
        delete[] A;
        A = new_queue;
    }
    else
    return;
}

template <typename T> unsigned int DynamicQueue<T> :: size()
{
    return tail - head;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x)
{
    if(isFull())
    grow();
    
    A[tail] = x;
    tail ++;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x)
{
    if(isEmpty())
    return false;
    *x = A[head];
    head ++;
    return true;
}
