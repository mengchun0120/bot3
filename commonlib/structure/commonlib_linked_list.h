#ifndef INCLUDED_COMMOLIB_LINKED_LIST_H
#define INCLUDED_COMMOLIB_LINKED_LIST_H

#include <functional>
#include <commonlib_exception.h>
#include <commonlib_object.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class LinkedList: public Object {
public:
    using Deleter = typename std::function<void(T*)>;

public:
    LinkedList();

    LinkedList(const Deleter &deleter);

    ~LinkedList();

    void setDeleter(const Deleter &deleter);

    inline T *first();

    inline const T *first() const;

    inline T *last();

    inline const T *last() const;

    inline bool empty() const;

    inline unsigned int size() const;

    void pushFront(T *t);

    void pushBack(T *t);

    void insertAfter(T *ref, T* t);

    void insertBefore(T *ref, T* t);

    T *unlinkFront();

    T *unlinkBack();

    void unlink(T *t);

    void removeFront();

    void removeBack();

    void remove(T *t);

    void clear();

    T *get(int index);

private:
    void del(T *t);

private:
    Deleter deleter_;
    T *first_;
    T *last_;
    unsigned int size_;
};

template <typename T>
LinkedList<T>::LinkedList()
    : first_(nullptr)
    , last_(nullptr)
    , size_(0)
{
}

template <typename T>
LinkedList<T>::LinkedList(const Deleter &deleter)
    : deleter_(deleter)
    , first_(nullptr)
    , last_(nullptr)
    , size_(0)
{
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
void LinkedList<T>::setDeleter(const Deleter &deleter)
{
    deleter_ = deleter;
}

template <typename T>
T *LinkedList<T>::first()
{
    return first_;
}

template <typename T>
const T *LinkedList<T>::first() const
{
    return first_;
}

template <typename T>
T *LinkedList<T>::last()
{
    return last_;
}

template <typename T>
const T *LinkedList<T>::last() const
{
    return last_;
}

template <typename T>
bool LinkedList<T>::empty() const
{
    return size_ == 0;
}

template <typename T>
unsigned int LinkedList<T>::size() const
{
    return size_;
}

template <typename T>
void LinkedList<T>::pushFront(T *t)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "t is null");
    }

    t->setNext(first_);
    t->setPrev(nullptr);

    if (first_)
    {
        first_->setPrev(t);
    }
    else
    {
        last_ = t;
    }

    first_ = t;
    ++size_;
}

template <typename T>
void LinkedList<T>::pushBack(T *t)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "t is null");
    }

    t->setNext(nullptr);
    t->setPrev(last_);

    if (last_)
    {
        last_->setNext(t);
    }
    else
    {
        first_ = t;
    }

    last_ = t;
    ++size_;
}

template <typename T>
void LinkedList<T>::insertAfter(T *ref, T* t)
{
    if (ref)
    {
        if (ref->next())
        {
            ref->next()->setPrev(t);
        }
        else
        {
            last_ = t;
        }

        t->setNext(ref->next());
        t->setPrev(ref);
        ref->setNext(t);

        ++size_;
    }
    else
    {
        pushBack(t);
    }
}

template <typename T>
void LinkedList<T>::insertBefore(T *ref, T* t)
{
    if (ref)
    {
        if (ref->prev())
        {
            ref->prev()->setNext(t);
        }
        else
        {
            first_ = t;
        }

        t->setNext(ref);
        t->setPrev(ref->prev());
        ref->setPrev(t);

        ++size_;
    }
    else
    {
        pushFront(t);
    }
}

template <typename T>
T *LinkedList<T>::unlinkFront()
{
    if (empty())
    {
        return nullptr;
    }

    T *tmp = first_;

    if (first_ != last_)
    {
        first_ = static_cast<T*>(first_->next());
        first_->setPrev(nullptr);
    }
    else
    {
        first_ = nullptr;
        last_ = nullptr;
    }

    --size_;
    tmp->setNext(nullptr);

    return tmp;
}

template <typename T>
T *LinkedList<T>::unlinkBack()
{
    if (empty())
    {
        return nullptr;
    }

    T *tmp = last_;

    if (first_ != last_)
    {
        last_ = static_cast<T*>(last_->prev());
        last_->setNext(nullptr);
    }
    else
    {
        first_ = nullptr;
        last_ = nullptr;
    }

    --size_;
    tmp->setPrev(nullptr);

    return tmp;
}

template <typename T>
void LinkedList<T>::unlink(T *t)
{
    if (empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "List is empty");
    }

    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "t is null");
    }

    if (t->prev())
    {
        t->prev()->setNext(t->next());
    }
    else
    {
        first_ = static_cast<T*>(t->next());
    }

    if (t->next())
    {
        t->next()->setPrev(t->prev());
    }
    else
    {
        last_ = static_cast<T*>(t->prev());
    }

    t->setPrev(nullptr);
    t->setNext(nullptr);
    --size_;
}

template <typename T>
void LinkedList<T>::removeFront()
{
    T *t = unlinkFront();
    if (t)
    {
        del(t);
    }
}

template <typename T>
void LinkedList<T>::removeBack()
{
    T *t = unlinkBack();
    if (t)
    {
        del(t);
    }
}

template <typename T>
void LinkedList<T>::remove(T *t)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "t is null");
    }

    unlink(t);
    del(t);
}

template <typename T>
void LinkedList<T>::clear()
{
    T *next;
    for (T *cur = first_; cur; cur = next)
    {
        next = static_cast<T*>(cur->next());
        del(cur);
    }

    first_ = nullptr;
    last_ = nullptr;
    size_ = 0;
}

template <typename T>
void LinkedList<T>::del(T *t)
{
    if (deleter_)
    {
        deleter_(t);
    }
    else
    {
        delete t;
    }
}

template <typename T>
T *LinkedList<T>::get(int index)
{
    T *t = first_;

    for(int i = 0; i < index && t; ++i)
    {
        t = t->next();
    }

    return t;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

