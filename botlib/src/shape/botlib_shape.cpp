#include <commonlib_exception.h>
#include <botlib_constants.h>
#include <botlib_shape.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Shape::Shape(Point3* positions,
             unsigned int numPositions,
             Point2* texPos)
{
    load(positions, numPositions, texPos);
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

