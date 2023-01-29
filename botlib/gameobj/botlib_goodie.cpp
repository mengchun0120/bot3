#include <commonlib_log.h>
#include <botlib_progress_pie.h>
#include <botlib_goodie.h>
#include <botlib_player.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Goodie::Goodie()
    : activated_(false)
{
}

Goodie::Goodie(const GoodieTemplate* t,
               const commonlib::Vector2& pos,
               const commonlib::Vector2& direction,
               bool activated1)
{
    init(t, pos, direction, activated1);
}

Goodie::~Goodie()
{
}

void Goodie::init(const GoodieTemplate* t,
                  const commonlib::Vector2& pos,
                  const commonlib::Vector2& direction,
                  bool activated1)
{
    CompositeObject::init(t, pos, direction);

    activated_ = activated1;
    if (activated_)
    {
        duration_ = 0.0f;
    }
}

void Goodie::present() const
{
    CompositeObject::present();
}

void Goodie::update(UpdateContext& cxt)
{
}

void Goodie::setPos(const commonlib::Vector2& pos1)
{
    CompositeObject::setPos(pos1);
}

/*void Goodie::updateActivated(Player& player,
                             float delta)
{
    if (!activated_)
    {
        return;
    }

    duration_ += delta;

    float maxDuration = getTemplate()->duration();

    pie_->setFinishedRatio(duration_ / maxDuration);
    if (duration_ < maxDuration)
    {
        return;
    }

    activated_ = false;

    const DeactivateGoodieAction& action = getTemplate()->deactivateAction();
    if (action)
    {
        action(player);
    }
}*/

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
        player.addGoodie(t);
    }
}

void Goodie::reset()
{
    if (!activated_)
    {
        return;
    }

    duration_ = 0.0f;
}

} // end of namespace botlib
} // end of namespace mcdane

