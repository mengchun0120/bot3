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

inline bool checkLineOverlap(float start1,
                             float end1,
                             float start2,
                             float end2)
{
    return start1 < end2 && end1 > start2;
}

float lineDist(float start1,
               float end1,
               float start2,
               float end2);

bool checkRectCollide(float left1,
                      float right1,
                      float bottom1,
                      float top1,
                      float left2,
                      float right2,
                      float bottom2,
                      float top2);

bool checkRectCollide(float& adjustedDeltaX,
                      float& adjustedDeltaY,
                      float left1,
                      float right1,
                      float bottom1,
                      float top1,
                      float left2,
                      float right2,
                      float bottom2,
                      float top2,
                      float deltaX,
                      float deltaY);

} // end of namespace commonlib
} // end of namespace mcdane

#endif
