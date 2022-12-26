#ifndef INCLUDED_BOTLIB_TARGET_FINDER_H
#define INCLUDED_BOTLIB_TARGET_FINDER_H

#include <commonlib_linked_list.h>
#include <commonlib_linked_item.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class Missile;
class Robot;

class TargetFinder {
public:
    TargetFinder(Missile* src,
                 GameObjItemPool& pool);

    bool operator()(GameObject* obj);

    Robot* getTarget();

private:
    Missile* src_;
    GameObjItemPool& pool_;
    GameObjItemList candidates_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
