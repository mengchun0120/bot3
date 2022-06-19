#include <commonlib_log.h>
#include <botlib_goodie.h>

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
    LOG_INFO << "goodie " << id() << " present" << LOG_END;
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

} // end of namespace botlib
} // end of namespace mcdane

