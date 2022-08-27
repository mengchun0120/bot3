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

int Random::randomInt(int min, int max)
{
    return static_cast<int>(floor(distr_(engine_) * (max - min + 1.0) + min));
}

float Random::randomFloat(float min, float max)
{
    return static_cast<float>(distr_(engine_) * (max - min) + min);
}

} // end of namespace commonlib
} // end of namespace mcdane

