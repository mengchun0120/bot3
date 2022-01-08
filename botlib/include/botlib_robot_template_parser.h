#ifndef INCLUDED_BOTLIB_ROBOT_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_ROBOT_TEMPLATE_PARSER_H

#include <botlib_composite_object_template_parser.h>

namespace mcdane {
namespace botlib {

class MissileTemplate;

class RobotTemplateParser: public CompositeObjectTemplateParser {
public:
    RobotTemplateParser(
            const MissileTemplateLib& missileTemplateLib,
            const ComponentTemplateLib& componentTemplateLib);

    void load(const rapidjson::Value& v);

protected:
    float hp_;
    float armor_;
    float speed_;
    float energy_;
    float rechargeRate_;
    const MissileTemplate* missileTemplate_;
    std::string missileName_;
    float fireIntervalMS_;
    std::vector<commonlib::Vector2> firePoints_;
    std::vector<commonlib::Vector2> fireDirections_;
    std::vector<commonlib::JsonParamPtr> params_;
    const MissileTemplateLib& missileTemplateLib_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

