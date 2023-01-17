#ifndef INCLUDED_BOTLIB_AI_ROBOT_H
#define INCLUDED_BOTLIB_AI_ROBOT_H

#include <botlib_ai_robot_template.h>
#include <botlib_robot.h>

namespace mcdane {
namespace botlib {

class AI;

class AIRobot: public Robot {
public:
    AIRobot();

    ~AIRobot() override;

    void init(const AIRobotTemplate* t,
              const commonlib::Vector2& pos1,
              const commonlib::Vector2& direction1,
              GameObjItemDeleter itemDeleter=nullptr);

    inline const AIRobotTemplate* getTemplate() const;

    void update(UpdateContext& cxt) override;

    void toJson(rapidjson::Value& v,
                rapidjson::Document::AllocatorType& allocator) override;

private:
    AI* ai_;
};

const AIRobotTemplate* AIRobot::getTemplate() const
{
    return static_cast<const AIRobotTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

