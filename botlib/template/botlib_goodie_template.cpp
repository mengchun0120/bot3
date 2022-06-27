#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_goodie_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GoodieTemplate::init(GoodieType type1,
                          const rapidjson::Value& v,
                          const ComponentTemplateLib& componentTemplateLib)
{
    if (!isValid(type1))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid GoodieType");
    }

    type_ = type1;

    std::vector<JsonParamPtr> params{
        jsonParam(duration_, {"duration"}, true, ge(0.0f)),
        jsonParam(weight_, {"weight"}, true, gt(0.0f)),
        jsonParam(factor_, {"factor"}, false)
    };

    parse(params, v);

    CompositeObjectTemplate::init(GameObjectType::GOODIE, v, componentTemplateLib);
}

} // end of namespace botlib
} // end of namespace mcdane

