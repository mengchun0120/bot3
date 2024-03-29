#include <sstream>
#include <cmath>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_math_utils.h>
#include <botlib_context.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>
#include <botlib_tile.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Tile::Tile(const TileTemplate *t,
           const commonlib::Vector2 &pos1,
           const commonlib::Vector2 &direction1)
{
    init(t, pos1, direction1);
}

void Tile::init(const TileTemplate *t,
                const commonlib::Vector2 &pos1,
                const commonlib::Vector2 &direction1)
{
    CompositeObject::init(t, pos1, direction1);
    setInvincible(t->invincible());
    hp_ = t->hp();
    dyingTime_ = 0.0f;
}

void Tile::present() const
{
    CompositeObject::present();
}

void Tile::update(UpdateContext &cxt)
{
    if (state_ == GameObjectState::DYING)
    {
        dyingTime_ += cxt.timeDelta();
        if (dyingTime_ >= getTemplate()->dyingDuration())
        {
            cxt.dumper().add(this);
        }
        else
        {
            setAlpha(1.0f - dyingTime_ / getTemplate()->dyingDuration());
        }
    }

    GameObject::update(cxt);
}

void Tile::doDamage(float damage)
{
    if (state() != GameObjectState::ALIVE || invincible() || damage <= 0.0f)
    {
        return;
    }

    const TileTemplate *t = getTemplate();

    hp_ = clamp(hp_-damage, 0.0f, t->hp());
    if (hp_ <= 0.0f)
    {
        setState(GameObjectState::DYING);
    }
}

bool Tile::canBeDumped(GameMap &map) const
{
    return state_ == GameObjectState::DYING && !map.canSee(this);
}

void Tile::toJson(rapidjson::Value &v,
                  rapidjson::Document::AllocatorType &allocator)
{
    CompositeObject::toJson(v, allocator);
    v.AddMember("type", jsonVal("tile", allocator), allocator);
}

bool Tile::touched(const Vector2 &p) const
{
    float span = getTemplate()->touchSpan();
    return fabs(p[0] - pos_[0]) <= span &&
           fabs(p[1] - pos_[1]) <= span;
}

} // end of namespace botlib
} // end of namespace mcdane

