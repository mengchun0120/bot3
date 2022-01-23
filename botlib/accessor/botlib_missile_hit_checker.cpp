#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_tile.h>
#include <botlib_missile.h>
#include <botlib_robot.h>
#include <botlib_missile_hit_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

namespace {

inline bool isSameSideRobot(GameObject* obj,
                            Missile* missile)
{
    return obj->type() == GameObjectType::ROBOT &&
           static_cast<Robot*>(obj)->side() == missile->side();
}


inline bool check(GameObject* obj, Missile* missile)
{
    return obj->state() == GameObjectState::ALIVE &&
           (obj->type() == GameObjectType::TILE ||
            isSameSideRobot(obj, missile));
}

} // end of unnamed namespace

MissileHitChecker::MissileHitChecker(Missile* missile,
                                     bool inflictDamage)
    : collide_(false)
    , inflictDamage_(inflictDamage)
    , missile_(missile)
{
}

void MissileHitChecker::reset(Missile* missile,
                              bool inflictDamage)
{
    collide_ = false;
    inflictDamage_ = inflictDamage;
    missile_ = missile;
}

bool MissileHitChecker::run(GameObjectList& objList,
                            GameObject* obj)
{
    if (!check(obj, missile_))
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

    if (inflictDamage_)
    {
        doDamage(obj);
    }

    return true;
}

void MissileHitChecker::doDamage(GameObject* obj)
{
    if (obj->type() == GameObjectType::ROBOT)
    {
        Robot* robot = static_cast<Robot*>(obj);
        robot->addHP(-missile_->damage());
        LOG_DEBUG << "damage robot " << robot << " hp=" << robot->hp() << LOG_END;
    }
    else if (obj->type() == GameObjectType::TILE)
    {
        Tile* tile = static_cast<Tile*>(obj);
        tile->addHP(-missile_->damage());
        LOG_DEBUG << "damage tile " << tile << " hp=" << tile->hp() << LOG_END;
    }
}

} // end of namespace botlib
} // end of namespace mcdane
