#include <ctime>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_named_map.h>
#include <botlib_goodie.h>
#include <botlib_goodie_generator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GoodieGenerator::GoodieGenerator()
    : distribution_(0.0f, 1.0f)
{
}

void GoodieGenerator::init(const GoodieTemplateLib& lib)
{
    initBase(lib);
    initRandomGenerator();
}

Goodie* GoodieGenerator::generate(float prob,
                                  const Vector2& pos)
{
    float dice = distribution_(generator_);
    if (dice > prob)
    {
        return nullptr;
    }

    const GoodieTemplate* t = getTemplate();
    Vector2 direction{1.0f, 0.0f};

    Goodie* goodie =  new Goodie();
    goodie->init(t, pos, direction);

    return goodie;
}

void GoodieGenerator::initBase(const GoodieTemplateLib& lib)
{
    base_.resize(lib.size());

    int i = 0;
    float weight = 0.0f;
    auto accessor = [&](const GoodieTemplate& t)->bool
    {
        weight += t.weight();
        base_[i].t_ = &t;
        base_[i].weight_ = weight;
        ++i;
        return true;
    };

    lib.traverse(accessor);
}

void GoodieGenerator::initRandomGenerator()
{
    generator_.seed(time(nullptr));
}

const GoodieTemplate* GoodieGenerator::getTemplate()
{
    float w = distribution_(generator_) * base_.back().weight_;

    for (Item& t: base_)
    {
        if (w <= t.weight_)
        {
            return t.t_;
        }
    }

    return base_.back().t_;
}

} // end of namespace botlib
} // end of namespace mcdane

