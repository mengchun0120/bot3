#include <commonlib_log.h>
#include <botlib_progress_pie.h>
#include <botlib_goodie.h>
#include <botlib_player.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Goodie::Goodie(const GoodieTemplate* t,
               const commonlib::Vector2& pos,
               const commonlib::Vector2& direction)
{
    init(t, pos, direction);
}

Goodie::~Goodie()
{
}

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

bool Goodie::canBeDumped(GameMap& map) const
{
    return false;
}

} // end of namespace botlib
} // end of namespace mcdane

