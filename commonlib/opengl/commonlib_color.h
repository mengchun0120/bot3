#ifndef INCLUDED_COMMONLIB_COLOR_H
#define INCLUDED_COMMONLIB_COLOR_H

#include <vector>
#include <type_traits>
#include <commonlib_exception.h>
#include <commonlib_algorithm.h>
#include <commonlib_vector.h>

namespace mcdane {
namespace commonlib {

struct Color: public Vector<4> {
    inline static bool isValidComponent(unsigned int c);

    inline static float toFloat(unsigned int c);

    Color() = default;

    Color(unsigned int red,
          unsigned int green,
          unsigned int blue,
          unsigned int alpha);

    Color(std::initializer_list<unsigned int> c);

    Color(const std::vector<unsigned int> &c);

    template <typename Iterator>
    Color(Iterator begin,
          Iterator end);

    void init(unsigned int red,
              unsigned int green,
              unsigned int blue,
              unsigned int alpha);

    void init(std::initializer_list<unsigned int> c);

    void init(const std::vector<unsigned int> &c);

    template <typename Iterator>
    void init(Iterator begin,
              Iterator end);

    inline float red() const noexcept;

    inline float green() const noexcept;

    inline float blue() const noexcept;

    inline float alpha() const noexcept;
};

static_assert(std::is_standard_layout<Color>::value,
              "Color must be standard layout");

bool Color::isValidComponent(unsigned int c)
{
    return c <= 255;
}

float Color::toFloat(unsigned int c)
{
    return static_cast<float>(c) / 255.0f;
}

template <typename Iterator>
Color::Color(Iterator begin,
             Iterator end)
{
    init(begin, end);
}

template <typename Iterator>
void Color::init(Iterator begin,
                 Iterator end)
{
    unsigned int num = count(begin, end);
    if (num != 4)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Length of initializer list is not 4");
    }

    unsigned int i = 0;
    for (auto it = begin; it != end; ++it, ++i)
    {
        if (!isValidComponent(*it))
        {
            THROW_EXCEPT(InvalidArgumentException,
                         "Invalid component " + std::to_string(*it));
        }

        (*this)[i] = toFloat(*it);
    }
}

float Color::red() const noexcept
{
    return (*this)[0];
}

float Color::green() const noexcept
{
    return (*this)[1];
}

float Color::blue() const noexcept
{
    return (*this)[2];
}

float Color::alpha() const noexcept
{
    return (*this)[3];
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

