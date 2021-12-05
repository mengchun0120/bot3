#ifndef INCLUDED_COMMONLIB_COLLIDE_H
#define INCLUDED_COMMONLIB_COLLIDE_H

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

bool checkRectCollideBoundary(float left,
                              float right,
                              float bottom,
                              float top,
                              float boundaryLeft,
                              float boundaryRight,
                              float boundaryBottom,
                              float boundaryTop);

bool checkRectCollideBoundary(float& adjustedDeltaX,
                              float& adjustedDeltaY,
                              float left,
                              float right,
                              float bottom,
                              float top,
                              float boundaryLeft,
                              float boundaryRight,
                              float boundaryBottom,
                              float boundaryTop,
                              float deltaX,
                              float deltaY);

bool checkRectCollideRect(float left1,
                          float right1,
                          float bottom1,
                          float top1,
                          float left2,
                          float right2,
                          float bottom2,
                          float top2);

bool checkRectCollideRect(float& adjustedDeltaX,
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

