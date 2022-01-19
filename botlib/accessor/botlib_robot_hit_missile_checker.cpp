#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_collide.h>
#include <botlib_missile.h>
#include <botlib_robot.h>
#include <botlib_robot_hit_missile_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

namespace {

inline bool check(GameObject* obj,
                  Robot* robot)
{
    return obj->type() == GameObjectType::MISSILE &&
           obj->alive() &&
           static_cast<Missile*>(obj)->side() != robot->side();
}

} // end of unnamed namespace

RobotHitMissileChecker::RobotHitMissileChecker(GameMap* map,
                                               Robot* robot)
    : map_(map)
    , robot_(robot)
{
}

void RobotHitMissileChecker::reset(GameMap* map,
                                   Robot* robot)
{
    map_ = map;
    robot_ = robot;
}

bool RobotHitMissileChecker::run(GameObjectList& objList,
                                 GameObject* obj)
{
    if (!check(obj, robot_))
    {
        return true;
    }

    Missile* missile = static_cast<Missile*>(obj);

    bool collide = checkRectCollideRect(robot_->collideRegion(),
                                        missile->collideRegion());
    if (collide)
    {
        missile->explode(*map_);
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
