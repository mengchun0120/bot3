#ifndef INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H
#define INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H

#include <commonlib_vector.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameMap;
class Missile;
class GameObjectDumper;
class AIRobot;

class MissileHitChecker: public GameMapAccessor {
public:
    MissileHitChecker(GameMap& map,
                      Missile& missile,
                      bool inflictDamage=false,
                      GameObjectDumper* dumper=nullptr);

    inline bool collide() const;

    bool run(GameObject* obj) override;

private:
    void doDamage(GameObject* obj);

    void generateGoodie(AIRobot* robot);

private:
    GameMap& map_;
    Missile& missile_;
    bool inflictDamage_;
    GameObjectDumper* dumper_;
    bool collide_;
};

bool MissileHitChecker::collide() const
{
    return collide_;
}

} // end of namespace botlib
} // end of namespace mcdane


#endif
