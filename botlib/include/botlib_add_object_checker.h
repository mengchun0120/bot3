#ifndef INCLUDED_BOTLIB_ADD_OBJECT_CHECHER
#define INCLUDED_BOTLIB_ADD_OBJECT_CHECHER

#include <commonlib_region.h>
#include <botlib_game_object.h>

namespace mcdane {
namespace botlib {

class AddObjectChecker {
public:
    void reset(const commonlib::Region<float>& collideRegion);

    bool run(GameObject* o);

    inline bool collide() const;

private:
    inline bool check(GameObject* o) const;

private:
    bool collide_;
    commonlib::Region<float> collideRegion_;
};

bool AddObjectChecker::collide() const
{
    return collide_;
}

bool AddObjectChecker::check(GameObject* o) const
{
    return o->alive() && isNonPassthroughObjType(o->type());
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

