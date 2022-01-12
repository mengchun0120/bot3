#ifndef INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H
#define INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class Missile;

class MissileHitChecker: public GameMapAccessor {
public:
    MissileHitChecker() = default;

    MissileHitChecker(Missile* missile,
                      bool inflictDamage);

    inline bool collide() const;

    void reset(Missile* missile,
               bool inflictDamage);

    bool run(GameObjectList& objList,
             GameObject* obj) override;

private:
    void doDamage(GameObject* obj);

private:
    bool collide_;
    bool inflictDamage_;
    Missile* missile_;
};

bool MissileHitChecker::collide() const
{
    return collide_;
}

} // end of namespace botlib
} // end of namespace mcdane


#endif
