#include <commonlib_json_param.h>

namespace mcdane {
namespace commonlib {

void parse(std::vector<JsonParamPtr>& params,
           const rapidjson::Value& v)
{
    for (auto it = params.begin(); it != params.end(); ++it)
    {
        (*it)->parse(v);
    }
}

} // end of namespace commonlib
} // end of namespace mcdane

