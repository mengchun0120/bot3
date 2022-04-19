#include <iostream>
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
    Vector2 d = normalize(dest_ - pos_);
    Robot::setDirection(d);
}

void Player::update(GameMap& map,
                    float delta)
{
    Robot::update(map, delta);
}

void Player::updatePos(GameMap& map,
                       float delta)
{
    if (!movingEnabled_)
    {
        return;
    }

    if (fuzzyEqual(pos_, dest_, 0.1f))
    {
        setMovingEnabled(false);
        return;
    }

    Robot::updatePos(map, delta);
}

} // end of namespace botlib
} // end of namespace mcdane

