#ifndef INCLUDED_BOTLIB_AI_ROBOT_H
#define INCLUDED_BOTLIB_AI_ROBOT_H

#include <botlib_ai_robot_template.h>
#include <botlib_robot.h>

namespace mcdane {
namespace botlib {

class AIRobot: public Robot {
public:
    AIRobot() = default;

    ~AIRobot() override = default;

    void init(const AIRobotTemplate* t,
              const commonlib::Vector2& pos,
              const commonlib::Vector2& direction);

    inline const AIRobotTemplate* getTemplate() const;
};

const AIRobotTemplate* AIRobot::getTemplate() const
{
    return static_cast<const AIRobotTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

