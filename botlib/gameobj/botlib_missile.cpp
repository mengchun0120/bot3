#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>
#include <botlib_particle_effect.h>
#include <botlib_tile.h>
#include <botlib_missile_hit_checker.h>
#include <botlib_target_finder.h>
#include <botlib_missile.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Missile::Missile()
    : CompositeObject()
    , target_(nullptr)
{
}

Missile::Missile(const MissileTemplate* t,
                 Side side,
                 const commonlib::Vector2& pos1,
                 const commonlib::Vector2& direction1,
                 float damageFactor)
{
    init(t, side, pos1, direction1, damageFactor);
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

    showExplodeEffect(cxt);
    cxt.dumper().add(this);

    if (getTemplate()->splitCount() > 0)
    {
        shootSplitMissile(cxt);
    }
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
    if (getTemplate()->guided())
    {
        updateForTarget(cxt);
    }

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

void Missile::updateForTarget(UpdateContext& cxt)
{
    if (!target_)
    {
        searchTarget(cxt);
    }
    else
    {
        calibrateDirection();
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

void Missile::showExplodeEffect(UpdateContext& cxt)
{
    ParticleEffect* effect = cxt.factory().createParticleEffect(
                                    getTemplate()->explodeEffectTemplate(),
                                    pos_);
    cxt.map()->addObj(effect);
}

void Missile::setTarget(Robot* robot, UpdateContext& cxt)
{
    target_ = robot;
    robot->addMonitor(this, cxt.itemPool());
    calibrateDirection();
}

void Missile::searchTarget(UpdateContext& cxt)
{
    Region<int> area = searchRegion(cxt.map());
    Side enemySide = side() == Side::AI ? Side::PLAYER : Side::AI;
    GameObjItemList targets(cxt.itemPool().deleter());
    TargetFinder finder(enemySide, 1, targets, cxt.itemPool());

    cxt.map()->traverse(area, finder, GameMap::LAYER_ROBOT, 1);

    finder.getTargets();
    if (!targets.empty())
    {
        setTarget(static_cast<Robot*>(targets.first()->item()), cxt);
    }
}

void Missile::calibrateDirection()
{
    Vector2 targetDirection = target_->pos() - pos();
    if (!align(targetDirection, direction()))
    {
        setDirection(targetDirection.normalize());
    }
}

Region<int> Missile::searchRegion(GameMap* map)
{
    float searchBreath = getTemplate()->searchBreath();
    Region<float> r(pos_[0] - searchBreath, pos_[0] + searchBreath,
                    pos_[1] - searchBreath, pos_[1] + searchBreath);
    return map->getCoverArea(r);
}

void Missile::shootSplitMissile(UpdateContext& cxt)
{
    int splitCount = getTemplate()->splitCount();
    const MissileTemplate* t = getTemplate()->splitMissileTemplate();
    const std::vector<Vector2>& directions = getTemplate()->splitMissileDirections();

    for (int i = 0; i < splitCount; ++i)
    {
        Missile* m = cxt.factory().createMissile(t, side_, pos_, directions[i]);
        cxt.map()->addObj(m);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

