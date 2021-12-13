#include <commonlib_collide.h>
#include <botlib_collide_robot_tile_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void CollideRobotTileChecker::reset()
{
    collide_ = false;
}

void CollideRobotTileChecker::setObj(GameObject* o,
                                     float deltaX,
                                     float deltaY)
{
    obj_ = o;
    left_ = o->collideLeft();
    right_ = o->collideRight();
    bottom_ = o->collideBottom();
    top_ = o->collideTop();
    adjustedDeltaX_ = deltaX;
    adjustedDeltaY_ = deltaY;
}

bool CollideRobotTileChecker::operator()(GameObject* o)
{
    if (!check(o))
    {
        return true;
    }

    bool collide = checkRectCollideRect(adjustedDeltaX_, adjustedDeltaY_;
                                        left_, right_, bottom_, top_,
                                        o->collideLeft(), o->collideRight(),
                                        o->collideBottom(), o->collideTop(),
                                        adjustedDeltaX_, adjustedDeltaY_);

    if (collide)
    {
        collide_ = true;
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

