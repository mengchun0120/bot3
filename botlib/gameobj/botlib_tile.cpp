#include <sstream>
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

void Tile::init(const TileTemplate* t,
                const commonlib::Vector2& pos1,
                const commonlib::Vector2& direction1)
{
    CompositeObject::init(t, pos1, direction1);
    setInvincible(t->invincible());
    hp_ = t->hp();
    hpIndicator_.reset(pos(), hpRatio());
    dyingTime_ = 0.0f;
}

void Tile::present() const
{
    CompositeObject::present();

    if (Context::gameConfig().showHPIndicator())
    {
        hpIndicator_.present();
    }
}

void Tile::update(UpdateContext& cxt)
{
    if (state_ == GameObjectState::DYING)
    {
        dyingTime_ += cxt.timeDelta();
        if (dyingTime_ >= getTemplate()->dyingDuration())
        {
            cxt.dumper()->add(this);
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

    const TileTemplate* t = getTemplate();

    hp_ = clamp(hp_-damage, 0.0f, t->hp());
    if (hp_ <= 0.0f)
    {
        setState(GameObjectState::DYING);
    }

    hpIndicator_.reset(pos(), hpRatio());
}

bool Tile::canBeDumped(GameMap& map) const
{
    return state_ == GameObjectState::DYING && !map.canSee(this);
}

void Tile::toJson(rapidjson::Value& v,
                  rapidjson::Document::AllocatorType& allocator)
{
    CompositeObject::toJson(v, allocator);
    v.AddMember("type", jsonVal("tile", allocator), allocator);
}

} // end of namespace botlib
} // end of namespace mcdane

