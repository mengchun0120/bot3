#include <commonlib_log.h>
#include <commonlib_json_param.h>
#include <botlib_chase_shoot_ai_param.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ChaseShootAIParam::init(const rapidjson::Value &v)
{
    std::vector<JsonParamPtr> params{
        jsonParam(chaseDuration_, "chaseDuration", true, gt(0.0f)),
        jsonParam(directionChangeInterval_, "directionChangeInterval", true,
                  gt(0.0f)),
        jsonParam(shootDuration_, "shootDuration", true, gt(0.0f)),
        jsonParam(chaseProb_, "chaseProb", true, ge(0.0f) && le(1.0f)),
        jsonParam(stopChaseDist_, "stopChaseDist", true, gt(0.0f))
    };

    parse(params, v);
}

} // end of namespace botlib
} // end of namespace mcdane
