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
    Region<float> boundary{0.0f, 100.0f, 0.0f, 100.0f};
    Vector2 adjustedDelta;
    bool collide;

    collide = checkRectCollideBoundary(adjustedDelta,
                                       {10.0f, 20.0f, 20.0f, 30.0f},
                                       boundary,
                                       {-20.0f, 0.0f});
    assert(collide);
    assert(fuzzyEqual(adjustedDelta[0], -10.0f));
    assert(fuzzyEqual(adjustedDelta[1], 0.0f));

    collide = checkRectCollideBoundary(adjustedDelta,
                                       {80.0f, 90.0f, 20.0f, 30.0f},
                                       boundary,
                                       {0.0f, -30.0f});
    assert(collide);
    assert(fuzzyEqual(adjustedDelta[0], 0.0f));
    assert(fuzzyEqual(adjustedDelta[1], -20.0f));

    collide = checkRectCollideBoundary(adjustedDelta,
                                       {10.0f, 20.0f, 70.0f, 80.0f},
                                       boundary,
                                       {-20.0f, 30.0f});
    assert(collide);
    assert(fuzzyEqual(adjustedDelta[0], -10.0f));
    assert(fuzzyEqual(adjustedDelta[1], 15.0f));
}

void testCollide_RectNotCollideBoundary()
{
    Region<float> boundary{0.0f, 100.0f, 0.0f, 100.0f};
    Vector2 adjustedDelta;
    bool collide;

    collide = checkRectCollideBoundary(adjustedDelta,
                                       {10.0f, 20.0f, 20.0f, 30.0f},
                                       boundary,
                                       {-5.0f, 5.0f});
    assert(!collide);
    assert(fuzzyEqual(adjustedDelta[0], -5.0f));
    assert(fuzzyEqual(adjustedDelta[1], 5.0f));
}

void testCollide_RectCollideRect()
{
    Region<float> rect2{1.0f, 2.0f, 1.0f, 2.0f};
    Vector2 adjustedDelta;
    bool collide;

    collide = checkRectCollideRect(adjustedDelta,
                                   {0.0f, 0.5f, 0.0f, 0.5f},
                                   rect2,
                                   {0.6f, 0.6f});
    assert(collide);
    assert(fuzzyEqual(adjustedDelta[0], 0.5f));
    assert(fuzzyEqual(adjustedDelta[1], 0.5f));

    collide = checkRectCollideRect(adjustedDelta,
                                   {0.0f, 1.2f, 0.0f, 0.8f},
                                   rect2,
                                   {0.3f, 0.4f});
    assert(collide);
    assert(fuzzyEqual(adjustedDelta[0], 0.2f*0.3f/0.4f));
    assert(fuzzyEqual(adjustedDelta[1], 0.2f));

    collide = checkRectCollideRect(adjustedDelta,
                                   {2.2f, 3.0f, 0.0f, 0.9f},
                                   rect2,
                                   {-0.3f, 0.4f});
    assert(collide);
    assert(fuzzyEqual(adjustedDelta[0], -0.2f));
    assert(fuzzyEqual(adjustedDelta[1], 0.2f*0.4f/0.3f));

    collide = checkRectCollideRect(adjustedDelta,
                                   {2.1f, 3.1f, 2.2f, 3.2f},
                                   rect2,
                                   {-0.3f, -0.4f});
    assert(collide);
    assert(fuzzyEqual(adjustedDelta[0], -0.2f*0.3f/0.4f));
    assert(fuzzyEqual(adjustedDelta[1], -0.2f));

    collide = checkRectCollideRect(adjustedDelta,
                                   {1.4f, 2.4f, 2.2f, 3.2f},
                                   rect2,
                                   {-0.3f, -0.4f});
    assert(collide);
    assert(fuzzyEqual(adjustedDelta[0], -0.2f*0.3f/0.4f));
    assert(fuzzyEqual(adjustedDelta[1], -0.2f));
}

void testCollide_RectNotCollideRect()
{
    Region<float> rect2{1.0f, 2.0f, 1.0f, 2.0f};
    Vector2 adjustedDelta;
    bool collide;

    collide = checkRectCollideRect(adjustedDelta,
                                   {0.0f, 0.8f, 0.0f, 0.8f},
                                   rect2,
                                   {0.1f, 0.1f});
    assert(!collide);
    assert(fuzzyEqual(adjustedDelta[0], 0.1f));
    assert(fuzzyEqual(adjustedDelta[1], 0.1f));

    collide = checkRectCollideRect(adjustedDelta,
                                   {1.0f, 2.0f, 0.0f, 0.8f},
                                   rect2,
                                   {-0.1f, -0.1f});
    assert(!collide);
    assert(fuzzyEqual(adjustedDelta[0], -0.1f));
    assert(fuzzyEqual(adjustedDelta[1], -0.1f));
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

