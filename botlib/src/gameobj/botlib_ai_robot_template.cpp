#include <utility>
#include <botlib_ai_robot_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

AIRobotTemplate::AIRobotTemplate(float hp,
                                 float armor,
                                 float speed,
                                 float energy,
                                 float rechargeRate,
                                 float collideBreath,
                                 std::vector<Component>&& components,
                                 std::vector<Vector2>&& firePoints,
                                 std::vector<Vector2>&& fireDirections)
    : RobotTemplate(hp, armor, speed, energy, rechargeRate, collideBreath,
                    std::forward<std::vector<Component>>(components),
                    std::forward<std::vector<Vector2>>(firePoints),
                    std::forward<std::vector<Vector2>>(fireDirections))
{
}


} // end of namespace botlib
} // end of namespace mcdane

