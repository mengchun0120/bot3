#include <sstream>
#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <commonlib_json_utils.h>
#include <commonlib_string_utils.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_particle_effect.h>
#include <botlib_missile_hit_checker.h>
#include <botlib_game_object_dumper.h>
#include <botlib_missile.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Missile::init(const MissileTemplate* t,
                   Side side,
                   const commonlib::Vector2& pos1,
                   const commonlib::Vector2& direction1,
                   float damageFactor)
{
    CompositeObject::init(t, pos1, direction1);
    side_ = side;
    damage_ = t->damage() * damageFactor;
    resetSpeed();
}

void Missile::update(UpdateContext& cxt)
{
    Vector2 delta = speed_ * cxt.timeDelta();
    GameMap& map = *(cxt.map());

    bool collideBoundary = checkRectCollideBoundary(delta, collideRegion(),
                                                    map.boundary(), delta);

    shiftPos(delta);
    map.repositionObj(this);

    bool collideObjs = checkCollideObjs(cxt);

    if (collideBoundary || collideObjs)
    {
        explode(cxt);
    }

    GameObject::update(cxt);
}

void Missile::setDirection(const commonlib::Vector2& direction1)
{
    CompositeObject::setDirection(direction1);
    resetSpeed();
}

void Missile::explode(UpdateContext& cxt)
{
    GameMap& map = *(cxt.map());
    MissileHitChecker checker(cxt, *this, true);
    Region<int> area = map.getCollideArea(explodeRegion());
    map.accessRegion(area, checker);

    showExplodeEffect(map);
    cxt.dumper()->add(this);
}

void Missile::resetSpeed()
{
    speed_ = speedNorm() * direction_;
}

bool Missile::checkCollideObjs(UpdateContext& cxt)
{
    GameMap& map = *(cxt.map());
    MissileHitChecker checker(cxt, *this);
    Region<int> area = map.getCollideArea(collideRegion());
    map.accessRegion(area, checker);

    return checker.collide();
}

Region<float> Missile::explodeRegion()
{
    float breath = getTemplate()->explodeBreath();
    return Region<float>({x()-breath, x()+breath, y()-breath, y()+breath});
}

void Missile::showExplodeEffect(GameMap& map)
{
    ParticleEffect* explodeEffect = new ParticleEffect();
    explodeEffect->init(getTemplate()->explodeEffectTemplate(), pos_);
    map.addObj(explodeEffect);
}

bool Missile::canBeDumped(GameMap& map) const
{
    return state_ != GameObjectState::DEAD && !map.canSee(this);
}

} // end of namespace botlib
} // end of namespace mcdane

