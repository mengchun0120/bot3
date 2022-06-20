#ifndef INCLUDED_BOTLIB_GOODIE_GENERATOR_H
#define INCLUDED_BOTLIB_GOODIE_GENERATOR_H

#include <vector>
#include <random>
#include <memory>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class GoodieGenerator {
    struct Item {
        const GoodieTemplate* t_;
        float weight_;
    };

    using Distribution = std::uniform_real_distribution<float>;

public:
    GoodieGenerator();

    ~GoodieGenerator() = default;

    void init(GoodieTemplateLib& lib);

    const GoodieTemplate* generate();

private:
    void initBase(GoodieTemplateLib& lib);

    void initRandomGenerator();

private:
    std::vector<Item> base_;
    std::default_random_engine generator_;
    std::shared_ptr<Distribution> distribution_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

