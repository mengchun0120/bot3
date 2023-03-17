#ifndef INCLUDED_COMMONLIB_OBJECT_POOL_H
#define INCLUDED_COMMONLIB_OBJECT_POOL_H

#include <functional>
#include <commonlib_exception.h>

namespace mcdane {
namespace commonlib {

template <typename T>
using Deleter = std::function<void(T*)>;

template <typename T>
class ObjectPool {
public:
    ObjectPool();

    ObjectPool(unsigned int size);

    virtual ~ObjectPool();

    void init(unsigned int size);

    template <typename INITFUNC>
    void init(unsigned int size, INITFUNC f);

    template <typename... Args>
    T *alloc(Args&&... args);

    void free(T *t);

    inline int freeCount() const;

    inline Deleter<T> &deleter();

private:
    void initDeleter();

    void initPool(unsigned int size);

    void initNext(unsigned int size);

private:
    T *pool_;
    T *upper_;
    std::size_t size_;
    int *next_;
    int firstFree_;
    int freeCount_;
    Deleter<T> deleter_;
};

template <typename T>
ObjectPool<T>::ObjectPool()
    : pool_(nullptr)
    , upper_(nullptr)
    , size_(0)
    , next_(nullptr)
    , firstFree_(-1)
    , freeCount_(0)
{
    initDeleter();
}

template <typename T>
ObjectPool<T>::ObjectPool(unsigned int size)
{
    initDeleter();
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
template <typename INITFUNC>
void ObjectPool<T>::init(unsigned int size, INITFUNC f)
{
    init(size);

    for (unsigned int i = 0; i < size; ++i)
    {
        f(pool_[i]);
    }
}

template <typename T>
template <typename... Args>
T *ObjectPool<T>::alloc(Args&&... args)
{
    T *t;

    if (firstFree_ < 0)
    {
        t = new T(std::forward<Args>(args)...);
    }
    else
    {
        t = &pool_[firstFree_];
        new (t) T(std::forward<Args>(args)...);
        firstFree_ = next_[firstFree_];
        --freeCount_;
    }

    return t;
}

template <typename T>
void ObjectPool<T>::free(T *t)
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
int ObjectPool<T>::freeCount() const
{
    return freeCount_;
}

template <typename T>
Deleter<T> &ObjectPool<T>::deleter()
{
    return deleter_;
}

template <typename T>
void ObjectPool<T>::initDeleter()
{
    using namespace std::placeholders;

    deleter_ = std::bind(&ObjectPool::free, this, _1);
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

