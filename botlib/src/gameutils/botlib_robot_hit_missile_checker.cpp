#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_collide.h>
#include <botlib_robot_hit_missile_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void RobotHitMissileChecker::reset(Robot* robot)
{
    robot_ = robot;
}

bool RobotHitMissileChecker::run(ItemList& itemList,
                                 GameMapItem* item)
{
    GameObject* o = item->obj();

    if (!check(o))
    {
        return true;
    }

    Missile* missile = static_cast<Missile*>(o);

    bool collide = checkRectCollideRect(robot_->collideRegion(),
                                        missile->collideRegion());
    if (collide)
    {
        if (robot_->alive())
        {
            robot_->addHP(-missile->damage());
        }

        missile->setAlive(false);
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

