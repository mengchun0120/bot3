#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <commonlib_string_utils.h>
#include <botlib_context.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_passthrough_collide_checker.h>
#include <botlib_missile.h>
#include <botlib_robot.h>
#include <botlib_goodie.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Robot::Robot()
    : hp_(0.0f)
    , energy_(0.0f)
    , movingEnabled_(false)
    , shootingEnabled_(false)
{
}

Robot::~Robot()
{
    if (!monitors_.empty())
    {
        notifyAndClearMonitors();
    }
}

void Robot::init(const RobotTemplate* t,
                 Side side,
                 const Vector2& pos1,
                 const Vector2& direction1,
                 GameObjItemDeleter itemDeleter)
{
    CompositeObject::init(t, pos1, direction1);
    side_ = side;
    hp_ = t->hp();
    initFirePointsAndDirections();
    speedNorm_ = t->speed();
    energy_ = t->energy();
    armor_ = t->armor();
    fireIntervalMS_ = t->fireIntervalMS();
    damageFactor_ = 1.0f;
    resetSpeed();
    hpIndicator_.reset(pos(), hpRatio());
    timeSinceLastShoot_ = 0.0f;
    dyingTime_ = 0.0f;
    movingEnabled_ = false;
    shootingEnabled_ = false;
    resetArmorReduceRatio();
    if (itemDeleter)
    {
        monitors_.setDeleter(itemDeleter);
    }
}

void Robot::present() const
{
    CompositeObject::present();
    if (Context::gameConfig().showHPIndicator())
    {
        hpIndicator_.present();
    }
}

void Robot::update(UpdateContext& cxt)
{
    if (state_ == GameObjectState::ALIVE)
    {
        timeSinceLastShoot_ += cxt.timeDelta();

        if (movingEnabled_)
        {
            updatePos(cxt);
        }

        if (state_ == GameObjectState::ALIVE && shootingEnabled_)
        {
            updateShooting(cxt);
        }

        updateEnergy(cxt.timeDelta());
    }
    else if (state_ == GameObjectState::DYING)
    {
        dyingTime_ += cxt.timeDelta();
        if (dyingTime_ >= getTemplate()->dyingDuration())
        {
            cxt.dumper().add(this);
        }
        else
        {
            setAlpha(1.0f - dyingTime_ / getTemplate()->dyingDuration());
        }
    }

    GameObject::update(cxt);
}

void Robot::shiftPos(const Vector2& delta)
{
    CompositeObject::shiftPos(delta);
    resetFirePointsAndDirections();
    hpIndicator_.shiftPos(delta);
}

void Robot::setDirection(const Vector2& direction1)
{
    CompositeObject::setDirection(direction1);
    resetFirePointsAndDirections();
    resetSpeed();
}

void Robot::setMovingEnabled(bool b)
{
    movingEnabled_ = b;
}

void Robot::addHP(float delta)
{
    if (state_ != GameObjectState::ALIVE || delta <= 0.0f)
    {
        return;
    }

    hp_ = std::min(hp_ + delta, getTemplate()->hp());
    hpIndicator_.reset(pos(), hpRatio());
}

void Robot::doDamage(float damage, UpdateContext& cxt)
{
    if (state_ != GameObjectState::ALIVE || damage <= 0.0f || invincible())
    {
        return;
    }

    if (armor_ > 0.0f)
    {
        armor_ = std::max(armor_ - armorReduceRatio_ * damage, 0.0f);
        resetArmorReduceRatio();
    }
    else
    {
        hp_ = std::max(hp_ - damage, 0.0f);
        if (hp_ <= 0.0f)
        {
            setState(GameObjectState::DYING);
            notifyAndClearMonitors();
        }

        hpIndicator_.reset(pos(), hpRatio());
    }
}

void Robot::setShootingEnabled(bool b)
{
    shootingEnabled_ = b;
}

bool Robot::canBeDumped(GameMap& map) const
{
    return state_ == GameObjectState::DYING && !map.canSee(this);
}

void Robot::setSpeedNorm(float speedNorm1)
{
    if (speedNorm1 < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid speedNorm");
    }

    speedNorm_ = speedNorm1;
}

void Robot::setFireIntervalMS(float fireIntervalMS1)
{
    if (fireIntervalMS1 < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid fireIntervalMS");
    }

    fireIntervalMS_ = fireIntervalMS1;
}

void Robot::setArmor(float armor1)
{
    if (armor1 < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid armor");
    }

    armor_ = armor1;
}

void Robot::setDamageFactor(float factor)
{
    if (factor < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid factor");
    }

    damageFactor_ = factor;
}

void Robot::resetSpeed()
{
    speed_ = speedNorm_ * direction_;
}

void Robot::addMonitor(GameObject* obj,
                       GameObjItemPool& pool)
{
    GameObjectItem* item = pool.alloc(obj);
    monitors_.pushBack(item);
}

void Robot::removeMonitor(GameObject* obj)
{
    GameObjectItem* i = monitors_.first();

    for (; i; i = i->next())
    {
        if (i->item() == obj)
        {
            break;
        }
    }

    if (i)
    {
        monitors_.remove(i);
    }
}

void Robot::initFirePointsAndDirections()
{
    const RobotTemplate* t = getTemplate();

    firePoints_.resize(t->numFirePoints());
    fireDirections_.resize(t->numFirePoints());
    resetFirePointsAndDirections();
}

void Robot::shiftFirePoints(const Vector2& delta)
{
    for (std::size_t i = 0; i < firePoints_.size(); ++i)
    {
        firePoints_[i] += delta;
    }
}

void Robot::resetFirePointsAndDirections()
{
    const RobotTemplate* t = getTemplate();

    for (std::size_t i = 0; i < firePoints_.size(); ++i)
    {
        Vector2 p = t->firePoint(i);

        rotate(p[0], p[1], direction_[0], direction_[1]);
        firePoints_[i] = pos_ + p;

        Vector2 d = t->fireDirection(i);

        rotate(d[0], d[1], direction_[0], direction_[1]);
        fireDirections_[i] = d;
    }
}

void Robot::updatePos(UpdateContext& cxt)
{
    GameMap& map = *(cxt.map());
    Vector2 delta = speed_ * cxt.timeDelta();

    map.checkCollision(delta, this);
    shiftPos(delta);
    map.repositionObj(this);

    checkPassthroughCollide(cxt);
}

void Robot::updateShooting(UpdateContext& cxt)
{
    if (timeSinceLastShoot_ < fireIntervalMS())
    {
        return;
    }

    shoot(cxt);
}

void Robot::checkPassthroughCollide(UpdateContext& cxt)
{
    GameMap& map = *(cxt.map());
    PassthroughCollideChecker checker(cxt, this);
    Region<int> r = map.getCollideArea(collideRegion());
    map.traverse(r, checker, {0, 2});
}

void Robot::shoot(UpdateContext& cxt)
{
    GameMap& map = *(cxt.map());
    const MissileTemplate* t = getTemplate()->missileTemplate();

    for (unsigned int i = 0; i < firePoints_.size() && energy_ >= t->energyCost(); ++i)
    {
        Missile* missile = new Missile();
        missile->init(t, side_, firePoints_[i], fireDirections_[i], damageFactor_);
        energy_ -= t->energyCost();

        map.addObj(missile);
    }

    timeSinceLastShoot_ = 0.0f;
}

void Robot::resetArmorReduceRatio()
{
    constexpr float MIN_RATIO = 0.1f;
    constexpr float MAX_RATIO = 1.0f;
    constexpr float SLOPE = (MIN_RATIO - MAX_RATIO) / 1000.0f;

    armorReduceRatio_ = clamp(MAX_RATIO + SLOPE * armor_, MIN_RATIO, MAX_RATIO);
}

void Robot::updateEnergy(float timeDelta)
{
    energy_ = std::min(energy_ + timeDelta * getTemplate()->rechargeRate(),
                       getTemplate()->energy());
}

void Robot::notifyAndClearMonitors()
{
    for (GameObjectItem* i = monitors_.first(); i; i = i->next())
    {
        i->item()->notify(this);
    }

    monitors_.clear();
}

} // end of namespace botlib
} // end of namespace mcdane

