#ifndef INCLUDED_BOTLIB_GOODIE_GENERATOR_H
#define INCLUDED_BOTLIB_GOODIE_GENERATOR_H

#include <vector>
#include <random>
#include <commonlib_vector.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class Goodie;

class GoodieGenerator {
    struct Item {
        const GoodieTemplate* t_;
        float weight_;
    };

    using Distribution = std::uniform_real_distribution<float>;

public:
    GoodieGenerator();

    ~GoodieGenerator() = default;

    void init(const GoodieTemplateLib& lib);

    Goodie* generate(float prob,
                     const commonlib::Vector2& pos);

private:
    void initBase(const GoodieTemplateLib& lib);

    void initRandomGenerator();

    const GoodieTemplate* getTemplate();

private:
    std::vector<Item> base_;
    std::default_random_engine generator_;
    Distribution distribution_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

