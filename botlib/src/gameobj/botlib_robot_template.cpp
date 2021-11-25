#include <utility>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_robot_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

RobotTemplate::RobotTemplate(float hp,
                             float armor,
                             float speed,
                             float energy,
                             float rechargeRate,
                             float collideBreath,
                             std::vector<Component>&& components,
                             std::vector<commonlib::Vector2>&& firePoints,
                             std::vector<commonlib::Vector2>&& fireDirections)
    : CompositeObjectTemplate(
        GameObjectType::ROBOT,
        collideBreath,
        false,
        std::forward<std::vector<Component>>(components))
    , hp_(hp)
    , armor_(armor)
    , speed_(speed)
    , energy_(energy)
    , rechargeRate_(rechargeRate)
    , firePoints_(firePoints)
    , fireDirections_(fireDirections)
{
    if (hp_ < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid hp " + toString(hp_));
    }

    if (armor_ < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid armor " + toString(armor_));
    }

    if (speed_ < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid speed " + toString(speed_));
    }

    if (energy_ < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid energy " + toString(energy_));
    }

    if (rechargeRate_ < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid recharge-rate " + toString(rechargeRate_));
    }

    if (firePoints_.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "firePoints is empty");
    }

    if (fireDirections_.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "fireDirections is empty");
    }

    if (firePoints_.size() != fireDirections_.size())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "firePoints size doesn't match fireDirections size");
    }
}

} // end of namespace botlib
} // end of namespace mcdane

