#ifndef INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H
#define INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H

#include <botlib_missile.h>
#include <botlib_robot.h>

namespace mcdane {
namespace botlib {

class MissileHitChecker {
public:
    void reset(Missile* missile);

    inline bool collide() const;

    bool run(GameObject* o);

private:
    inline bool check(GameObject* o);

    inline bool isSameSideRobot(GameObject* o);

private:
    bool collide_;
    Missile* missile_;
};

bool MissileHitChecker::collide() const
{
    return collide_;
}

bool MissileHitChecker::check(GameObject* o)
{
    return o->alive() &&
           (o->type() == GameObjectType::TILE ||
            isSameSideRobot(o));
}

bool MissileHitChecker::isSameSideRobot(GameObject* o)
{
    return o->type() == GameObjectType::ROBOT &&
           static_cast<Robot*>(o)->side() == missile_->side();
}

} // end of namespace botlib
} // end of namespace mcdane


#endif
