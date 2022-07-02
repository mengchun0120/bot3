#include <commonlib_log.h>
#include <botlib_goodie.h>
#include <botlib_player.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Goodie::init(const GoodieTemplate* t,
                  const commonlib::Vector2& pos,
                  const commonlib::Vector2& direction)
{
    CompositeObject::init(t, pos, direction);
}

void Goodie::present() const
{
    CompositeObject::present();
}

void Goodie::update(GameMap& map,
                    GameObjectDumper& dumper,
                    float delta)
{
}

bool Goodie::canBeDumped(GameMap& map) const
{
    return false;
}

void Goodie::activate(Player& player)
{
    const GoodieTemplate* t = getTemplate();
    const ActivateGoodieAction& action = t->activateAction();
    if (action)
    {
        action(t, player);
    }

    if (isLasting(t->goodieType()))
    {
        player.addGoodieEffect(t);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

