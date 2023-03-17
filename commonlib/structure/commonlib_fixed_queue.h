#ifndef INCLUDED_COMMONLIB_FIXED_QUEUE_H
#define INCLUDED_COMMONLIB_FIXED_QUEUE_H

#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class FixedQueue {
public:
    FixedQueue();

    FixedQueue(unsigned int capacity);

    virtual ~FixedQueue();

    void init(unsigned int capacity);

    bool full() const
    {
        return size_ == capacity_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    bool peek(T &t);

    bool enqueue(const T &t);

    bool dequeue(T &t);

    void clear();

    int size() const
    {
        return size_;
    }

    int capacity() const
    {
        return capacity_;
    }

private:
    T *queue_;
    int capacity_;
    int size_;
    int first_;
    int free_;
};


template <typename T>
FixedQueue<T>::FixedQueue()
    : queue_(nullptr)
    , capacity_(0)
    , size_(0)
    , first_(-1)
    , free_(-1)
{
}

template <typename T>
FixedQueue<T>::FixedQueue(unsigned int capacity)
    : FixedQueue()
{
    init(capacity);
}

template <typename T>
FixedQueue<T>::~FixedQueue()
{
    delete[] queue_;
}

template <typename T>
void FixedQueue<T>::init(unsigned int capacity)
{
    if (capacity == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid capacity");
    }

    if (queue_)
    {
        delete[] queue_;
    }

    queue_ = new T[capacity];
    size_ = 0;
    capacity_ = capacity;
    first_ = -1;
    free_ = 0;
}

template <typename T>
bool FixedQueue<T>::peek(T &t)
{
    if (empty())
    {
        return false;
    }

    t = queue_[first_];
    return true;
}

template <typename T>
bool FixedQueue<T>::enqueue(const T &t)
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
bool FixedQueue<T>::dequeue(T &t)
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

template <typename T>
void FixedQueue<T>::clear()
{
    size_ = 0;
    first_ = -1;
    free_ = 0;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

