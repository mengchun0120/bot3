#ifndef INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H
#define INCLUDED_BOTLIB_MISSILE_HIT_CHECKER_H

#include <botlib_missile.h>
#include <botlib_robot.h>

namespace mcdane {
namespace botlib {

class AIRobot;

class MissileHitChecker {
public:
    MissileHitChecker(UpdateContext &cxt,
                      Missile &missile,
                      bool inflictDamage=false);

    inline bool collide() const;

    bool operator()(GameObject *obj);

private:
    inline bool check(GameObject *obj) const;

    inline bool isEnemyRobot(GameObject *obj) const;

    void doDamage(GameObject *obj);

    void generateGoodie(AIRobot *robot);

private:
    UpdateContext &cxt_;
    Missile &missile_;
    bool inflictDamage_;
    bool collide_;
};

bool MissileHitChecker::collide() const
{
    return collide_;
}

bool MissileHitChecker::check(GameObject *obj) const
{
    return obj != static_cast<GameObject*>(&missile_) &&
           obj->state() == GameObjectState::ALIVE &&
            (obj->type() == GameObjectType::TILE ||
             isEnemyRobot(obj));
}

bool MissileHitChecker::isEnemyRobot(GameObject *obj) const
{
    return obj->type() == GameObjectType::ROBOT &&
           static_cast<Robot*>(obj)->side() != missile_.side();
}



} // end of namespace botlib
} // end of namespace mcdane

#endif
