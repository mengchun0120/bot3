#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <botlib_goodie_template.h>
#include <botlib_goodie_effect.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GoodieEffect::init(const GoodieTemplate* t)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "GoodieTemplate is null");
    }

    t_ = t;
    prev_ = nullptr;
    next_ = nullptr;
    duration_ = 0.0f;
}

void GoodieEffect::reset()
{
    duration_ = 0.0f;
}

bool GoodieEffect::update(Player& player,
                          float timeDelta)
{
    duration_ += timeDelta;

    if (duration_ < t_->duration())
    {
        return false;
    }

    const DeactivateGoodieAction& action = t_->deactivateAction();
    if (action)
    {
        action(player);
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

