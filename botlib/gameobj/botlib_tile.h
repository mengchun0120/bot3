#ifndef INCLUDED_BOTLIB_TILE_H
#define INCLUDED_BOTLIB_TILE_H

#include <botlib_hp_indicator.h>
#include <botlib_composite_object.h>
#include <botlib_tile_template.h>

namespace mcdane {
namespace botlib {

class Tile: public CompositeObject {
public:
    Tile() = default;

    ~Tile() override = default;

    void init(const TileTemplate* t,
              const commonlib::Vector2& pos1,
              const commonlib::Vector2& direction1);

    inline float hp() const;

    inline const TileTemplate* getTemplate() const;

    inline float hpRatio() const;

    void present() const override;

    void update(GameMap& map,
                GameObjectDumper& dumper,
                float delta) override;

    void addHP(float delta);

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;

    bool canBeDumped(GameMap& map) const override;

private:
    float hp_;
    HPIndicator hpIndicator_;
};

float Tile::hp() const
{
    return hp_;
}

const TileTemplate* Tile::getTemplate() const
{
    return static_cast<const TileTemplate*>(t_);
}

float Tile::hpRatio() const
{
    return hp_ / getTemplate()->hp();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

