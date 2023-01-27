#ifndef INCLUDED_BOTLIB_TARGET_FINDER_H
#define INCLUDED_BOTLIB_TARGET_FINDER_H

#include <commonlib_linked_list.h>
#include <commonlib_linked_item.h>
#include <botlib_side.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class TargetFinder {
public:
    TargetFinder(Side side,
                 int numTargets,
                 GameObjItemList& targets,
                 GameObjItemPool& pool);

    bool operator()(GameObject* obj);

    GameObjItemList& getTargets();

private:
    Side side_;
    int numTargets_;
    GameObjItemList& targets_;
    GameObjItemPool& pool_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
