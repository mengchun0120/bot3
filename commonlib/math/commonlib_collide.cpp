#include <cmath>
#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <commonlib_collide.h>

namespace mcdane {
namespace commonlib {

float lineDist(float start1,
               float end1,
               float start2,
               float end2)
{
    if (start1 > end2)
    {
        return start1 - end2;
    }
    else if(end1 < start2)
    {
        return start2 - end1;
    }

    return 0.0f;
}

inline float distToBoundary(float start,
                            float end,
                            float boundaryStart,
                            float boundaryEnd,
                            float delta)
{
    return delta > 0.0f ? boundaryEnd - end : start - boundaryStart;
}

bool checkRectCollideBoundary(const Region<float> &rect,
                              const Region<float> &boundary)
{
    return rect.left() < boundary.left() ||
           rect.right() > boundary.right() ||
           rect.bottom() < boundary.bottom() ||
           rect.top() > boundary.top();
}

bool checkRectCollideBoundary(Vector2 &adjustedDelta,
                              const Region<float> &rect,
                              const Region<float> &boundary,
                              const Vector2 &delta)
{
    bool collide = checkRectCollideBoundary(shift(rect, delta[0], delta[1]),
                                            boundary);
    if (!collide)
    {
        adjustedDelta = delta;
        return false;
    }

    float distToBoundaryX = distToBoundary(rect.left(), rect.right(),
                                           boundary.left(), boundary.right(),
                                           delta[0]);
    float distToBoundaryY = distToBoundary(rect.bottom(), rect.top(),
                                           boundary.bottom(), boundary.top(),
                                           delta[1]);
    float absDeltaX = fabs(delta[0]);
    float absDeltaY = fabs(delta[1]);
    float leftSide = distToBoundaryX * absDeltaY;
    float rightSide = distToBoundaryY * absDeltaX;
    float absAdjustedDeltaX, absAdjustedDeltaY;

    if (leftSide < rightSide)
    {
        absAdjustedDeltaX = distToBoundaryX;
        absAdjustedDeltaY = leftSide / absDeltaX;

    }
    else if (absDeltaY > 0.0f)
    {
        absAdjustedDeltaX = rightSide / absDeltaY;
        absAdjustedDeltaY = distToBoundaryY;
    }
    else
    {
        absAdjustedDeltaX = distToBoundaryX;
        absAdjustedDeltaY = 0.0f;
    }

    adjustedDelta[0] = std::signbit(delta[0]) ?
                                -absAdjustedDeltaX : absAdjustedDeltaX;
    adjustedDelta[1] = std::signbit(delta[1]) ?
                                -absAdjustedDeltaY : absAdjustedDeltaY;

    return true;
}

bool checkRectCollideRect(const Region<float> &rect1,
                          const Region<float> &rect2)
{
    return checkLineOverlap(rect1.left(), rect1.right(),
                            rect2.left(), rect2.right()) &&
           checkLineOverlap(rect1.bottom(), rect1.top(),
                            rect2.bottom(), rect2.top());
}

bool checkRectCollideRect(Vector2 &adjustedDelta,
                          const Region<float> &rect1,
                          const Region<float> &rect2,
                          const Vector2 &delta)
{
    bool collide = checkRectCollideRect(shift(rect1, delta[0], delta[1]),
                                        rect2);
    if (!collide)
    {
        adjustedDelta = delta;
        return false;
    }

    float lineDistX = lineDist(rect1.left(), rect1.right(),
                               rect2.left(), rect2.right());
    float lineDistY = lineDist(rect1.bottom(), rect1.top(),
                               rect2.bottom(), rect2.top());
    float absDeltaX = fabs(delta[0]);
    float absDeltaY = fabs(delta[1]);
    float absAdjustedDeltaX, absAdjustedDeltaY;
    float leftSide = lineDistX * absDeltaY;
    float rightSide = absDeltaX * lineDistY;

    if (leftSide > rightSide)
    {
        absAdjustedDeltaX = lineDistX;
        absAdjustedDeltaY = leftSide / absDeltaX;
    }
    else if (absDeltaY > 0.0f)
    {
        absAdjustedDeltaX = rightSide / absDeltaY;
        absAdjustedDeltaY = lineDistY;
    }
    else
    {
        absAdjustedDeltaX = lineDistX;
        absAdjustedDeltaY = 0.0f;
    }

    adjustedDelta[0] = std::signbit(delta[0]) ?
                            -absAdjustedDeltaX : absAdjustedDeltaX;
    adjustedDelta[1] = std::signbit(delta[1]) ?
                            -absAdjustedDeltaY : absAdjustedDeltaY;

    return true;
}

} // end of namespace commonlib
} // end of namespace mcdane

