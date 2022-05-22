#ifndef INCLUDED_BOTLIB_PLAYER_TEMPLATE_H
#define INCLUDED_BOTLIB_PLAYER_TEMPLATE_H

#include <botlib_robot_template.h>

namespace mcdane {
namespace botlib {

class PlayerTemplate: public RobotTemplate {
public:
    PlayerTemplate() = default;

    void init(const std::string& playerTemplateFile,
              const MissileTemplateLib& missileTemplateLib,
              const ComponentTemplateLib& componentTemplateLib);

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

