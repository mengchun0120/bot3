#ifndef INCLUDED_BOTLIB_PASSTHROUGH_COLLIDE_CHECKER_H
#define INCLUDED_BOTLIB_PASSTHROUGH_COLLIDE_CHECKER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameMap;
class Robot;
class GameObjectDumper;
class Missile;
class Goodie;

class PassthroughCollideChecker: public GameMapAccessor {
public:
    PassthroughCollideChecker(GameMap& map,
                              GameObjectDumper& dumper,
                              Robot* robot);

    bool run(GameObject* obj) override;

private:
    void collideMissile(Missile* missile);

    void collideGoodie(Goodie* goodie);

private:
    GameMap& map_;
    GameObjectDumper& dumper_;
    Robot* robot_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

