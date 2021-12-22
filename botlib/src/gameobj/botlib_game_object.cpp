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
    , flags_(0)
    , row_(0)
    , col_(0)
{
}

void GameObject::init(const GameObjectTemplate* t,
                      const Vector2& pos)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "t is null");
    }

    t_ = t;
    pos_ = pos;
    setAlive(true);
    collideRegion_.init(x()-collideBreath(), x()+collideBreath(),
                        y()-collideBreath(), y()+collideBreath());
}

void GameObject::update(GameMap& map,
                        float timeDelta)
{
    setUpdated(true);
}

void GameObject::setPos(float x,
                        float y)
{
    shiftPos(x - pos_[0], y - pos_[1]);
}

void GameObject::shiftPos(float deltaX,
                          float deltaY)
{
    pos_[0] += deltaX;
    pos_[1] += deltaY;
    collideRegion_.shift(deltaX, deltaY);
}

void GameObject::setMapPos(unsigned int r,
                           unsigned int c)
{
    row_ = r;
    col_ = c;
}

void GameObject::clearFlags()
{
    flags_ = 0;
}

void GameObject::setAlive(bool b)
{
    setFlag(FLAG_ALIVE, b);
}

void GameObject::setInvincible(bool b)
{
    setFlag(FLAG_INVINCIBLE, b);
}

void GameObject::setUpdated(bool b)
{
    setFlag(FLAG_UPDATED, b);
}

void GameObject::setFlag(Flag flag,
                         bool b)
{
    if (b)
    {
        flags_ |= flag;
    }
    else
    {
        flags_ &= ~flag;
    }
}

} // end of namespace botlib
} // end of namespace mcdane

