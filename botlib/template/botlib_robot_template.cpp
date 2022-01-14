#include <utility>
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

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::botlib::RobotTemplate& t)
{
    using namespace mcdane::botlib;

    os << "RobotTemplate(" << &t
       << ", hp=" << t.hp()
       << ", armor=" << t.armor()
       << ", speed=" << t.speed()
       << ", energy=" << t.energy()
       << ", rechargeRate=" << t.rechargeRate()
       << ", fireIntervalMS=" << t.fireIntervalMS()
       << ", missileTemplate=" << *t.missileTemplate()
       << ", firePoints=" << t.firePoints()
       << ", fireDirections=" << t.fireDirections()
       << ", CompositeTemplate=" << static_cast<const CompositeObjectTemplate&>(t)
       << ")";

    return os;
}

} // end of namespace std


