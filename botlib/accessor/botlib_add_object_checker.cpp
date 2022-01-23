#include <commonlib_collide.h>
#include <botlib_game_object.h>
#include <botlib_add_object_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

AddObjectChecker::AddObjectChecker(const Region<float>& collideRegion)
    : collide_(false)
    , collideRegion_(collideRegion)
{
}

void AddObjectChecker::reset(const commonlib::Region<float>& collideRegion)
{
    collide_ = false;
    collideRegion_ = collideRegion;
}

bool AddObjectChecker::run(GameObjectList& objList,
                           GameObject* obj)
{
    if (obj->state() != GameObjectState::ALIVE ||
        !isNonPassthroughObjType(obj->type()))
    {
        return true;
    }

    if (checkRectCollideRect(obj->collideRegion(), collideRegion_))
    {
        collide_ = true;
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

