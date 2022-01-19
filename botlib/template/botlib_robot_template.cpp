#include <utility>
#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_out_utils.h>
#include <commonlib_json_utils.h>
#include <botlib_robot_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

RobotTemplate::RobotTemplate(float hp1,
                             float armor1,
                             float speed1,
                             float energy1,
                             float rechargeRate1,
                             float collideBreath1,
                             const MissileTemplate* missileTemplate1,
                             float fireIntervalMS1,
                             std::vector<Component>&& components,
                             std::vector<Vector2>&& firePoints1,
                             std::vector<Vector2>&& fireDirections1)
    : CompositeObjectTemplate(
        GameObjectType::ROBOT,
        collideBreath1,
        false,
        std::forward<std::vector<Component>>(components))
    , hp_(hp1)
    , armor_(armor1)
    , speed_(speed1)
    , energy_(energy1)
    , rechargeRate_(rechargeRate1)
    , missileTemplate_(missileTemplate1)
    , fireIntervalMS_(fireIntervalMS1)
    , firePoints_(std::forward<std::vector<Vector2>>(firePoints1))
    , fireDirections_(std::forward<std::vector<Vector2>>(fireDirections1))
{
}

void RobotTemplate::init(float hp1,
                         float armor1,
                         float speed1,
                         float energy1,
                         float rechargeRate1,
                         float collideBreath1,
                         const MissileTemplate* missileTemplate1,
                         float fireIntervalMS1,
                         std::vector<Component>&& components,
                         std::vector<Vector2>&& firePoints1,
                         std::vector<Vector2>&& fireDirections1)
{
    CompositeObjectTemplate::init(
                         GameObjectType::ROBOT,
                         collideBreath1,
                         false,
                         std::forward<std::vector<Component>>(components));

    hp_ = hp1;
    armor_ = armor1;
    speed_ = speed1;
    energy_ = energy1;
    rechargeRate_ = rechargeRate1;
    missileTemplate_ = missileTemplate1;
    fireIntervalMS_ = fireIntervalMS1;
    firePoints_ = std::forward<std::vector<Vector2>>(firePoints1);
    fireDirections_ = std::forward<std::vector<Vector2>>(fireDirections1);
}

std::string RobotTemplate::toString() const
{
    std::ostringstream oss;

    oss << "RobotTemplate(hp=" << hp_
        << ", armor=" << armor_
        << ", speed=" << speed_
        << ", energy=" << energy_
        << ", rechargeRate=" << rechargeRate_
        << ", fireIntervalMS=" << fireIntervalMS_
        << ", missileTemplate=" << missileTemplate_->toString()
        << ", firePoints=" << firePoints_
        << ", fireDirections=" << fireDirections_
        << ", Base=" << CompositeObjectTemplate::toString()
        << ")";

    return oss.str();
}

rapidjson::Value RobotTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "RobotTemplate", allocator);
    v.AddMember("hp", hp_, allocator);
    v.AddMember("armor", armor_, allocator);
    v.AddMember("speed", speed_, allocator);
    v.AddMember("energy", energy_, allocator);
    v.AddMember("rechargeRate", rechargeRate_, allocator);
    v.AddMember("fireIntervalMS", fireIntervalMS_, allocator);
    v.AddMember("firePoints", jsonVal(firePoints_, allocator), allocator);
    v.AddMember("fireDirections", jsonVal(fireDirections_, allocator), allocator);
    v.AddMember("missileTemplate", missileTemplate_->toJson(allocator), allocator);
    v.AddMember("base", CompositeObjectTemplate::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

