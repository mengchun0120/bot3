#ifndef INCLUDED_BOTLIB_ROBOT_HIT_MISSILE_CHECKER_H
#define INCLUDED_BOTLIB_ROBOT_HIT_MISSILE_CHECKER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class Robot;

class RobotHitMissileChecker: public GameMapAccessor {
public:
    RobotHitMissileChecker(Robot* robot);

    void reset(Robot* robot);

    bool run(GameObjectList& objList,
             GameObject* obj) override;

private:
    Robot* robot_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

