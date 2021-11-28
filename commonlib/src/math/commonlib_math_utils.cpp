#include <commonlib_math_utils.h>

namespace mcdane {
namespace commonlib {

void rotate(float& x,
            float& y,
            float directionX,
            float directionY)
{
    float x1 = x * directionX - y * directionY;
    float y1 = x * directionY + y * directionX;
    x = x1;
    y = y1;
}

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
    if (checkRectCollide(left1, right1, bottom1, top1,
                         left2, right2, bottom2, top2))
    {
        adjustedDeltaX = 0.0f;
        adjustedDeltaY = 0.0f;
        return true;
    }

    if (!checkRectCollide(left1+deltaX, right1+deltaX,
                          bottom1+deltaY, top1+deltaY,
                          left2, right2, bottom2, top2))
    {
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

