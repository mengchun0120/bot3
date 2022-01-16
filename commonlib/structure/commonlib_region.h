#ifndef INCLUDED_COMMONLIB_REGION_H
#define INCLUDED_COMMONLIB_REGION_H

#include <vector>
#include <sstream>
#include <ostream>
#include <commonlib_exception.h>
#include <commonlib_object.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class Region: public Object {
public:
    Region() = default;

    Region(const Region& other) = default;

    Region(std::initializer_list<T> i);

    Region(const std::vector<T>& v);

    Region(T left1,
           T right1,
           T bottom1,
           T top1);

    ~Region() = default;

    void init(T left1,
              T right1,
              T bottom1,
              T top1);

    inline T left() const;

    inline T right() const;

    inline T bottom() const;

    inline T top() const;

    inline void setLeft(T left1);

    inline void setRight(T right1);

    inline void setBottom(T bottom1);

    inline void setTop(T top1);

    Region& operator=(const Region& other);

    void shift(T deltaX,
               T deltaY);

    std::string toString() const override;

private:
    T left_;
    T right_;
    T bottom_;
    T top_;
};

template <typename T>
Region<T> shift(const Region<T>& r,
                T deltaX,
                T deltaY)
{
    return Region<T>(r.left() + deltaX,
                     r.right() + deltaX,
                     r.bottom() + deltaY,
                     r.top() + deltaY);
}

template <typename T>
Region<T>::Region(T left1,
                  T right1,
                  T bottom1,
                  T top1)
    : left_(left1)
    , right_(right1)
    , bottom_(bottom1)
    , top_(top1)
{
}

template <typename T>
Region<T>::Region(std::initializer_list<T> i)
{
    if (i.size() != 4)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Initializer-list has wrong size");
    }

    T t[4];
    int k = 0;

    for(auto it = i.begin(); it != i.end(); ++it, ++k)
    {
        t[k] = *it;
    }

    left_ = t[0];
    right_ = t[1];
    bottom_ = t[2];
    top_ = t[3];
}

template <typename T>
Region<T>::Region(const std::vector<T>& v)
{
    if (v.size() != 4)
    {
        THROW_EXCEPT(InvalidArgumentException, "v has wrong size");
    }

    left_ = v[0];
    right_ = v[1];
    bottom_ = v[2];
    top_ = v[3];
}

template <typename T>
void Region<T>::init(T left1,
                     T right1,
                     T bottom1,
                     T top1)
{
    left_ = left1;
    right_ = right1;
    bottom_ = bottom1;
    top_ = top1;
}

template <typename T>
T Region<T>::left() const
{
    return left_;
}

template <typename T>
T Region<T>::right() const
{
    return right_;
}

template <typename T>
T Region<T>::bottom() const
{
    return bottom_;
}

template <typename T>
T Region<T>::top() const
{
    return top_;
}

template <typename T>
void Region<T>::setLeft(T left1)
{
    left_ = left1;
}

template <typename T>
void Region<T>::setRight(T right1)
{
    right_ = right1;
}

template <typename T>
void Region<T>::setBottom(T bottom1)
{
    bottom_ = bottom1;
}

template <typename T>
void Region<T>::setTop(T top1)
{
    top_ = top1;
}

template <typename T>
Region<T>& Region<T>::operator=(const Region& other)
{
    left_ = other.left();
    right_ = other.right();
    bottom_ = other.bottom();
    top_ = other.top();
    return *this;
}

template <typename T>
void Region<T>::shift(T deltaX,
                      T deltaY)
{
    left_ += deltaX;
    right_ += deltaX;
    bottom_ += deltaY;
    top_ += deltaY;
}

template <typename T>
std::string Region<T>::toString() const
{
    std::ostringstream oss;

    oss << "Region(left=" << left_
        << ", right=" << right_
        << ", bottom=" << bottom_
        << ", top=" << top_
        << ", Base=" << Object::toString()
        << ")";

    return oss.str();
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

