#include <commonlib_exception.h>
#include <botlib_game_object.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObject::Deleter GameObject::k_defaultDeleter = [](GameObject* o)->void
{
    delete o;
};

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

void GameObject::update()
{
}

void GameObject::setPos(float x,
                        float y)
{
    pos_[0] = x;
    pos_[1] = y;
}

void GameObject::shiftPos(float deltaX,
                          float deltaY)
{
    pos_[0] += deltaX;
    pos_[1] += deltaY;
}

} // end of namespace botlib
} // end of namespace mcdane

