#ifndef INCLUDED_BOTLIB_ROBOT_HIT_MISSILE_CHECKER_H
#define INCLUDED_BOTLIB_ROBOT_HIT_MISSILE_CHECKER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameMap;
class Robot;
class GameObjectDumper;

class RobotHitMissileChecker: public GameMapAccessor {
public:
    RobotHitMissileChecker(GameMap& map,
                           GameObjectDumper& dumper,
                           Robot* robot);

    bool run(GameObject* obj) override;

private:
    GameMap& map_;
    GameObjectDumper& dumper_;
    Robot* robot_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

