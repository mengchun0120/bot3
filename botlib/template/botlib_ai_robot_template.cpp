#include <commonlib_json_param.h>
#include <botlib_ai_robot_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

AIRobotTemplate::AIRobotTemplate()
    : goodieProb_(0.0f)
{
}

void AIRobotTemplate::init(const std::string& name,
                           const rapidjson::Value& v,
                           const MissileTemplateLib& missileTemplateLib,
                           const ComponentTemplateLib& componentTemplateLib,
                           const SkillTemplateLib& skillTemplateLib)
{
    std::vector<JsonParamPtr> params{
        jsonParam(goodieProb_, "goodieProb", false, ge(0.0f)),
        jsonParam(aiAlgorithm_, {"ai", "algorithm"}, true, k_nonEmptyStrV),
        jsonParam(aiName_, {"ai", "name"}, true, k_nonEmptyStrV)
    };

    parse(params, v);

    RobotTemplate::init(name, v, missileTemplateLib, componentTemplateLib,
                        skillTemplateLib);
}

} // end of namespace botlib
} // end of namespace mcdane

