#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <commonlib_vertex_array.h>
#include <botlib_progress_bar_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ProgressBarTemplate::init(const rapidjson::Value &v,
                               const VertexArrayLib &vertexArrayLib)
{
    std::string vertexArrayName;
    std::string borderVertexArrayName;
    std::vector<JsonParamPtr> params{
        jsonParam(width_, "width", true, gt(0.0f)),
        jsonParam(height_, "height", true, gt(0.0f)),
        jsonParam(frontColor_, "frontColor"),
        jsonParam(backgroundColor_, "backgroundColor"),
        jsonParam(vertexArrayName, "vertexArray", true, k_nonEmptyStrV),
        jsonParam(alpha_, "alpha", true, gt(0.0f) && le(1.0f)),
        jsonParam(borderVertexArrayName, {"border", "vertexArray"},
                  true, k_nonEmptyStrV),
        jsonParam(borderColor_, {"border", "color"})
    };

    parse(params, v);

    va_ = vertexArrayLib.search(vertexArrayName);
    if (!va_)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find vertexArray " + vertexArrayName);
    }

    borderVertexArray_ = vertexArrayLib.search(borderVertexArrayName);
    if (!borderVertexArray_)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find vertexArray " + borderVertexArrayName);
    }

    numBlocks_ = (va_->numVertices(0) - 2) / 2;
}

} // end of namespace botlib
} // end of namespace mcdane

