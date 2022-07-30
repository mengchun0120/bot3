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
    Goodie();

    ~Goodie() override;

    void init(const GoodieTemplate* t,
              const commonlib::Vector2& pos,
              const commonlib::Vector2& direction,
              bool activated1=false);

    void initPie();

    inline const GoodieTemplate* getTemplate() const;

    inline bool activated() const;

    inline GoodieType goodieType() const;

    void present() const override;

    void update(GameMap& map,
                GameObjectDumper& dumper,
                float delta) override;

    void updateActivated(Player& player,
                         float delta);

    bool canBeDumped(GameMap& map) const override;

    void activate(Player& player);

    void reset();

private:
    float duration_;
    bool activated_;
    ProgressPie* pie_;
};

const GoodieTemplate* Goodie::getTemplate() const
{
    return static_cast<const GoodieTemplate*>(t_);
}

bool Goodie::activated() const
{
    return activated_;
}

GoodieType Goodie::goodieType() const
{
    return getTemplate()->goodieType();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
