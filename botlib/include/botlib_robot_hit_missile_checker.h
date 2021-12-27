#ifndef INCLUDED_BOTLIB_ROBOT_HIT_MISSILE_CHECKER_H
#define INCLUDED_BOTLIB_ROBOT_HIT_MISSILE_CHECKER_H

#include <botlib_missile.h>
#include <botlib_robot.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class RobotHitMissileChecker: public GameMapAccessor {
public:
    void reset(Robot* robot);

    bool run(ItemList& itemList,
             GameMapItem* item) override;

private:
    inline bool check(GameObject* o);

private:
    Robot* robot_;
};

bool RobotHitMissileChecker::check(GameObject* o)
{
    return o->type() == GameObjectType::MISSILE &&
           o->alive() &&
           static_cast<Missile*>(o)->side() != robot_->side();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

