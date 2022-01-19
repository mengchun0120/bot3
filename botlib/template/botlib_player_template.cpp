#include <sstream>
#include <commonlib_log.h>
#include <botlib_player_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

PlayerTemplate::PlayerTemplate(float hp1,
                               float armor1,
                               float speed1,
                               float energy1,
                               float rechargeRate1,
                               float collideBreath1,
                               const MissileTemplate* missileTemplate1,
                               float fireIntervalMS1,
                               std::vector<Component>&& components,
                               std::vector<Vector2>&& firePoints,
                               std::vector<Vector2>&& fireDirections)
    : RobotTemplate(hp1,
                    armor1,
                    speed1,
                    energy1,
                    rechargeRate1,
                    collideBreath1,
                    missileTemplate1,
                    fireIntervalMS1,
                    std::forward<std::vector<Component>>(components),
                    std::forward<std::vector<Vector2>>(firePoints),
                    std::forward<std::vector<Vector2>>(fireDirections))
{
}

void PlayerTemplate::init(float hp1,
                          float armor1,
                          float speed1,
                          float energy1,
                          float rechargeRate1,
                          float collideBreath1,
                          const MissileTemplate* missileTemplate1,
                          float fireIntervalMS1,
                          std::vector<Component>&& components,
                          std::vector<Vector2>&& firePoints,
                          std::vector<Vector2>&& fireDirections)
{
    LOG_DEBUG << "numComponents=" << components.size() << LOG_END;

    RobotTemplate::init(hp1,
                        armor1,
                        speed1,
                        energy1,
                        rechargeRate1,
                        collideBreath1,
                        missileTemplate1,
                        fireIntervalMS1,
                        std::forward<std::vector<Component>>(components),
                        std::forward<std::vector<Vector2>>(firePoints),
                        std::forward<std::vector<Vector2>>(fireDirections));

}

std::string PlayerTemplate::toString() const
{
    std::ostringstream oss;

    oss << "PlayerTemplate(Base=" << RobotTemplate::toString() << ")";

    return oss.str();
}

rapidjson::Value PlayerTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "PlayerTemplate", allocator);
    v.AddMember("base", RobotTemplate::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane
