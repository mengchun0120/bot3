#ifndef INCLUDED_BOTLIB_ADD_OBJECT_CHECHER
#define INCLUDED_BOTLIB_ADD_OBJECT_CHECHER

#include <commonlib_region.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class AddObjectChecker: public GameMapAccessor {
public:
    AddObjectChecker(const commonlib::Region<float>& collideRegion);

    void reset(const commonlib::Region<float>& collideRegion);

    bool run(GameObjectList& objList,
             GameObject* obj) override;

    inline bool collide() const;

private:
    bool collide_;
    commonlib::Region<float> collideRegion_;
};

bool AddObjectChecker::collide() const
{
    return collide_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

