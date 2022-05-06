#include <algorithm>
#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <botlib_player.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Player::init(const PlayerTemplate* t,
                  const Vector2& pos1,
                  const Vector2& direction1)
{
    Robot::init(t, Side::PLAYER, pos1, direction1);
}

rapidjson::Value Player::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "Player", allocator);
    v.AddMember("base", Robot::toJson(allocator), allocator);

    return v;
}

void Player::setDest(const Vector2& dest1)
{
    dest_ = dest1;
    Vector2 dist = dest_ - pos_;
    Robot::setDirection(normalize(dist));
    updateMoveTime(dist);
}

void Player::update(GameMap& map,
                    GameObjectDumper& dumper,
                    float timeDelta)
{
    Robot::update(map, dumper, timeDelta);
}

void Player::updatePos(GameMap& map,
                       GameObjectDumper& dumper,
                       float timeDelta)
{
    bool reachDest = false;
    if (timeToDest_ <= timeDelta)
    {
        timeDelta = timeToDest_;
        timeToDest_ = 0.0f;
        reachDest = true;
    }
    else
    {
        timeToDest_ -= timeDelta;
    }

    Robot::updatePos(map, dumper, timeDelta);

    if (reachDest)
    {
        setMovingEnabled(false);
    }
}

void Player::updateMoveTime(const Vector2& dist)
{
    constexpr float VERY_SMALL = 1.0e-6f;
    Vector2 absDist = abs(dist);
    Vector2 absSpeed = abs(speed_);
    float timeToDestX = 0.0f, timeToDestY = 0.0f;

    if (absSpeed[0] > VERY_SMALL)
    {
        timeToDestX = absDist[0] / absSpeed[0];
    }

    if (absSpeed[1] > VERY_SMALL)
    {
        timeToDestY = absDist[1] / absSpeed[1];
    }

    timeToDest_ = std::max(timeToDestX, timeToDestY);
}

} // end of namespace botlib
} // end of namespace mcdane

