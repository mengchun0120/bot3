#ifndef INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H
#define INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H

#include <botlib_missile.h>
#include <botlib_robot.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class MissileHitChecker: public GameMapAccessor {
public:
    void reset(Missile* missile);

    inline bool collide() const;

    bool run(GameObjectList& objList,
             GameObject* obj) override;

private:
    inline bool check(GameObject* obj);

    inline bool isSameSideRobot(GameObject* obj);

private:
    bool collide_;
    Missile* missile_;
};

bool MissileHitChecker::collide() const
{
    return collide_;
}

bool MissileHitChecker::check(GameObject* obj)
{
    return obj->alive() &&
           (obj->type() == GameObjectType::TILE ||
            isSameSideRobot(obj));
}

bool MissileHitChecker::isSameSideRobot(GameObject* obj)
{
    return obj->type() == GameObjectType::ROBOT &&
           static_cast<Robot*>(obj)->side() == missile_->side();
}

} // end of namespace botlib
} // end of namespace mcdane


#endif
