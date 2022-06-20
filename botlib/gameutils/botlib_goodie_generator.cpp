#include <ctime>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_named_map.h>
#include <botlib_goodie_template.h>
#include <botlib_goodie_generator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GoodieGenerator::init(GoodieTemplateLib& lib)
{
    initBase(lib);
    initRandomGenerator();
}

const GoodieTemplate* GoodieGenerator::generate()
{
    float w = (*distribution_)(generator_);

    for (Item& t: base_)
    {
        if (w <= t.weight_)
        {
            return t.t_;
        }
    }

    return base_.back().t_;
}

void GoodieGenerator::initBase(GoodieTemplateLib& lib)
{
    base_.resize(lib.size());

    int i = 0;
    float weight = 0.0f;
    auto accessor = [&](const GoodieTemplate* t)->bool
    {
        weight += t->weight();
        base_[i].t_ = t;
        base_[i].weight_ = weight;
        ++i;
        return true;
    };

    lib.traverse(accessor);
}

void GoodieGenerator::initRandomGenerator()
{
    generator_.seed(time(nullptr));

    distribution_.reset(new Distribution(0.0f, base_.back().weight_));
}

} // end of namespace botlib
} // end of namespace mcdane

