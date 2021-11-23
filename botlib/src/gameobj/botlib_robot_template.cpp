#include <utility>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_robot_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

RobotTemplate::RobotTemplate(float hp,
                             float armor,
                             float energy,
                             float rechargeRate,
                             float collideBreath,
                             std::vector<Component>&& components,
                             std::vector<commonlib::Vector2>&& firePoints)
    : CompositeObjectTemplate(
            GameObjectType::ROBOT,
            collideBreath,
            false,
            std::forward<std::vector<Component>>(components))
    , hp_(hp)
    , armor_(armor)
    , energy_(energy)
    , rechargeRate_(rechargeRate)
    , firePoints_(firePoints)
{
    if (hp_ <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid hp " + toString(hp_));
    }

    if (armor_ <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid armor " + toString(armor_));
    }

    if (energy_ <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid energy " + toString(energy_));
    }

    if (rechargeRate_ <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid recharge-rate " + toString(rechargeRate_));
    }
}

} // end of namespace botlib
} // end of namespace mcdane

