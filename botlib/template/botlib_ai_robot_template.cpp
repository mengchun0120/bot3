#include <commonlib_json_param.h>
#include <botlib_ai_robot_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

AIRobotTemplate::AIRobotTemplate()
    : goodieProb_(0.0f)
{
}

void AIRobotTemplate::init(const rapidjson::Value& v,
                           const MissileTemplateLib& missileTemplateLib,
                           const ComponentTemplateLib& componentTemplateLib)
{
    std::vector<JsonParamPtr> params{
        jsonParam(goodieProb_, "goodieProb", false, ge(0.0f)),
        jsonParam(aiAlgorithm_, {"ai", "algorithm"}, true, k_nonEmptyStrV),
        jsonParam(aiName_, {"ai", "name"}, true, k_nonEmptyStrV)
    };

    parse(params, v);

    RobotTemplate::init(v, missileTemplateLib, componentTemplateLib);
}

} // end of namespace botlib
} // end of namespace mcdane

