#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_game_map.h>
#include <botlib_nonpassthrough_collide_checker.h>
#include <botlib_robot.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Robot::Robot()
    : hp_(0.0f)
    , energy_(0.0f)
    , movingEnabled_(false)
{
}

void Robot::init(const RobotTemplate* t,
                 Side side,
                 const commonlib::Vector2& pos1,
                 const commonlib::Vector2& direction1)
{
    CompositeObject::init(t, pos1, direction1);
    side_ = side;
    initFirePointsAndDirections();
    resetSpeed();
}

void Robot::update(GameMap& map,
                   float timeDelta)
{
    if (movingEnabled_)
    {
        updatePos(map, timeDelta);
    }

    GameObject::update(map, timeDelta);
}

void Robot::setPos(const commonlib::Vector2& pos1)
{
    shiftPos(pos1 - pos_);
}

void Robot::shiftPos(const Vector2& delta)
{
    CompositeObject::shiftPos(delta);
    resetFirePointsAndDirections();
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
    speedX_ = speed() * direction_[0];
    speedY_ = speed() * direction_[1];
}

void Robot::updatePos(GameMap& map,
                      float timeDelta)
{
    Vector2 delta{speedX_ * timeDelta, speedY_ * timeDelta};

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
}

bool Robot::checkNonpassthroughCollide(commonlib::Vector2& delta,
                                       GameMap& map)
{
    using namespace std::placeholders;

    static NonpassthroughCollideChecker checker;
    static GameMap::Accessor accessor = std::bind(
                                            &NonpassthroughCollideChecker::run,
                                            &checker, _1);

    Region<int> area = map.getCollideArea(collideRegion(), delta[0], delta[1]);

    checker.reset(this, delta);
    map.accessRegion(area, accessor);

    delta = checker.delta();

    return checker.collide();
}

void Robot::addHP(float delta)
{
    const RobotTemplate* t = getTemplate();

    if (invincible())
    {
        return;
    }

    hp_ = clamp(hp_+delta, 0.0f, t->hp());
    if (hp_ <= 0.0f)
    {
        setAlive(false);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

