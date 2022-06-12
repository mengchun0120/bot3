#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_goodie_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GoodieTemplate::init(const rapidjson::Value& v,
                          const ComponentTemplateLib& componentTemplateLib)
{
    std::string goodieTypeStr;
    std::vector<JsonParamPtr> params{
        jsonParam(goodieTypeStr, {"type"}, true, k_nonEmptyStrV),
        jsonParam(duration_, {"duration"}, true, ge(0.0f)),
        jsonParam(weight_, {"weight"}, true, gt(0.0f))
    };

    parse(params, v);

    CompositeObjectTemplate::init(GameObjectType::GOODIE, v, componentTemplateLib);
}

} // end of namespace botlib
} // end of namespace mcdane

