#ifndef INCLUDED_BOTLIB_COLLIDE_H
#define INCLUDED_BOTLIB_COLLIDE_H

namespace mcdane {
namespace botlib {

inline bool checkLineOverlap(float start1,
                             float end1,
                             float start2,
                             float end2)
{
    return start1 < end2 && end1 > start2;
}

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

} // end of namespace botlib
} // end of namespace mcdane

#endif

