#ifndef INCLUDED_COMMONLIB_RANDOM_H
#define INCLUDED_COMMONLIB_RANDOM_H

#include <random>

namespace mcdane {
namespace commonlib {

class Random {
public:
    Random();

    Random(int seed);

    int randomInt(int min, int max);

    float randomFloat(float min=0.0f, float max=1.0f);

private:
    std::default_random_engine engine_;
    std::uniform_real_distribution<double> distr_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif
