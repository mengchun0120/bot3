#ifndef INCLUDED_COMMONLIB_COLLIDE_H
#define INCLUDED_COMMONLIB_COLLIDE_H

#include <commonlib_region.h>
#include <commonlib_vector.h>

namespace mcdane {
namespace commonlib {

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

bool checkRectCollideBoundary(const Region<float> &rect,
                              const Region<float> &boundary);

bool checkRectCollideBoundary(Vector2 &adjustedDelta,
                              const Region<float> &rect,
                              const Region<float> &boundary,
                              const Vector2 &delta);

bool checkRectCollideRect(const Region<float> &rect1,
                          const Region<float> &rect2);

bool checkRectCollideRect(Vector2 &adjustedDelta,
                          const Region<float> &rect1,
                          const Region<float> &rect2,
                          const Vector2 &delta);

} // end of namespace commonlib
} // end of namespace mcdane

#endif

