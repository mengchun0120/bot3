#ifndef INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H
#define INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class Missile;

class MissileHitChecker: public GameMapAccessor {
public:
    MissileHitChecker(Missile* missile);

    inline bool collide() const;

    void reset(Missile* missile);

    bool run(GameObjectList& objList,
             GameObject* obj) override;

private:
    bool collide_;
    Missile* missile_;
};

bool MissileHitChecker::collide() const
{
    return collide_;
}

} // end of namespace botlib
} // end of namespace mcdane


#endif
