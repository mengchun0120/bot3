#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <commonlib_vertex_array.h>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>
#include <botlib_progress_pie_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ProgressPieTemplate::ProgressPieTemplate()
    : va_(nullptr)
    , iconRect_(nullptr)
    , iconImage_(nullptr)
{
}

void ProgressPieTemplate::init(const rapidjson::Value& v,
                               const VertexArrayLib& vertexArrayLib,
                               const RectLib& rectLib,
                               const TextureLib& textureLib)
{
    std::string vertexArrayName, iconRectName, iconImageName;
    std::vector<JsonParamPtr> params{
        jsonParam(radius_, "radius", true, gt(0.0f)),
        jsonParam(vertexArrayName, "vertexArray", true, k_nonEmptyStrV),
        jsonParam(backgroundColor_, "backgroundColor"),
        jsonParam(frontColor_, "frontColor"),
        jsonParam(alpha_, "alpha", true, gt(0.0f) && le(1.0f)),
        jsonParam(iconRectName, "iconRect", false, k_nonEmptyStrV),
        jsonParam(iconImageName, "iconImage", false, k_nonEmptyStrV),
    };

    parse(params, v);

    initVertexArray(vertexArrayName, vertexArrayLib);
    initIcon(iconRectName, iconImageName, rectLib, textureLib);
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

void ProgressPieTemplate::initIcon(const std::string& iconRectName,
                                   const std::string& iconImageName,
                                   const RectLib& rectLib,
                                   const TextureLib& textureLib)
{
    if (iconRectName.empty() && iconImageName.empty())
    {
        return;
    }

    if (!iconRectName.empty() && iconImageName.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "iconRect not set");
    }
    else if (iconRectName.empty() && !iconImageName.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "iconImage not set");
    }

    iconRect_ = rectLib.search(iconRectName);
    if (!iconRect_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find rect " + iconRectName);
    }


    iconImage_ = textureLib.search(iconImageName);
    if (!iconImage_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find texture " + iconImageName);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
