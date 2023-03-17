#include <commonlib_json_param.h>

namespace mcdane {
namespace commonlib {

JsonParam::JsonParam(const std::vector<std::string> &path,
                     bool required) noexcept
    : path_(path)
    , required_(required)
{
}

void parse(std::vector<JsonParamPtr> &params,
           const rapidjson::Value &v)
{
    for (auto it = params.begin(); it != params.end(); ++it)
    {
        (*it)->parse(v);
    }
}

} // end of namespace commonlib
} // end of namespace mcdane

