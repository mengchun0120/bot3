#ifndef INCLUDED_BOTLIB_GOODIE_H
#define INCLUDED_BOTLIB_GOODIE_H

#include <botlib_composite_object.h>
#include <botlib_goodie_template.h>

namespace mcdane {
namespace botlib {

class Player;
class ProgressPie;

class Goodie: public CompositeObject {
public:
    Goodie() = default;

    Goodie(const GoodieTemplate* t,
           const commonlib::Vector2& pos,
           const commonlib::Vector2& direction);

    ~Goodie() override;

    void init(const GoodieTemplate* t,
              const commonlib::Vector2& pos,
              const commonlib::Vector2& direction);

    inline const GoodieTemplate* getTemplate() const;

    inline GoodieType goodieType() const;

    void present() const override;

    bool canBeDumped(GameMap& map) const override;
};

const GoodieTemplate* Goodie::getTemplate() const
{
    return static_cast<const GoodieTemplate*>(t_);
}

GoodieType Goodie::goodieType() const
{
    return getTemplate()->goodieType();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

