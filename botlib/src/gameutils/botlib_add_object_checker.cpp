#include <commonlib_collide.h>
#include <botlib_add_object_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

namespace {

inline bool check(GameObject* obj)
{
    return obj->alive() && isNonPassthroughObjType(obj->type());
}

} // end of unnamed namespace

AddObjectChecker::AddObjectChecke(const Region<float>& collideRegion)
    : collide_(false)
    , collideRegion_(collideRegion)
{
}

bool AddObjectChecker::run(GameObjectList& objList,
                           GameObject* obj)
{
    if (!check(obj))
    {
        return true;
    }

    bool collide1 = checkRectCollideRect(obj->collideRegion(), collideRegion_);
    if (collide1)
    {
        collide_ = true;
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

