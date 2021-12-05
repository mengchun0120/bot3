#include <cassert>
#include <iostream>
#include <commonlib_math_utils.h>
#include <commonlib_collide.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

void testCollide_LineOverlap()
{
    assert(checkLineOverlap(0.0f, 2.0f, 1.0f, 3.0f));
}

void testCollide_LineNotOverlap()
{
    assert(!checkLineOverlap(0.0f, 2.0f, 3.0f, 4.0f));
    assert(!checkLineOverlap(0.0f, 2.0f, 2.0f, 3.0f));
}

void testCollide_RectCollideBoundary()
{
    float boundaryLeft = 0.0f, boundaryRight = 100.0f;
    float boundaryBottom = 0.0f, boundaryTop = 100.0f;
    float adjustedDeltaX, adjustedDeltaY;
    bool collide;

    collide = checkRectCollideBoundary(adjustedDeltaX, adjustedDeltaY,
                                       10.0f, 20.0f, 20.0f, 30.0f,
                                       boundaryLeft, boundaryRight,
                                       boundaryBottom, boundaryTop,
                                       -20.0f, 0.0f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, -10.0f));
    assert(fuzzyEqual(adjustedDeltaY, 0.0f));

    collide = checkRectCollideBoundary(adjustedDeltaX, adjustedDeltaY,
                                       80.0f, 90.0f, 20.0f, 30.0f,
                                       boundaryLeft, boundaryRight,
                                       boundaryBottom, boundaryTop,
                                       0.0f, -30.0f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, 0.0f));
    assert(fuzzyEqual(adjustedDeltaY, -20.0f));

    collide = checkRectCollideBoundary(adjustedDeltaX, adjustedDeltaY,
                                       10.0f, 20.0f, 70.0f, 80.0f,
                                       boundaryLeft, boundaryRight,
                                       boundaryBottom, boundaryTop,
                                       -20.0f, 30.0f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, -10.0f));
    assert(fuzzyEqual(adjustedDeltaY, 15.0f));
}

void testCollide_RectNotCollideBoundary()
{
    float boundaryLeft = 0.0f, boundaryRight = 100.0f;
    float boundaryBottom = 0.0f, boundaryTop = 100.0f;
    float adjustedDeltaX, adjustedDeltaY;
    bool collide;

    collide = checkRectCollideBoundary(adjustedDeltaX, adjustedDeltaY,
                                       10.0f, 20.0f, 20.0f, 30.0f,
                                       boundaryLeft, boundaryRight,
                                       boundaryBottom, boundaryTop,
                                       -5.0f, 5.0f);
    assert(!collide);
    assert(fuzzyEqual(adjustedDeltaX, -5.0f));
    assert(fuzzyEqual(adjustedDeltaY, 5.0f));
}

void testCollide_RectCollideRect()
{
    float left = 1.0f, bottom = 1.0f, right = 2.0f, top = 2.0f;
    float adjustedDeltaX, adjustedDeltaY;
    bool collide;

    collide = checkRectCollideRect(adjustedDeltaX, adjustedDeltaY,
                                   0.0f, 0.5f, 0.0f, 0.5f,
                                   left, right, bottom, top,
                                   0.6f, 0.6f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, 0.5f));
    assert(fuzzyEqual(adjustedDeltaY, 0.5f));

    collide = checkRectCollideRect(adjustedDeltaX, adjustedDeltaY,
                                   0.0f, 1.2f, 0.0f, 0.8f,
                                   left, right, bottom, top,
                                   0.3f, 0.4f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, 0.2f*0.3f/0.4f));
    assert(fuzzyEqual(adjustedDeltaY, 0.2f));

    collide = checkRectCollideRect(adjustedDeltaX, adjustedDeltaY,
                                   2.2f, 3.0f, 0.0f, 0.9f,
                                   left, right, bottom, top,
                                   -0.3f, 0.4f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, -0.2f));
    assert(fuzzyEqual(adjustedDeltaY, 0.2f*0.4f/0.3f));

    collide = checkRectCollideRect(adjustedDeltaX, adjustedDeltaY,
                                   2.1f, 3.1f, 2.2f, 3.2f,
                                   left, right, bottom, top,
                                   -0.3f, -0.4f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, -0.2f*0.3f/0.4f));
    assert(fuzzyEqual(adjustedDeltaY, -0.2f));

    collide = checkRectCollideRect(adjustedDeltaX, adjustedDeltaY,
                                   1.4f, 2.4f, 2.2f, 3.2f,
                                   left, right, bottom, top,
                                   -0.3f, -0.4f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, -0.2f*0.3f/0.4f));
    assert(fuzzyEqual(adjustedDeltaY, -0.2f));
}

void testCollide_RectNotCollideRect()
{
    float left = 1.0f, bottom = 1.0f, right = 2.0f, top = 2.0f;
    float adjustedDeltaX, adjustedDeltaY;
    bool collide;

    collide = checkRectCollideRect(adjustedDeltaX, adjustedDeltaY,
                                   0.0f, 0.8f, 0.0f, 0.8f,
                                   left, right, bottom, top,
                                   0.1f, 0.1f);
    assert(!collide);
    assert(fuzzyEqual(adjustedDeltaX, 0.1f));
    assert(fuzzyEqual(adjustedDeltaY, 0.1f));

    collide = checkRectCollideRect(adjustedDeltaX, adjustedDeltaY,
                                   1.0f, 2.0f, 0.0f, 0.8f,
                                   left, right, bottom, top,
                                   -0.1f, -0.1f);
    assert(!collide);
    assert(fuzzyEqual(adjustedDeltaX, -0.1f));
    assert(fuzzyEqual(adjustedDeltaY, -0.1f));
}

void testCollide()
{
    testCollide_LineOverlap();
    testCollide_LineNotOverlap();
    testCollide_RectCollideBoundary();
    testCollide_RectNotCollideBoundary();
    testCollide_RectCollideRect();
    testCollide_RectNotCollideRect();
}

} // end of namespace commonlib
} // end of namespace mcdane

