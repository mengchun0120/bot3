#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_object_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObjectTemplate::GameObjectTemplate(GameObjectType t,
                                       float width,
                                       float height,
                                       float collideBreath,
                                       bool invincible)
{
    init(t, width, height, collideBreath, invincible);
}

void GameObjectTemplate::init(GameObjectType t,
                              float width,
                              float height,
                              float collideBreath,
                              bool invincible)
{
    if (!isValidGameObjectType(t))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid type " + toString(static_cast<int>(t)));
    }

    if (width <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid width " + toString(width));
    }

    if (height <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid height " + toString(height));
    }

    type_ = t;
    width_ = width;
    height_ = height;
    collideBreath_ = collideBreath;
    invincible_ = invincible;
}

} // end of namespace botlib
} // end of namespace mcdane

