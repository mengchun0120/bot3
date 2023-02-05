#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <commonlib_vertex_array.h>
#include <botlib_icon_template.h>
#include <botlib_progress_pie_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ProgressPieTemplate::ProgressPieTemplate()
    : va_(nullptr)
{
}

void ProgressPieTemplate::init(const rapidjson::Value& v,
                               const VertexArrayLib& vertexArrayLib,
                               const IconTemplateLib& iconLib)
{
    std::string vertexArrayName;
    std::vector<std::string> iconNames;
    std::vector<JsonParamPtr> params{
        jsonParam(radius_, "radius", true, gt(0.0f)),
        jsonParam(vertexArrayName, "vertexArray", true, k_nonEmptyStrV),
        jsonParam(backgroundColor_, "backgroundColor"),
        jsonParam(frontColor_, "frontColor"),
        jsonParam(alpha_, "alpha", true, gt(0.0f) && le(1.0f)),
        jsonParam(iconNames, "icons", false),
    };

    parse(params, v);

    initVertexArray(vertexArrayName, vertexArrayLib);
    initIcons(iconNames, iconLib);
}

void ProgressPieTemplate::initVertexArray(const std::string& vertexArrayName,
                                          const VertexArrayLib& vertexArrayLib)
{
    va_ = vertexArrayLib.search(vertexArrayName);
    if (!va_)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find VertexArray " + vertexArrayName);
    }

    if (va_->numVertices(0) % 3 != 0)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Number of vertices must be multiples of 3");
    }

    numTriangles_ = va_->numVertices(0) / 3;
}

void ProgressPieTemplate::initIcons(const std::vector<std::string>& iconNames,
                                    const IconTemplateLib& iconLib)
{
    if (iconNames.empty())
    {
        return;
    }

    icons_.resize(iconNames.size());
    for (unsigned int i = 0; i < iconNames.size(); ++i)
    {
        icons_[i] = iconLib.search(iconNames[i]);
        if (!icons_[i])
        {
            THROW_EXCEPT(InvalidArgumentException,
                         "Failed to find IconTemplate " + iconNames[i]);
        }
    }
}

} // end of namespace botlib
} // end of namespace mcdane
