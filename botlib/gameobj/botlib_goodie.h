#ifndef INCLUDED_BOTLIB_GOODIE_H
#define INCLUDED_BOTLIB_GOODIE_H

#include <botlib_composite_object.h>
#include <botlib_goodie_template.h>

namespace mcdane {
namespace botlib {

class Player;

class Goodie: public CompositeObject {
public:
    Goodie() = default;

    ~Goodie() override = default;

    void init(const GoodieTemplate* t,
              const commonlib::Vector2& pos,
              const commonlib::Vector2& direction);

    inline const GoodieTemplate* getTemplate() const;

    void present() const override;

    void update(GameMap& map,
                GameObjectDumper& dumper,
                float delta) override;

    bool canBeDumped(GameMap& map) const override;

    void activate(Player& player);
};

const GoodieTemplate* Goodie::getTemplate() const
{
    return static_cast<const GoodieTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

