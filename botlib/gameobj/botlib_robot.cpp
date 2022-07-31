#include <sstream>
#include <algorithm>
#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map.h>
#include <botlib_passthrough_collide_checker.h>
#include <botlib_missile.h>
#include <botlib_game_object_dumper.h>
#include <botlib_robot.h>

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

void Robot::init(const RobotTemplate* t,
                 Side side,
                 const Vector2& pos1,
                 const Vector2& direction1)
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
}

void Robot::present() const
{
    CompositeObject::present();
    hpIndicator_.present();
}

void Robot::update(GameMap& map,
                   GameObjectDumper& dumper,
                   float timeDelta)
{
    if (state_ == GameObjectState::ALIVE)
    {
        timeSinceLastShoot_ += timeDelta;

        if (movingEnabled_)
        {
            updatePos(map, dumper, timeDelta);
        }

        if (state_ == GameObjectState::ALIVE && shootingEnabled_)
        {
            updateShooting(map, dumper);
        }
    }
    else if (state_ == GameObjectState::DYING)
    {
        dyingTime_ += timeDelta;
        if (dyingTime_ >= getTemplate()->dyingDuration())
        {
            dumper.add(this);
        }
        else
        {
            setAlpha(1.0f - dyingTime_ / getTemplate()->dyingDuration());
        }
    }

    GameObject::update(map, dumper, timeDelta);
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
    if (state_ != GameObjectState::ALIVE)
    {
        return;
    }

    if (invincible() or delta == 0.0f)
    {
        return;
    }

    if (delta > 0.0f)
    {
        refillHP(delta);
    }
    else
    {
        doDamage(-delta);
    }

    hpIndicator_.reset(pos(), hpRatio());
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

void Robot::resetSpeed()
{
    speed_ = speedNorm_ * direction_;
}

void Robot::updatePos(GameMap& map,
                      GameObjectDumper& dumper,
                      float timeDelta)
{
    Vector2 delta = speed_ * timeDelta;
    map.checkCollision(delta, this);

    shiftPos(delta);
    map.repositionObj(this);

    checkPassthroughCollide(map, dumper);
}

void Robot::updateShooting(GameMap& map,
                           GameObjectDumper& dumper)
{
    if (timeSinceLastShoot_ < fireIntervalMS())
    {
        return;
    }

    shoot(map, dumper);
}

void Robot::checkPassthroughCollide(GameMap& map,
                                    GameObjectDumper& dumper)
{
    PassthroughCollideChecker checker(map, dumper, this);
    Region<int> r = map.getCollideArea(collideRegion());
    map.accessRegion(r, checker);
}

void Robot::shoot(GameMap& map,
                  GameObjectDumper& dumper)
{
    for (unsigned int i = 0; i < firePoints_.size(); ++i)
    {
        Missile* missile = new Missile();
        missile->init(getTemplate()->missileTemplate(),
                      side_,
                      firePoints_[i],
                      fireDirections_[i],
                      damageFactor_);

        map.addObj(missile);
    }

    timeSinceLastShoot_ = 0.0f;
}

void Robot::refillHP(float hpIncrease)
{
    hp_ = std::min(hp_ + hpIncrease, getTemplate()->hp());
}

void Robot::doDamage(float damage)
{
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
        }
    }
}

void Robot::resetArmorReduceRatio()
{
    constexpr float MIN_RATIO = 0.1f;
    constexpr float MAX_RATIO = 1.0f;
    constexpr float SLOPE = (MIN_RATIO - MAX_RATIO) / 1000.0f;

    armorReduceRatio_ = clamp(MAX_RATIO + SLOPE * armor_, MIN_RATIO, MAX_RATIO);
}

} // end of namespace botlib
} // end of namespace mcdane

