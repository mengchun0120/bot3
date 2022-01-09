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

    bool run(GameObjectList& objList,
             GameObject* obj) override;

private:
    inline bool check(GameObject* obj);

private:
    Robot* robot_;
};

bool RobotHitMissileChecker::check(GameObject* obj)
{
    return obj->type() == GameObjectType::MISSILE &&
           obj->alive() &&
           static_cast<Missile*>(obj)->side() != robot_->side();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

