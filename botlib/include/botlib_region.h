#ifndef INCLUDED_BOTLIB_REGION_H
#define INCLUDED_BOTLIB_REGION_H

namespace mcdane {
namespace botlib {

template <typename T>
class Region {
public:
    Region() = default;

    Region(const Region& other) = default;

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

} // end of namespace botlib
} // end of namespace mcdane

#endif

