#ifndef INCLUDED_BOTLIB_ROBOT_ACTION_H
#define INCLUDED_BOTLIB_ROBOT_ACTION_H

#include <ostream>

namespace mcdane {
namespace botlib {

enum class RobotAction {
    CHASE,
    SHOOT,
    NONE
};

const std::string& toString(RobotAction action);

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    mcdane::botlib::RobotAction action);

} // end of namespace std

#endif

