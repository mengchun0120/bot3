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
                      const Vector2& pos1)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "t is null");
    }

    t_ = t;
    pos_ = pos1;
    setAlive(true);
    collideRegion_.init(x()-collideBreath(), x()+collideBreath(),
                        y()-collideBreath(), y()+collideBreath());
}

void GameObject::update(GameMap& map,
                        float timeDelta)
{
    setUpdated(true);
}

void GameObject::setPos(const commonlib::Vector2& pos1)
{
    shiftPos(pos1 - pos_);
}

void GameObject::shiftPos(const commonlib::Vector2& delta)
{
    pos_ += delta;
    collideRegion_.shift(delta[0], delta[1]);
}

void GameObject::setMapPos(unsigned int row1,
                           unsigned int col1)
{
    row_ = row1;
    col_ = col1;
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

