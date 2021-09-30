#include <commonlib_exception.h>
#include <botlib_game_object.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObject::GameObject()
    : t_(nullptr)
    , alive_(true)
{
}

GameObject::GameObject(const GameObjectTemplate* t,
                       float x,
                       float y)
{
    init(t, x, y);
}

void GameObject::init(const GameObjectTemplate* t,
                      float x,
                      float y)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "t is null");
    }

    t_ = t;
    GameObject::setPos(x, y);
    alive_ = true;
}

void GameObject::setPos(float x,
                        float y)
{
    pos_[0] = x;
    pos_[1] = y;
}

} // end of namespace botlib
} // end of namespace mcdane

