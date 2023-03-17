#ifndef INCLUDED_COMMONLIB_LINKED_ITEM_H
#define INCLUDED_COMMONLIB_LINKED_ITEM_H

#include <utility>

namespace mcdane {
namespace commonlib {

template <typename T>
class LinkedItem {
public:
    LinkedItem();

    template <typename... A>
    LinkedItem(A&&... args);

    ~LinkedItem() = default;

    inline LinkedItem *next();

    inline const LinkedItem *next() const;

    inline LinkedItem *prev();

    inline const LinkedItem *prev() const;

    inline T &item();

    inline const T &item() const;

    void setNext(LinkedItem *n);

    void setPrev(LinkedItem *p);

    template <typename... A>
    void setItem(A&&... args);

private:
    LinkedItem *next_;
    LinkedItem *prev_;
    T item_;;
};

template <typename T>
LinkedItem<T>::LinkedItem()
    : next_(nullptr)
    , prev_(nullptr)
    , item_()
{
}

template <typename T>
template <typename... A>
LinkedItem<T>::LinkedItem(A&&... args)
    : next_(nullptr)
    , prev_(nullptr)
    , item_(std::forward<A>(args)...)
{
}

template <typename T>
LinkedItem<T> *LinkedItem<T>::next()
{
    return next_;
}

template <typename T>
const LinkedItem<T> *LinkedItem<T>::next() const
{
    return next_;
}

template <typename T>
LinkedItem<T> *LinkedItem<T>::prev()
{
    return prev_;
}

template <typename T>
const LinkedItem<T> *LinkedItem<T>::prev() const
{
    return prev_;
}

template <typename T>
T &LinkedItem<T>::item()
{
    return item_;
}

template <typename T>
const T &LinkedItem<T>::item() const
{
    return item_;
}

template <typename T>
void LinkedItem<T>::setNext(LinkedItem<T> *n)
{
    next_ = n;
}

template <typename T>
void LinkedItem<T>::setPrev(LinkedItem<T> *p)
{
    prev_ = p;
}

template <typename T>
template <typename... A>
void LinkedItem<T>::setItem(A&&... args)
{
    new (&item_) T(std::forward<A>(args)...);
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif
