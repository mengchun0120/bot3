#ifndef INCLUDED_BOTLIB_GOODIE_EFFECT_H
#define INCLUDED_BOTLIB_GOODIE_EFFECT_H

#include <commonlib_linked_item.h>
#include <botlib_goodie_type.h>

namespace mcdane {
namespace botlib {

class GoodieEffect {
public:
    GoodieEffect() = nullptr;

    GoodieEffect(GoodieType type1, float timeToLive1);

    void init(GoodieType type1, float timeToLive1);

    inline GoodieType type() const;

    inline float timeToLive() const;

    void reduceTime(float timeDelta);

private:
    GoodieType type_;
    float timeToLive_;
};

using GoodieEffectItem = commonlib::LinkedItem<GoodieEffect>;

GoodieType GoodieEffect::type() const
{
    return type_;
}

float GoodieEffect::timeToLive() const
{
    return timeToLive_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
