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

std::string Player::toString() const
{
    std::ostringstream oss;

    oss << "Player(" << this
        << ", Base=" << Robot::toString()
        << ")";

    return oss.str();
}

} // end of namespace botlib
} // end of namespace mcdane

