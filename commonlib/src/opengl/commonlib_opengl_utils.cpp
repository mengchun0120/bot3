#include <commonlib_exception.h>
#include <commonlib_opengl_utils.h>

namespace mcdane {
namespace commonlib {

void validateTexPos(const Point2& texPos)
{
    if (texPos[0] < 0.0f || texPos[0] > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "texPos[0] is out of bound");
    }

    if (texPos[1] < 0.0f || texPos[1] > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "texPos[1] is out of bound");
    }
}

} // end of namespace commonlib
} // end of namespace mcdane


