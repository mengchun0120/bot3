#include <cmath>
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

bool checkRectCollideBoundary(float left,
                              float right,
                              float bottom,
                              float top,
                              float boundaryLeft,
                              float boundaryRight,
                              float boundaryBottom,
                              float boundaryTop)
{
    return left < boundaryLeft ||
           right > boundaryRight ||
           bottom < boundaryBottom ||
           top > boundaryTop;
}

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
                              float deltaY)
{
    bool collide = checkRectCollideBoundary(left+deltaX, right+deltaX,
                                            bottom+deltaY, top+deltaY,
                                            boundaryLeft, boundaryRight,
                                            boundaryBottom, boundaryTop);
    if (!collide)
    {
        adjustedDeltaX = deltaX;
        adjustedDeltaY = deltaY;
        return false;
    }

    float distToBoundaryX = distToBoundary(left, right, boundaryLeft,
                                           boundaryRight, deltaX);
    float distToBoundaryY = distToBoundary(bottom, top, boundaryBottom,
                                           boundaryTop, deltaY);
    float absDeltaX = fabs(deltaX);
    float absDeltaY = fabs(deltaY);
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

    adjustedDeltaX = std::signbit(deltaX) ? -absAdjustedDeltaX : absAdjustedDeltaX;
    adjustedDeltaY = std::signbit(deltaY) ? -absAdjustedDeltaY : absAdjustedDeltaY;

    return true;
}

bool checkRectCollideRect(float left1,
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
                          float deltaY)
{
    bool collide = checkRectCollideRect(left1+deltaX, right1+deltaX,
                                        bottom1+deltaY, top1+deltaY,
                                        left2, right2, bottom2, top2);
    if (!collide)
    {
        adjustedDeltaX = deltaX;
        adjustedDeltaY = deltaY;
        return false;
    }

    float lineDistX = lineDist(left1, right1, left2, right2);
    float lineDistY = lineDist(bottom1, top1, bottom2, top2);
    float absDeltaX = fabs(deltaX);
    float absDeltaY = fabs(deltaY);
    float absAdjustedDeltaX, absAdjustedDeltaY;
    float leftSide = lineDistX * absDeltaY;
    float rightSide = absDeltaX * lineDistY;

    if (leftSide > rightSide)
    {
        absAdjustedDeltaX = lineDistX;
        absAdjustedDeltaY = leftSide / absDeltaX;
    }
    else
    {
        absAdjustedDeltaX = rightSide / absDeltaY;
        absAdjustedDeltaY = lineDistY;
    }

    adjustedDeltaX = std::signbit(deltaX) ? -absAdjustedDeltaX : absAdjustedDeltaX;
    adjustedDeltaY = std::signbit(deltaY) ? -absAdjustedDeltaY : absAdjustedDeltaY;

    return true;
}

} // end of namespace commonlib
} // end of namespace mcdane

