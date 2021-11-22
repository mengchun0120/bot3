#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_object_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObjectTemplate::GameObjectTemplate(GameObjectType t,
                                       float span,
                                       float collideBreath,
                                       bool invincible)
{
    init(t, span, collideBreath, invincible);
}

void GameObjectTemplate::init(GameObjectType t,
                              float span,
                              float collideBreath,
                              bool invincible)
{
    if (!isValidGameObjectType(t))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid type " + toString(static_cast<int>(t)));
    }

    if (span < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid span " + toString(span));
    }

    type_ = t;
    span_ = span;
    collideBreath_ = collideBreath;
    invincible_ = invincible;
}

} // end of namespace botlib
} // end of namespace mcdane

