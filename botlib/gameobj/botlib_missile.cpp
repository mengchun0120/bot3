#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>
#include <botlib_particle_effect.h>
#include <botlib_tile.h>
#include <botlib_missile_hit_checker.h>
#include <botlib_missile.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Missile::Missile()
    : target_(nullptr)
{
}

Missile::~Missile()
{
    if (target_)
    {
        target_->removeMonitor(this);
    }
}

void Missile::init(const MissileTemplate* t,
                   Side side,
                   const commonlib::Vector2& pos1,
                   const commonlib::Vector2& direction1,
                   float damageFactor)
{
    CompositeObject::init(t, pos1, direction1);
    side_ = side;
    damage_ = t->damage() * damageFactor;
    livingTime_ = 0.0f;
    resetSpeed();
}

void Missile::update(UpdateContext& cxt)
{
    livingTime_ += cxt.timeDelta();

    if (livingTime_ < getTemplate()->duration())
    {
        updateAlive(cxt);
    }
    else
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
    map.traverse(area, checker, 0, 2);

    if (target_)
    {
        target_->removeMonitor(this);
        target_ = nullptr;
    }

    showExplodeEffect(map);
    cxt.dumper().add(this);
}

bool Missile::canBeDumped(GameMap& map) const
{
    return state_ != GameObjectState::DEAD && !map.canSee(this);
}

void Missile::notify(GameObject* obj)
{
    if (static_cast<Robot*>(obj) == target_)
    {
        target_ = nullptr;
    }
}

void Missile::updateAlive(UpdateContext& cxt)
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
    map.traverse(area, checker, 0, 2);

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

void Missile::setTarget(Robot* robot, GameObjItemPool& pool)
{
    target_ = robot;
    robot->addMonitor(this, pool);
}

} // end of namespace botlib
} // end of namespace mcdane

