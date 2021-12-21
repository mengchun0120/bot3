#include <commonlib_collide.h>
#include <botlib_add_object_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void AddObjectChecker::reset(const commonlib::Region<float>& collideRegion)
{
    collide_ = false;
    collideRegion_ = collideRegion;
}

bool AddObjectChecker::run(GameObject* o)
{
    if (!check(o))
    {
        return true;
    }

    bool collide1 = checkRectCollideRect(o->collideRegion(), collideRegion_);
    if (collide1)
    {
        collide_ = true;
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

