#include <memory>
#include <algorithm>
#include <commonlib_exception.h>
#include <commonlib_algorithm.h>
#include <commonlib_color.h>
#include <botlib_constants.h>
#include <botlib_simple_shader_program.h>
#include <botlib_tex_pos_array.h>
#include <botlib_shape.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Shape::Shape(
    std::initializer_list<Point2> positions)
{
    load(positions);
}

Shape::Shape(
    std::initializer_list<Point2> positions,
    const TexPosArray& texPosArray)
{
    load(
        positions,
        texPosArray);
}

Shape::Shape(
    const Point2* positions,
    unsigned int numPositions,
    const Point2* texPos)
{
    load(
        positions,
        numPositions,
        texPos);
}

void Shape::load(
    std::initializer_list<Point2> positions)
{
    unsigned int numPositions =
        count(positions.begin(), positions.end());

    if (numPositions == 0)
    {
        THROW_EXCEPT(
            InvalidArgumentException,
            "positions is empty");
    }

    std::unique_ptr<Point2> posPtr(new Point2[numPositions]);

    std::copy(
        positions.begin(),
        positions.end(),
        posPtr.get());

    load(
        posPtr.get(),
        numPositions);
}

void Shape::load(
    std::initializer_list<Point2> positions,
    const TexPosArray& texPosArray)
{
    unsigned int numPositions =
        count(positions.begin(), positions.end());

    if (numPositions == 0)
    {
        THROW_EXCEPT(
            InvalidArgumentException,
            "positions is empty");
    }

    if (numPositions != texPosArray.numVertices())
    {
        THROW_EXCEPT(
            InvalidArgumentException,
            "texPos size doesn't match position size");
    }

    std::unique_ptr<Point2> posPtr(new Point2[numPositions]);

    std::copy(
        positions.begin(),
        positions.end(),
        posPtr.get());

    load(
        posPtr.get(),
        numPositions,
        texPosArray.texPos());
}

void
Shape::load(
    const Point2* positions,
    unsigned int numPositions,
    const Point2* texPos)
{
    if (!positions)
    {
        THROW_EXCEPT(
            InvalidArgumentException,
            "positions is null");
    }

    if (numPositions == 0)
    {
        THROW_EXCEPT(
            InvalidArgumentException,
            "numPositions is zero");
    }

    if (!texPos)
    {
        va_.load({
            BufferBlock{
                positions,
                numPositions,
                Constants::POS_SIZE,
                0
            }
        });
    }
    else
    {
        va_.load({
            BufferBlock{
                positions,
                numPositions,
                Constants::POS_SIZE,
                0
            },

            BufferBlock{
                texPos,
                numPositions,
                Constants::TEXPOS_SIZE,
                0
            }
        });
    }
}

rapidjson::Value
Shape::toJson(
    rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember(
        "class",
        "Shape",
        allocator);

    v.AddMember(
        "base",
        NamedObject::toJson(allocator),
        allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

