#include <commonlib_json_param.h>

namespace mcdane {
namespace commonlib {

void parse(std::vector<JsonParamPtr>& params,
           const rapidjson::Document& doc)
{
    for (auto it = params.begin(); it != params.end(); ++it)
    {
        (*it)->parse(doc);
    }
}

} // end of namespace commonlib
} // end of namespace mcdane

