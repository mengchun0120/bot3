#ifndef INCLUDED_COMMONLIB_REGION_H
#define INCLUDED_COMMONLIB_REGION_H

#include <vector>
#include <sstream>
#include <ostream>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class Region {
public:
    Region() = default;

    Region(const Region &other) = default;

    Region(std::initializer_list<T> i);

    Region(const std::vector<T> &v);

    Region(T left1,
           T right1,
           T bottom1,
           T top1);

    ~Region() = default;

    void init(T left1,
              T right1,
              T bottom1,
              T top1);

    void init(const Region &other);

    void init(std::initializer_list<T> i);

    void init(const std::vector<T> &v);

    inline T left() const;

    inline T right() const;

    inline T bottom() const;

    inline T top() const;

    inline void setLeft(T left1);

    inline void setRight(T right1);

    inline void setBottom(T bottom1);

    inline void setTop(T top1);

    Region &operator=(const Region& other);

    void shift(T deltaX,
               T deltaY);

    bool contains(const T &x,
                  const T &y) const;

    template <typename F>
    void iterate(F &func,
                 T deltaX,
                 T deltaY);

private:
    T left_;
    T right_;
    T bottom_;
    T top_;
};

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
    init(i);
}

template <typename T>
Region<T>::Region(const std::vector<T> &v)
{
    init(v);
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
void Region<T>::init(const Region &other)
{
    left_ = other.left_;
    right_ = other.right_;
    bottom_ = other.bottom_;
    top_ = other.top_;
}

template <typename T>
void Region<T>::init(std::initializer_list<T> i)
{
    if (i.size() < 4)
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
void Region<T>::init(const std::vector<T> &v)
{
    if (v.size() < 4)
    {
        THROW_EXCEPT(InvalidArgumentException, "v has wrong size");
    }

    left_ = v[0];
    right_ = v[1];
    bottom_ = v[2];
    top_ = v[3];
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
Region<T> &Region<T>::operator=(const Region& other)
{
    left_ = other.left_;
    right_ = other.right_;
    bottom_ = other.bottom_;
    top_ = other.top_;
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
template <typename F>
void Region<T>::iterate(F &func,
                        T deltaX,
                        T deltaY)
{
    for (T y = bottom_; y <= top_; y += deltaY)
    {
        for (T x = left_; x <= right_; x += deltaX)
        {
            if (!func(x, y))
            {
                break;
            }
        }
    }
}

template <typename T>
bool Region<T>::contains(const T &x,
                         const T &y) const
{
    return left_ <= x &&
           x <= right_ &&
           bottom_ <= y &&
           y <= top_;
}

template <typename T>
bool operator==(const Region<T> &r1, const Region<T>& r2)
{
    return r1.left() == r2.left() &&
           r1.right() == r2.right() &&
           r1.bottom() == r2.bottom() &&
           r1.top() == r2.top();
}

template <typename T>
Region<T> shift(const Region<T> &r,
                T deltaX,
                T deltaY)
{
    return Region<T>(r.left() + deltaX,
                     r.right() + deltaX,
                     r.bottom() + deltaY,
                     r.top() + deltaY);
}

template <typename T>
bool overlap(const Region<T> &r1,
             const Region<T> &r2)
{
    return r1.left() <= r2.right() &&
           r1.right() >= r2.left() &&
           r1.bottom() <= r2.top() &&
           r1.top() >= r2.bottom();
}

int diff(std::vector<commonlib::Region<int>> &result,
         const commonlib::Region<int> &r1,
         const commonlib::Region<int> &r2);

} // end of namespace commonlib
} // end of namespace mcdane

namespace std {

template <typename T>
std::ostream &operator<<(std::ostream& os,
                         const mcdane::commonlib::Region<T> &r)
{
    return os << "Region(left=" << r.left()
              << ", right=" << r.right()
              << ", bottom=" << r.bottom()
              << ", top=" << r.top()
              << ")";
}

} // end of namespace std

#endif

