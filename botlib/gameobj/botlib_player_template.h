#ifndef INCLUDED_BOTLIB_PLAYER_TEMPLATE_H
#define INCLUDED_BOTLIB_PLAYER_TEMPLATE_H

#include <unordered_map>
#include <commonlib_input_map.h>
#include <botlib_robot_template.h>

namespace mcdane {
namespace botlib {

class PlayerTemplate: public RobotTemplate {
public:
    PlayerTemplate() = default;

    void init(const std::string& playerTemplateFile,
              const MissileTemplateLib& missileTemplateLib,
              const ComponentTemplateLib& componentTemplateLib,
              const SkillTemplateLib& skillTemplateLib,
              const commonlib::InputMap& inputMap);

    inline const std::unordered_map<int,SkillType>& inputSkillMap() const;

private:
    void initInputSkillMap(const rapidjson::Value& v,
                           const commonlib::InputMap& inputMap);

protected:
    std::unordered_map<int,SkillType> inputSkillMap_;
};

const std::unordered_map<int,SkillType>& PlayerTemplate::inputSkillMap() const
{
    return inputSkillMap_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

