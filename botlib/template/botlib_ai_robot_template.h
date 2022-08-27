#ifndef INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_H
#define INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_H

#include <botlib_robot_template.h>

namespace mcdane {
namespace botlib {

class AIRobotTemplate: public RobotTemplate {
public:
    AIRobotTemplate();

    ~AIRobotTemplate() = default;

    void init(const std::string& name,
              const rapidjson::Value& v,
              const MissileTemplateLib& missileTemplateLib,
              const ComponentTemplateLib& componentTemplateLib);

    inline float goodieProb() const;

    inline const std::string& aiAlgorithm() const;

    inline const std::string& aiName() const;

private:
    float goodieProb_;
    std::string aiAlgorithm_;
    std::string aiName_;
};

float AIRobotTemplate::goodieProb() const
{
    return goodieProb_;
}

const std::string& AIRobotTemplate::aiAlgorithm() const
{
    return aiAlgorithm_;
}

const std::string& AIRobotTemplate::aiName() const
{
    return aiName_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

