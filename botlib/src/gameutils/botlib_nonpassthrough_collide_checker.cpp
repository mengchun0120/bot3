#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_nonpassthrough_collide_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void NonpassthroughCollideChecker::reset(GameObject* obj,
                                         const commonlib::Vector2& delta)
{
    obj_ = obj;
    collide_ = false;
    delta_ = delta;
}

bool NonpassthroughCollideChecker::run(GameObjectList& objList,
                                       GameObject* other)
{
    if (!check(other))
    {
        return true;
    }

    bool collide = checkRectCollideRect(delta_,
                                        obj_->collideRegion(),
                                        other->collideRegion(),
                                        delta_);

    if (collide)
    {
        collide_ = true;
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

