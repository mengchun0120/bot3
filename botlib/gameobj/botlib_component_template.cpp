#include <cmath>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_rectangle.h>
#include <botlib_component_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ComponentTemplate::init(const rapidjson::Value& v,
                             const IconTemplateLib& iconLib)
{
    std::string typeStr, iconName;
    std::vector<JsonParamPtr> params{
        jsonParam(typeStr, "type", true, k_nonEmptyStrV),
        jsonParam(iconName, "icon", true, k_nonEmptyStrV),
        jsonParam(firePos_, "firePos", false)
    };

    parse(params, v);

    type_ = toComponentType(typeStr);

    icon_ = iconLib.search(iconName);
    if (!icon_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find IconTemplate " + iconName);
    }

    resetSpan();
}

void ComponentTemplate::resetSpan()
{
    span_ = static_cast<float>(sqrt(rect()->width() * rect()->width() +
                                    rect()->height() * rect()->height()) / 2.0);
}

} // end of namespace botlib
} // end of namespace mcdane

