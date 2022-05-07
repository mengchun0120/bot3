#include <sstream>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_math_utils.h>
#include <botlib_graphics.h>
#include <botlib_game_map.h>
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
}

void Tile::present() const
{
    CompositeObject::present();
    hpIndicator_.present();
}

void Tile::update(GameMap& map,
                  GameObjectDumper& dumper,
                  float delta)
{
    if (state_ == GameObjectState::DYING)
    {
        //TODO
    }

    GameObject::update(map, dumper, delta);
}

void Tile::addHP(float delta)
{
    const TileTemplate* t = getTemplate();

    if (invincible())
    {
        return;
    }

    hp_ = clamp(hp_+delta, 0.0f, t->hp());
    if (hp_ <= 0.0f)
    {
        setState(GameObjectState::DEAD);
    }

    hpIndicator_.reset(pos(), hpRatio());
}

rapidjson::Value Tile::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "Tile", allocator);
    v.AddMember("hp", hp_, allocator);
    v.AddMember("base", CompositeObject::toJson(allocator), allocator);

    return v;
}

bool Tile::canBeDumped(GameMap& map) const
{
    return state_ != GameObjectState::DUMPED &&
           (state_ == GameObjectState::DEAD ||
            (state_ == GameObjectState::DYING && !map.canSee(this)));
}

} // end of namespace botlib
} // end of namespace mcdane

