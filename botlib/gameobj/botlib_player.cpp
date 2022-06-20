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
    Robot::updatePos(map, dumper, timeDelta);
}

} // end of namespace botlib
} // end of namespace mcdane

