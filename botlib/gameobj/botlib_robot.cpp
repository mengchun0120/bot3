#include <sstream>
#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map.h>
#include <botlib_nonpassthrough_collide_checker.h>
#include <botlib_robot_hit_missile_checker.h>
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
    , lastShootTime_(Clock::now())
{
}

void Robot::init(const RobotTemplate* t,
                 Side side,
                 const Vector2& pos1,
                 const Vector2& direction1)
{
    CompositeObject::init(t, pos1, direction1);
    side_ = side;
    hp_ = getTemplate()->hp();
    initFirePointsAndDirections();
    resetSpeed();
    hpIndicator_.reset(pos(), hpRatio());
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
        if (movingEnabled_)
        {
            updatePos(map, dumper, timeDelta);
        }

        if (shootingEnabled_)
        {
            updateShooting(map, dumper);
        }
    }
    else if (state_ == GameObjectState::DYING)
    {
        //TODO
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

    const RobotTemplate* t = getTemplate();

    if (invincible())
    {
        return;
    }

    hp_ = clamp(hp_+delta, 0.0f, t->hp());
    if (hp_ <= 0.0f)
    {
        setState(GameObjectState::DEAD);
    }

    hpIndicator_.reset(pos(), hpRatio());
}

void Robot::setShootingEnabled(bool b)
{
    shootingEnabled_ = b;
}

rapidjson::Value Robot::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "Robot", allocator);
    v.AddMember("side", jsonVal(stringVal(side_), allocator), allocator);
    v.AddMember("hp", hp_, allocator);
    v.AddMember("speed", jsonVal(speed_, allocator), allocator);
    v.AddMember("energy", energy_, allocator);
    v.AddMember("movingEnabled", movingEnabled_, allocator);
    v.AddMember("shootingEnabled", shootingEnabled_, allocator);
    v.AddMember("base", CompositeObject::toJson(allocator), allocator);

    return v;
}

bool Robot::canBeDumped(GameMap& map) const
{
    return state_ != GameObjectState::DUMPED &&
           (state_ == GameObjectState::DEAD ||
            (state_ == GameObjectState::DYING && !map.canSee(this)));
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
    speed_ = speedNorm() * direction_;
}

void Robot::updatePos(GameMap& map,
                      GameObjectDumper& dumper,
                      float timeDelta)
{
    Vector2 delta = speed_ * timeDelta;

    bool collideBoundary = checkRectCollideBoundary(delta,
                                                    collideRegion(),
                                                    map.boundary(),
                                                    delta);

    bool collideObjs = checkNonpassthroughCollide(delta, map);
    if (collideBoundary || collideObjs)
    {
        setMovingEnabled(false);
    }

    shiftPos(delta);
    map.repositionObj(this);

    checkCollideMissile(map, dumper);
}

bool Robot::checkNonpassthroughCollide(Vector2& delta,
                                       GameMap& map)
{
    NonpassthroughCollideChecker checker(this, delta);
    Region<int> area = map.getCollideArea(collideRegion(), delta[0], delta[1]);

    map.accessRegion(area, checker);

    delta = checker.delta();

    return checker.collide();
}

void Robot::checkCollideMissile(GameMap& map,
                                GameObjectDumper& dumper)
{
    RobotHitMissileChecker checker(map, dumper, this);
    Region<int> r = map.getCollideArea(collideRegion());
    map.accessRegion(r, checker);
}

void Robot::updateShooting(GameMap& map,
                           GameObjectDumper& dumper)
{
    TimePoint thisTime = Clock::now();

    if (timeDistMs(lastShootTime_, thisTime) < fireIntervalMS())
    {
        return;
    }

    shoot(map, dumper, thisTime);
}

void Robot::shoot(GameMap& map,
                  GameObjectDumper& dumper,
                  const TimePoint& t)
{
    for (unsigned int i = 0; i < firePoints_.size(); ++i)
    {
        Missile* missile = new Missile();
        missile->init(getTemplate()->missileTemplate(),
                      side_,
                      firePoints_[i],
                      fireDirections_[i]);

        map.addObj(missile);
    }

    lastShootTime_ = t;
}

} // end of namespace botlib
} // end of namespace mcdane

