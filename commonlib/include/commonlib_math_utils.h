#ifndef INCLUDED_COMMONLIB_MATH_UTILS_H
#define INCLUDED_COMMONLIB_MATH_UTILS_H

#include <cmath>

namespace mcdane {
namespace commonlib {

constexpr float PI = 3.14159265359;

inline float rad(float degree)
{
    return degree / 180 * PI;
}

inline bool fuzzyEqual(float a, float b, float threshold=1.0e-6f)
{
    return fabs(a - b) <= threshold;
}

template <typename T>
T clamp(const T& t, const T& min, const T& max)
{
    if (t < min)
    {
        return min;
    }
    else if (t > max)
    {
        return max;
    }

    return t;
}

void rotate(float& x,
            float& y,
            float directionX,
            float directionY);

} // end of namespace commonlib
} // end of namespace mcdane

#endif
