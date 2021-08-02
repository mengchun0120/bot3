#ifndef INCLUDED_COMMONLIB_OBJECT_POOL_H
#define INCLUDED_COMMONLIB_OBJECT_POOL_H

#include <memory>
#include <functional>
#include <commonlib_exception.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class ObjectPool {
public:
    ObjectPool(unsigned int size);

    std::shared_ptr<T> alloc();

    int freeCount() const
    {
        return freeCount_;
    }

private:
    void initDeleter();

    void initPool(unsigned int size);

    void initNext(unsigned int size);

private:
    std::function<void(T*)> deleter_;
    T* pool_;
    T* upper_;
    std::size_t size_;
    int* next_;
    int firstFree_;
    int freeCount_;
};

template <typename T>
ObjectPool<T>::ObjectPool(unsigned int size)
{
    if (size == 0)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid size: " + std::to_string(size));
    }

    initPool(size);
    initNext(size);
    initDeleter();
}

template <typename T>
void ObjectPool<T>::initDeleter()
{
    deleter_ = [this](T* t)
    {
        if (t < pool_ || t > upper_)
        {
            THROW_EXCEPT(MemoryException, "Invalid pointer for object pool");
        }

        int idx = t - pool_;
        next_[idx] = firstFree_;
        firstFree_ = idx;
        ++freeCount_;
    };
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

template <typename T>
std::shared_ptr<T> ObjectPool<T>::alloc()
{
    std::shared_ptr<T> p;

    if (firstFree_ < 0)
    {
        p.reset(new T());
    }
    else
    {
        p.reset(&pool_[firstFree_], deleter_);
        firstFree_ = next_[firstFree_];
        --freeCount_;
    }

    return p;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

