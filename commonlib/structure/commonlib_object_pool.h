#ifndef INCLUDED_COMMONLIB_OBJECT_POOL_H
#define INCLUDED_COMMONLIB_OBJECT_POOL_H

#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class ObjectPool {
public:
    ObjectPool();

    ObjectPool(unsigned int size);

    virtual ~ObjectPool();

    void init(unsigned int size);

    T* alloc();

    void free(T* t);

    int freeCount() const
    {
        return freeCount_;
    }

private:
    void initPool(unsigned int size);

    void initNext(unsigned int size);

private:
    T* pool_;
    T* upper_;
    std::size_t size_;
    int* next_;
    int firstFree_;
    int freeCount_;
};

template <typename T>
ObjectPool<T>::ObjectPool()
    : pool_(nullptr)
    , upper_(nullptr)
    , size_(0)
    , next_(nullptr)
{
}

template <typename T>
ObjectPool<T>::ObjectPool(unsigned int size)
{
    init(size);
}

template <typename T>
ObjectPool<T>::~ObjectPool()
{
    delete[] pool_;
    delete[] next_;
}

template <typename T>
void ObjectPool<T>::init(unsigned int size)
{
    if (size == 0)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid size: " + std::to_string(size));
    }

    initPool(size);
    initNext(size);
}

template <typename T>
T* ObjectPool<T>::alloc()
{
    T* t;

    if (firstFree_ < 0)
    {
        t = new T();
    }
    else
    {
        t = &pool_[firstFree_];
        firstFree_ = next_[firstFree_];
        --freeCount_;
    }

    return t;
}

template <typename T>
void ObjectPool<T>::free(T* t)
{
    if (t < pool_ || t > upper_)
    {
        delete t;
    }
    else
    {
        int idx = t - pool_;
        next_[idx] = firstFree_;
        firstFree_ = idx;
        ++freeCount_;
    }
}

template <typename T>
void ObjectPool<T>::initPool(unsigned int size)
{
    size_ = size;
    pool_ = new T[size];
    upper_ = pool_ + (size-1);
    firstFree_ = 0;
    freeCount_ = size;
}

template <typename T>
void ObjectPool<T>::initNext(unsigned int size)
{
    next_ = new int[size];
    for (unsigned int i = 0; i < size - 1; ++i)
    {
        next_[i] = i+1;
    }
    next_[size-1] = -1;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

