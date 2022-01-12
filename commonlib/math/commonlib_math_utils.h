#ifndef INCLUDED_COMMONLIB_MATH_UTILS_H
#define INCLUDED_COMMONLIB_MATH_UTILS_H

#include <cmath>

namespace mcdane {
namespace commonlib {

constexpr float k_pi = 3.14159265359;
constexpr float k_verySmall = 1.0e-6f;

inline float rad(float degree)
{
    return degree / 180 * k_pi;
}

inline bool fuzzyEqual(float a, float b, float threshold=k_verySmall)
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

float sign(float x);

} // end of namespace commonlib
} // end of namespace mcdane

#endif
