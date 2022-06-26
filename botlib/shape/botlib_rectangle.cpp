#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <botlib_rectangle.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void validateParamForRect(float width1,
                          float height1)
{
    if (width1 < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "width is negative");
    }

    if (height1 < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "height is negative");
    }
}

Rectangle::Rectangle(float width1,
                     float height1)
{
    load(width1, height1);
}

Rectangle::Rectangle(float width1,
                     float height1,
                     const TexRectangle& texRect)
{
    load(width1, height1, texRect);
}

void Rectangle::init(const rapidjson::Value& v,
                     bool requireName)
{
    float width1, height1;
    bool hasTexture;
    std::vector<JsonParamPtr> params{
        jsonParam(width1, "width", true, gt(0.0f)),
        jsonParam(height1, "height", true, gt(0.0f)),
        jsonParam(hasTexture, "hasTexture")
    };

    parse(params, v);

    if (hasTexture)
    {
        load(width1, height1, TexRectangle());
    }
    else
    {
        load(width1, height1);
    }
}

void Rectangle::load(float width,
                     float height)
{
    validateParamForRect(width, height);

    width_ = width;
    height_ = height;

    float w = width/2.0f;
    float h = height/2.0f;

    Polygon::load({
        Point2{0.0f, 0.0f},
        Point2{w, h},
        Point2{-w, h},
        Point2{-w, -h},
        Point2{w, -h},
        Point2{w, h}
    });
}

void Rectangle::load(float width,
                     float height,
                     const TexRectangle& texRect)
{
    validateParamForRect(width, height);

    width_ = width;
    height_ = height;

    float w = width/2.0f;
    float h = height/2.0f;

    std::vector<Point2> positions({
        Point2{0.0f, 0.0f},
        Point2{w, h},
        Point2{-w, h},
        Point2{-w, -h},
        Point2{w, -h},
        Point2{w, h}
    });

    Polygon::load(positions.data(), positions.size(), texRect.texPos());
}

} // end of namespace botlib
} // end of namespace mcdane

