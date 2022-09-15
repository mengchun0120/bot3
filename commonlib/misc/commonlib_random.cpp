#include <ctime>
#include <cmath>
#include <commonlib_random.h>

namespace mcdane {
namespace commonlib {

Random::Random()
    : distr_(0.0, 1.0)
{
    engine_.seed(time(nullptr));
}

Random::Random(int seed)
    : distr_(0.0, 1.0)
{
    engine_.seed(seed);
}

int Random::randomInt(int min,
                      int max)
{
    return static_cast<int>(floor(randomDouble(min, max+1.0)));
}

double Random::randomDouble(double min,
                            double max)
{
    return distr_(engine_) * (max - min) + min;
}

float Random::randomFloat(float min, float max)
{
    return static_cast<float>(randomDouble(min, max));
}

Vector2 Random::randomDirection()
{
    constexpr double TWO_PI = 2.0 * 3.14159265;
    double theta = randomDouble(0.0, TWO_PI);
    return Vector2{static_cast<float>(cos(theta)),
                   static_cast<float>(sin(theta))};
}

} // end of namespace commonlib
} // end of namespace mcdane

