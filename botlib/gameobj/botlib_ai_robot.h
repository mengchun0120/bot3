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
              const commonlib::Vector2& pos1,
              const commonlib::Vector2& direction1);

    inline const AIRobotTemplate* getTemplate() const;

    std::string toString() const override;

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;
};

const AIRobotTemplate* AIRobot::getTemplate() const
{
    return static_cast<const AIRobotTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

