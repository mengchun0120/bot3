#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <commonlib_vertex_array.h>
#include <botlib_direction_pie_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void DirectionPieConfig::init(const std::string &fileName,
                              const VertexArrayLib &vertexArrayLib)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    std::string directionLineName, directionCircleName;
    std::vector<JsonParamPtr> params{
        jsonParam(radius_, {"radius"}, true, gt(0.0f)),
        jsonParam(color_, {"color"}, true),
        jsonParam(alpha_, {"alpha"}, true, gt(0.0f) && le(1.0f)),
        jsonParam(directionLineName, {"directionLineVertexArray"},
                  true, k_nonEmptyStrV),
        jsonParam(directionCircleName, {"directionCircleVertexArray"},
                  true, k_nonEmptyStrV),
    };

    parse(params, doc);

    directionLine_ = vertexArrayLib.search(directionLineName);
    if (!directionLine_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find VertexArray " + directionLineName);
    }

    directionCircle_ = vertexArrayLib.search(directionCircleName);
    if (!directionCircle_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find VertexArray " + directionCircleName);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
