#include <commonlib_math_utils.h>
#include <commonlib_object_pool.h>
#include <botlib_missile.h>
#include <botlib_robot.h>
#include <botlib_target_finder.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TargetFinder::TargetFinder(Side side,
                           int numTargets,
                           GameObjItemList &targets,
                           GameObjItemPool &pool)
    : side_(side)
    , numTargets_(numTargets)
    , targets_(targets)
    , pool_(pool)
{
}

bool TargetFinder::operator()(GameObject *obj)
{
    if (obj->type() != GameObjectType::ROBOT)
    {
        return true;
    }

    Robot *robot = static_cast<Robot*>(obj);
    if (robot->state() != GameObjectState::ALIVE || robot->side() != side_)
    {
        return true;
    }

    GameObjectItem *item = pool_.alloc(obj);
    targets_.pushBack(item);

    return true;
}

GameObjItemList &TargetFinder::getTargets()
{
    int nonTargetCount = static_cast<int>(targets_.size()) - numTargets_;

    for (int i = 0; i < nonTargetCount; ++i)
    {
        int index = randInt(0, static_cast<int>(targets_.size()) - 1);
        targets_.remove(targets_.get(index));
    }

    return targets_;
}

} // end of namespace botlib
} // end of namespace mcdane

