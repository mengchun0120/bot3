#include <memory>
#include <algorithm>
#include <commonlib_exception.h>
#include <commonlib_algorithm.h>
#include <commonlib_color.h>
#include <commonlib_parse.h>
#include <botlib_constants.h>
#include <botlib_simple_shader_program.h>
#include <botlib_tex_pos_array.h>
#include <botlib_shape.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Shape::Shape(std::initializer_list<Point2> positions)
{
    init(positions);
}

Shape::Shape(std::initializer_list<Point2> positions,
             const TexPosArray &texPosArray)
{
    init(positions, texPosArray);
}

Shape::Shape(const Point2 *positions,
             unsigned int numPositions,
             const Point2 *texPos)
{
    init(positions, numPositions, texPos);
}

Shape::Shape(const std::vector<commonlib::Point2> &positions)
{
    init(positions);
}

Shape::Shape(const std::vector<commonlib::Point2> &positions,
             const std::vector<commonlib::Point2> &texPos)
{
    init(positions, texPos);
}

void Shape::init(std::initializer_list<Point2> positions)
{
    unsigned int numPositions = count(positions.begin(), positions.end());

    if (numPositions == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "positions is empty");
    }

    std::unique_ptr<Point2> posPtr(new Point2[numPositions]);

    std::copy(positions.begin(), positions.end(), posPtr.get());

    init(posPtr.get(), numPositions);
}

void Shape::init(std::initializer_list<Point2> positions,
                 const TexPosArray &texPosArray)
{
    unsigned int numPositions = count(positions.begin(), positions.end());

    if (numPositions == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "positions is empty");
    }

    if (numPositions != texPosArray.numVertices())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "texPos size doesn't match position size");
    }

    std::unique_ptr<Point2> posPtr(new Point2[numPositions]);

    std::copy(positions.begin(), positions.end(), posPtr.get());

    init(posPtr.get(), numPositions, texPosArray.texPos());
}

void Shape::init(const Point2 *positions,
                 unsigned int numPositions,
                 const Point2 *texPos)
{
    if (!positions)
    {
        THROW_EXCEPT(InvalidArgumentException, "positions is null");
    }

    if (numPositions == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "numPositions is zero");
    }

    if (!texPos)
    {
        va_.init({BufferBlock{positions, numPositions, Constants::POS_SIZE, 0}});
    }
    else
    {
        va_.init({
            BufferBlock{positions, numPositions, Constants::POS_SIZE, 0},
            BufferBlock{texPos, numPositions, Constants::TEXPOS_SIZE, 0}});
    }
}

void Shape::init(const std::vector<commonlib::Point2> &positions)
{
    init(positions.data(), positions.size(), nullptr);
}

void Shape::init(const std::vector<commonlib::Point2> &positions,
                 const std::vector<commonlib::Point2> &texPos)
{
    init(positions.data(), positions.size(), texPos.data());
}

} // end of namespace botlib

namespace commonlib {

void parse(botlib::Shape &shape, const rapidjson::Value &v)
{
    std::vector<std::vector<Point2>> vertexArrays;
    parse(vertexArrays, v);

    if (vertexArrays.size() == 0)
    {
        THROW_EXCEPT(ParseException, "vertexArray empty");
    }

    if (vertexArrays.size() == 1)
    {
        shape.init(vertexArrays[0]);
    }
    else
    {
        shape.init(vertexArrays[0], vertexArrays[1]);
    }
}

}

} // end of namespace mcdane

