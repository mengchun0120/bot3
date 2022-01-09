#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_tile.h>
#include <botlib_missile_hit_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void MissileHitChecker::reset(Missile* missile)
{
    collide_ = false;
    missile_ = missile;
}

bool MissileHitChecker::run(GameObjectList& objList,
                            GameObject* obj)
{
    if (!check(obj))
    {
        return true;
    }

    bool collide1 = checkRectCollideRect(missile_->collideRegion(),
                                         obj->collideRegion());
    if (!collide1)
    {
        return true;
    }

    collide_ = true;

    if (obj->type() == GameObjectType::ROBOT)
    {
        Robot* robot = static_cast<Robot*>(obj);
        robot->addHP(-missile_->damage());
    }
    else if (obj->type() == GameObjectType::TILE)
    {
        Tile* tile = static_cast<Tile*>(obj);
        tile->addHP(-missile_->damage());
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
