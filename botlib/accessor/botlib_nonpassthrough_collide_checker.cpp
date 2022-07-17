#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_game_object.h>
#include <botlib_nonpassthrough_collide_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

namespace {

bool check(const GameObject* obj,
           const GameObject* thisObj)
{
    return obj != thisObj &&
           obj->state() == GameObjectState::ALIVE &&
           (obj->type() == GameObjectType::ROBOT ||
            obj->type() == GameObjectType::TILE);
}

} // end of unnamed namespace

NonpassthroughCollideChecker::NonpassthroughCollideChecker(const GameObject* obj,
                                                           Vector2& delta1)
    : obj_(obj)
    , collide_(false)
    , delta_(delta1)
{
}

bool NonpassthroughCollideChecker::run(GameObject* other)
{
    if (!check(other, obj_))
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

