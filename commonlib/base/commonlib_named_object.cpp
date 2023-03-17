#include <commonlib_json_param.h>
#include <commonlib_named_object.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace commonlib {

void NamedObject::init(const rapidjson::Value &v,
                       bool requireName)
{
    std::vector<JsonParamPtr> params{
        jsonParam(name_, {"name"}, requireName, k_nonEmptyStrV)
    };

    parse(params, v);
}

void NamedObject::setName(const std::string &name1)
{
    name_ = name1;
}

} // end of namespace commonlib
} // end of namespace mcdane

