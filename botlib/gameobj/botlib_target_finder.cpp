#include <commonlib_math_utils.h>
#include <commonlib_object_pool.h>
#include <botlib_missile.h>
#include <botlib_robot.h>
#include <botlib_target_finder.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TargetFinder::TargetFinder(Missile* src, GameObjItemPool& pool)
    : src_(src)
    , pool_(pool)
    , candidates_(pool.deleter())
{
}

bool TargetFinder::operator()(GameObject* obj)
{
    if (obj->type() != GameObjectType::ROBOT)
    {
        return true;
    }

    Robot* robot = static_cast<Robot*>(obj);
    if (robot->state() != GameObjectState::ALIVE || robot->side() == src_->side())
    {
        return true;
    }

    GameObjectItem* item = pool_.alloc(obj);
    candidates_.pushBack(item);

    return true;
}

Robot* TargetFinder::getTarget()
{
    int maxIndex = candidates_.size() - 1;
    if (maxIndex < 0)
    {
        return nullptr;
    }

    if (maxIndex == 0)
    {
        return static_cast<Robot*>(candidates_.first()->item());
    }

    int index = randInt(0, maxIndex);
    return static_cast<Robot*>(candidates_.get(index)->item());
}

} // end of namespace botlib
} // end of namespace mcdane

