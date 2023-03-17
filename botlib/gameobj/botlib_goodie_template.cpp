#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_goodie_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GoodieTemplate::init(GoodieType goodieType1,
                          const std::string &name,
                          const rapidjson::Value &v,
                          const ComponentTemplateLib &componentTemplateLib)
{
    CompositeObjectTemplate::init(GameObjectType::GOODIE, name,
                                  v, componentTemplateLib);

    if (!isValid(goodieType1))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid GoodieType");
    }

    goodieType_ = goodieType1;

    std::string pieName;
    std::vector<JsonParamPtr> params{
        jsonParam(duration_, {"duration"}, true, ge(0.0f)),
        jsonParam(weight_, {"weight"}, true, gt(0.0f)),
        jsonParam(factor_, {"factor"}, false),
    };

    parse(params, v);
}

} // end of namespace botlib
} // end of namespace mcdane

