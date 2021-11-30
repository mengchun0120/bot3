#include <cassert>
#include <commonlib_math_utils.h>
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

void testCollide_RectWithinBoundary()
{
    assert(checkRectWithinBoundary(0.0f, 2.0f, 0.0f, 2.0f,
                                   0.0f, 100.0f, 0.0f, 100.0f));
}

void testCollide_RectOutsideBoundary()
{
    assert(!checkRectWithinBoundary(-1.0f, 1.0f, 0.0f, 2.0f,
                                    0.0f, 100.0f, 0.0f, 100.0f));
    assert(!checkRectWithinBoundary(99.0f, 101.0f, 0.0f, 2.0f,
                                    0.0f, 100.0f, 0.0f, 100.0f));
}

void testCollide_RectCollide()
{
    float left = 1.0f, bottom = 1.0f, right = 2.0f, top = 2.0f;
    float adjustedDeltaX, adjustedDeltaY;
    bool collide;

    collide = checkRectCollide(adjustedDeltaX, adjustedDeltaY,
                               1.2f, 1.5f, 1.3f, 2.0f,
                               left, right, bottom, top,
                               0.1f, 0.1f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, 0.0f));
    assert(fuzzyEqual(adjustedDeltaY, 0.0f));

    collide = checkRectCollide(adjustedDeltaX, adjustedDeltaY,
                               0.0f, 0.5f, 0.0f, 0.5f,
                               left, right, bottom, top,
                               0.6f, 0.6f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, 0.5f));
    assert(fuzzyEqual(adjustedDeltaY, 0.5f));

    collide = checkRectCollide(adjustedDeltaX, adjustedDeltaY,
                               0.0f, 1.2f, 0.0f, 0.8f,
                               left, right, bottom, top,
                               0.3f, 0.4f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, 0.2f*0.3f/0.4f));
    assert(fuzzyEqual(adjustedDeltaY, 0.2f));

    collide = checkRectCollide(adjustedDeltaX, adjustedDeltaY,
                               2.2f, 3.0f, 0.0f, 0.9f,
                               left, right, bottom, top,
                               -0.3f, 0.4f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, -0.2f));
    assert(fuzzyEqual(adjustedDeltaY, 0.2f*0.4f/0.3f));

    collide = checkRectCollide(adjustedDeltaX, adjustedDeltaY,
                               2.1f, 3.1f, 2.2f, 3.2f,
                               left, right, bottom, top,
                               -0.3f, -0.4f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, -0.2f*0.3f/0.4f));
    assert(fuzzyEqual(adjustedDeltaY, -0.2f));

    collide = checkRectCollide(adjustedDeltaX, adjustedDeltaY,
                               1.4f, 2.4f, 2.2f, 3.2f,
                               left, right, bottom, top,
                               -0.3f, -0.4f);
    assert(collide);
    assert(fuzzyEqual(adjustedDeltaX, -0.2f*0.3f/0.4f));
    assert(fuzzyEqual(adjustedDeltaY, -0.2f));
}

void testCollide_RectNotCollide()
{
    float left = 1.0f, bottom = 1.0f, right = 2.0f, top = 2.0f;
    float adjustedDeltaX, adjustedDeltaY;
    bool collide;

    collide = checkRectCollide(adjustedDeltaX, adjustedDeltaY,
                               0.0f, 0.8f, 0.0f, 0.8f,
                               left, right, bottom, top,
                               0.1f, 0.1f);
    assert(!collide);

    collide = checkRectCollide(adjustedDeltaX, adjustedDeltaY,
                               1.0f, 2.0f, 0.0f, 0.8f,
                               left, right, bottom, top,
                               -0.1f, -0.1f);
    assert(!collide);
}

void testCollide()
{
    testCollide_LineOverlap();
    testCollide_LineNotOverlap();
    testCollide_RectWithinBoundary();
    testCollide_RectOutsideBoundary();
    testCollide_RectCollide();
    testCollide_RectNotCollide();
}

} // end of namespace commonlib
} // end of namespace mcdane

