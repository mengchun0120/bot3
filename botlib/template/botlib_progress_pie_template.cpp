#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <commonlib_vertex_array.h>
#include <botlib_progress_pie_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ProgressPieTemplate::init(const rapidjson::Value& v,
                               const VertexArrayLib& vertexArrayLib)
{
    std::string vertexArrayName;
    std::vector<JsonParamPtr> params{
        jsonParam(vertexArrayName, "vertexArray", true, k_nonEmptyStrV),
        jsonParam(backgroundColor_, "backgroundColor"),
        jsonParam(frontColor_, "frontColor"),
        jsonParam(alpha_, "alpha", true, gt(0.0f) && le(1.0f))
    };

    parse(params, v);

    va_ = vertexArrayLib.search(vertexArrayName);
    if (!va_)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find VertexArray " + vertexArrayName);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
