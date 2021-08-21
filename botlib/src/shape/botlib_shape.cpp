#include <memory>
#include <algorithm>
#include <commonlib_exception.h>
#include <commonlib_algorithm.h>
#include <botlib_constants.h>
#include <botlib_shape.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Shape::Shape(std::initializer_list<commonlib::Point3> positions)
{
    load(positions);
}

Shape::Shape(std::initializer_list<commonlib::Point3> positions,
             std::initializer_list<commonlib::Point2> texPos)
{
    load(positions, texPos);
}

Shape::Shape(Point3* positions,
             unsigned int numPositions,
             Point2* texPos)
{
    load(positions, numPositions, texPos);
}

void Shape::load(std::initializer_list<commonlib::Point3> positions)
{
    unsigned int numPositions = count(positions.begin(), positions.end());
    if (numPositions == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "positions is empty");
    }

    std::unique_ptr<Point3> posPtr(new Point3[numPositions]);

    std::copy(positions.begin(), positions.end(), posPtr.get());
    load(posPtr.get(), numPositions);
}

void Shape::load(std::initializer_list<commonlib::Point3> positions,
                 std::initializer_list<commonlib::Point2> texPos)
{
    unsigned int numPositions = count(positions.begin(), positions.end());
    if (numPositions == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "positions is empty");
    }

    if (numPositions != count(texPos.begin(), texPos.end()))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "texPos size doesn't match position size");
    }

    std::unique_ptr<Point3> posPtr(new Point3[numPositions]);
    std::unique_ptr<Point2> texPosPtr(new Point2[numPositions]);

    std::copy(positions.begin(), positions.end(), posPtr.get());
    std::copy(texPos.begin(), texPos.end(), texPosPtr.get());
    load(posPtr.get(), numPositions, texPosPtr.get());
}

void Shape::load(Point3* positions,
                 unsigned int numPositions,
                 Point2* texPos)
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
        va_.load({BufferBlock{positions, numPositions, Constants::POS_SIZE, 0}});
    }
    else
    {
        va_.load({BufferBlock{positions, numPositions, Constants::POS_SIZE, 0},
                  BufferBlock{texPos, numPositions, Constants::TEXPOS_SIZE, 0}});
    }
}

} // end of namespace botlib
} // end of namespace mcdane

