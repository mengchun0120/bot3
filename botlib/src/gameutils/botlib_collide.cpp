#include <botlib_collide.h>

namespace mcdane {
namespace botlib {

bool checkRectCollide(float left1,
                      float right1,
                      float bottom1,
                      float top1,
                      float left2,
                      float right2,
                      float bottom2,
                      float top2)
{
    return checkLineOverlap(left1, right1, left2, right2) &&
           checkLineOverlap(bottom1, top1, bottom2, top2);
}

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
                      float deltaY)
{
}

} // end of namespace botlib
} // end of namespace mcdane

