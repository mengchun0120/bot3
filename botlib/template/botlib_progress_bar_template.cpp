#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <commonlib_vertex_array.h>
#include <botlib_progress_bar_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ProgressBarTemplate::init(const rapidjson::Value& v,
                               const VertexArrayLib& vertexArrayLib)
{
    std::string vertexArrayName;
    std::vector<JsonParamPtr> params{
        jsonParam(width_, "width", true, gt(0.0f)),
        jsonParam(height_, "height", true, gt(0.0f)),
        jsonParam(frontColor_, "frontColor"),
        jsonParam(backgroundColor_, "backgroundColor"),
        jsonParam(vertexArrayName, "vertexArray", true, k_nonEmptyStrV)
    };

    parse(params, v);

    va_ = vertexArrayLib.search(vertexArrayName);
    if (!va_)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find vertexArray " + vertexArrayName);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

