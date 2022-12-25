#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <botlib_update_context.h>
#include <botlib_game_object_dumper.h>
#include <botlib_game_map.h>
#include <botlib_game_object.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

unsigned int GameObject::k_curId = 0;

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
    id_ = k_curId++;
    setState(GameObjectState::ALIVE);
    collideRegion_.init(x()-collideBreath(), x()+collideBreath(),
                        y()-collideBreath(), y()+collideBreath());
}

void GameObject::update(UpdateContext& cxt)
{
    setUpdated(true);

    if (state_ != GameObjectState::DEAD && canBeDumped(*(cxt.map())))
    {
        cxt.dumper().add(this);
    }
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

void GameObject::setState(GameObjectState newState)
{
    state_ = newState;
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

void GameObject::toJson(rapidjson::Value& v,
                        rapidjson::Document::AllocatorType& allocator)
{
    v.AddMember("template", jsonVal(t_->name(), allocator), allocator);
    v.AddMember("pos", pos_.toJson(allocator), allocator);
}

} // end of namespace botlib
} // end of namespace mcdane

