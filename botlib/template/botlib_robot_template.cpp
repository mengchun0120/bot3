#include <utility>
#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_out_utils.h>
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

} // end of namespace botlib
} // end of namespace mcdane

