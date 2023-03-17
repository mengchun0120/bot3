#include <cstdlib>
#include <commonlib_math_utils.h>

namespace mcdane {
namespace commonlib {

void rotate(float &x,
            float &y,
            float directionX,
            float directionY)
{
    float x1 = x * directionX - y * directionY;
    float y1 = x * directionY + y * directionX;
    x = x1;
    y = y1;
}

float sign(float x)
{
    if (x == 0.0f)
    {
        return 0.0f;
    }

    return x < 0.0f ? -1.0f : 1.0f;
}

int randInt(int min, int max)
{
    double r = static_cast<double>(rand()) * (max - min) / RAND_MAX + min;
    return static_cast<int>(floor(r));
}

} // end of namespace commonlib
} // end of namespace mcdane

