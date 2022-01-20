#include <commonlib_log.h>
#include <botlib_rectangle.h>
#include <botlib_rect_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

RectParser::RectParser()
    : params_{
        jsonParam(width_, "width", true, gt(0.0f)),
        jsonParam(height_, "height", true, gt(0.0f)),
        jsonParam(hasTexture_, "hasTexture")
      }
{
}

Rectangle* RectParser::operator()(const rapidjson::Value& v)
{
    hasTexture_ = false;
    parse(params_, v);

    Rectangle* rect= hasTexture_ ?
                         new Rectangle(width_, height_, TexRectangle()) :
                         new Rectangle(width_, height_);

    return rect;
}

} // end of namespace botlib
} // end of namespace mcdane

