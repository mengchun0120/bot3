#include <sstream>
#include <commonlib_log.h>
#include <botlib_player.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Player::init(const PlayerTemplate* t,
                  const commonlib::Vector2 pos1,
                  const commonlib::Vector2 direction1)
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

} // end of namespace botlib
} // end of namespace mcdane

