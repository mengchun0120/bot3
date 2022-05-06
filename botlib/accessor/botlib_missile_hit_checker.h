#ifndef INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H
#define INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class Missile;
class GameObjectDumper;

class MissileHitChecker: public GameMapAccessor {
public:
    MissileHitChecker(Missile* missile,
                      bool inflictDamage,
                      GameObjectDumper* dumper=nullptr);

    inline bool collide() const;

    bool run(GameMap& map,
             GameObject* obj) override;

private:
    void doDamage(GameMap& map,
                  GameObject* obj);

private:
    bool collide_;
    bool inflictDamage_;
    Missile* missile_;
    GameObjectDumper* dumper_;
};

bool MissileHitChecker::collide() const
{
    return collide_;
}

} // end of namespace botlib
} // end of namespace mcdane


#endif
