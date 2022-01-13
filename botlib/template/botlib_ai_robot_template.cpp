#include <utility>
#include <botlib_ai_robot_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

AIRobotTemplate::AIRobotTemplate(float hp1,
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

void AIRobotTemplate::init(float hp1,
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

} // end of namespace botlib
} // end of namespace mcdane

