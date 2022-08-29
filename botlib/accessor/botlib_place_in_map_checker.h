#ifndef INCLUDED_BOTLIB_PLACE_IN_MAP_CHECHER
#define INCLUDED_BOTLIB_PLACE_IN_MAP_CHECHER

#include <commonlib_region.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class PlaceInMapChecker: public GameMapAccessor {
public:
    PlaceInMapChecker(const commonlib::Region<float>& collideRegion);

    void reset(const commonlib::Region<float>& collideRegion);

    bool run(GameObject* obj) override;

    inline bool collide() const;

private:
    bool collide_;
    commonlib::Region<float> collideRegion_;
};

bool PlaceInMapChecker::collide() const
{
    return collide_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

