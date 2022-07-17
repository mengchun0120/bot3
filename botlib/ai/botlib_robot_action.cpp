#include <botlib_robot_action.h>

namespace mcdane {
namespace botlib {

std::string k_robotActionStr[] = {
    "chase",
    "shoot",
    "none"
};

const std::string& toString(RobotAction action)
{
    return k_robotActionStr[static_cast<int>(action)];
}

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    mcdane::botlib::RobotAction action)
{
    return os << mcdane::botlib::toString(action);
}

} // end of namespace std


