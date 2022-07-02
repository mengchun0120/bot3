#ifndef INCLUDED_BOTLIB_GOODIE_EFFECT_H
#define INCLUDED_BOTLIB_GOODIE_EFFECT_H

#include <botlib_goodie_template.h>

namespace mcdane {
namespace botlib {

class GoodieEffect {
public:
    GoodieEffect() = default;

    void init(const GoodieTemplate* t);

    inline GoodieEffect* prev();

    inline const GoodieEffect* prev() const;

    inline void setPrev(GoodieEffect* prev1);

    inline GoodieEffect* next();

    inline const GoodieEffect* next() const;

    inline void setNext(GoodieEffect* next1);

    inline const GoodieTemplate* getTemplate() const;

    inline GoodieType type() const;

    void reset();

    bool update(Player& player,
                float timeDelta);

private:
    GoodieEffect* prev_;
    GoodieEffect* next_;
    const GoodieTemplate* t_;
    float duration_;
};

GoodieEffect* GoodieEffect::prev()
{
    return prev_;
}

const GoodieEffect* GoodieEffect::prev() const
{
    return prev_;
}

void GoodieEffect::setPrev(GoodieEffect* prev1)
{
    prev_ = prev1;
}

GoodieEffect* GoodieEffect::next()
{
    return next_;
}

const GoodieEffect* GoodieEffect::next() const
{
    return next_;
}

void GoodieEffect::setNext(GoodieEffect* next1)
{
    next_ = next1;
}

const GoodieTemplate* GoodieEffect::getTemplate() const
{
    return t_;
}

GoodieType GoodieEffect::type() const
{
    return t_->goodieType();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

