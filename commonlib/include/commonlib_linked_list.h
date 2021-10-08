#ifndef INCLUDED_COMMOLIB_LINKED_LIST_H
#define INCLUDED_COMMOLIB_LINKED_LIST_H

#include <memory>

namespace mcdane {
namespace commonlib {

template <typename T>
class DefaultDeleter {
public:
    DefaultDeleter() = default;

    ~DefaultDeleter() = default;

    inline void operator()(T* t);

public:
    static DefaultDeleter k_instance;
};

template <typename T>
DefaultDeleter<T> DefaultDeleter<T>::k_instance;

template <typename T>
void DefaultDeleter<T>::operator()(T* t)
{
    delete t;
}

template <typename T, typename DELETER=DefaultDeleter<T>>
class LinkedList {
public:
    LinkedList(DELETER& deleter=DefaultDeleter<T>::k_instance);

    ~LinkedList();

    inline T* first();

    inline const T* first() const;

    inline bool empty() const;

    void add(T* t);

    void remove(T* prev, T* t);

    void clear();

private:
    DELETER& deleter_;
    T* first_;
};

template <typename T, typename DELETER>
LinkedList<T,DELETER>::LinkedList(DELETER& deleter)
    : deleter_(deleter)
    , first_(nullptr)
{
}

template <typename T, typename DELETER>
LinkedList<T,DELETER>::~LinkedList()
{
    clear();
}

template <typename T, typename DELETER>
T* LinkedList<T,DELETER>::first()
{
    return first_;
}

template <typename T, typename DELETER>
const T* LinkedList<T,DELETER>::first() const
{
    return first_;
}

template <typename T, typename DELETER>
bool LinkedList<T,DELETER>::empty() const
{
    return first_ == nullptr;
}

template <typename T, typename DELETER>
void LinkedList<T,DELETER>::add(T* t)
{
    t->setNext(first_);
    first_ = t;
}

template <typename T, typename DELETER>
void LinkedList<T,DELETER>::remove(T* prev, T* t)
{
    if (t == first_)
    {
        first_ = t->next();
    }
    else
    {
        prev->setNext(t->next());
    }

    deleter_(t);
}

template <typename T, typename DELETER>
void LinkedList<T,DELETER>::clear()
{
    T* next;
    for (T* cur = first_; cur; cur = next)
    {
        next = cur->next();
        deleter_(cur);
    }

    first_ = nullptr;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

