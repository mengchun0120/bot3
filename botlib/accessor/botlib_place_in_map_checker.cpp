#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_game_object.h>
#include <botlib_place_in_map_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

PlaceInMapChecker::PlaceInMapChecker(const Region<float>& collideRegion)
    : collide_(false)
    , collideRegion_(collideRegion)
{
}

void PlaceInMapChecker::reset(const commonlib::Region<float>& collideRegion)
{
    collide_ = false;
    collideRegion_ = collideRegion;
}

bool PlaceInMapChecker::run(GameObject* obj)
{
    if (obj->state() != GameObjectState::ALIVE ||
        !isNonPassthroughObjType(obj->type()))
    {
        return true;
    }

    if (checkRectCollideRect(obj->collideRegion(), collideRegion_))
    {
        LOG_INFO << "check " << obj->type() << " " << obj->id() << " "
                 << obj->collideRegion() << " " << collideRegion_
                 << LOG_END;
        collide_ = true;
        return false;
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

