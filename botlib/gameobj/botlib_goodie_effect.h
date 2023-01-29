#ifndef INCLUDED_BOTLIB_GOODIE_EFFECT_H
#define INCLUDED_BOTLIB_GOODIE_EFFECT_H

#include <commonlib_linked_item.h>
#include <botlib_goodie_type.h>

namespace mcdane {
namespace botlib {

class GoodieEffect {
public:
    GoodieEffect() = default;

    GoodieEffect(GoodieType type1, float lifeSpan1);

    void init(GoodieType type1, float lifeSpan1);

    inline GoodieType type() const;

    inline float lifeSpan() const;

    inline float timeToLive() const;

    inline float finishedRatio() const;

    inline bool expired() const;

    void reset();

    void reduceTimeToLive(float timeDelta);

private:
    GoodieType type_;
    float lifeSpan_;
    float timeToLive_;
    float finishedRatio_;
};

using GoodieEffectItem = commonlib::LinkedItem<GoodieEffect>;

GoodieType GoodieEffect::type() const
{
    return type_;
}

float GoodieEffect::lifeSpan() const
{
    return lifeSpan_;
}

float GoodieEffect::timeToLive() const
{
    return timeToLive_;
}

float GoodieEffect::finishedRatio() const
{
    return finishedRatio_;
}

bool GoodieEffect::expired() const
{
    return timeToLive_ <= 0.0f;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
