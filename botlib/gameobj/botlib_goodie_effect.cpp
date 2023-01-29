#include <commonlib_log.h>
#include <botlib_goodie_effect.h>

namespace mcdane {
namespace botlib {

GoodieEffect::GoodieEffect(GoodieType type1, float lifeSpan1)
{
    init(type1, lifeSpan1);
}

void GoodieEffect::init(GoodieType type1, float lifeSpan1)
{
    type_ = type1;
    lifeSpan_ = lifeSpan1;
    timeToLive_ = lifeSpan1;
    finishedRatio_ = 0.0f;
}

void GoodieEffect::reset()
{
    timeToLive_ = lifeSpan_;
    finishedRatio_ = 0.0f;
}

void GoodieEffect::reduceTimeToLive(float timeDelta)
{
    timeToLive_ -= timeDelta;
    finishedRatio_ = timeToLive_ > 0.0f ? (1.0f - timeToLive_/lifeSpan_) : 1.0f;
}

} // end of namespace botlib
} // end of namespace mcdane
