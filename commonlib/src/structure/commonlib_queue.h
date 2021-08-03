#ifndef INCLUDED_COMMONLIB_QUEUE_H
#define INCLUDED_COMMONLIB_QUEUE_H

#include <commonlib_exception.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class Queue {
public:
    Queue(unsigned int capacity);

    virtual ~Queue();

    bool full() const
    {
        return size_ == capacity_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    bool peek(T& t);

    bool enqueue(const T& t);

    bool dequeue(T& t);

    int size() const
    {
        return size_;
    }

    int capacity() const
    {
        return capacity_;
    }

private:
    T* queue_;
    int capacity_;
    int size_;
    int first_;
    int free_;
};

template <typename T>
Queue<T>::Queue(unsigned int capacity)
{
    if (capacity == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid capacity");
    }

    queue_ = new T[capacity];
    size_ = 0;
    capacity_ = capacity;
    first_ = -1;
    free_ = 0;
}

template <typename T>
Queue<T>::~Queue()
{
    delete[] queue_;
}

template <typename T>
bool Queue<T>::peek(T& t)
{
    if (empty())
    {
        return false;
    }

    t = queue_[first_];
    return true;
}

template <typename T>
bool Queue<T>::enqueue(const T& t)
{
    if (full())
    {
        return false;
    }

    if (first_ == -1)
    {
        first_ = 0;
        queue_[0] = t;
    }
    else
    {
        queue_[free_] = t;
    }

    free_ = (free_ + 1) % capacity_;
    ++size_;

    return true;
}

template <typename T>
bool Queue<T>::dequeue(T& t)
{
    if (empty())
    {
        return false;
    }

    t = queue_[first_];
    --size_;

    if (size_ > 0)
    {
        first_ = (first_ + 1) % capacity_;
    }
    else
    {
        first_ = -1;
        free_ = 0;
    }

    return true;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

