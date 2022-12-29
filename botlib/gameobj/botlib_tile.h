#ifndef INCLUDED_BOTLIB_TILE_H
#define INCLUDED_BOTLIB_TILE_H

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

    void update(UpdateContext& cxt) override;

    void doDamage(float damage);

    bool canBeDumped(GameMap& map) const override;

    void toJson(rapidjson::Value& v,
                rapidjson::Document::AllocatorType& allocator) override;

private:
    float hp_;
    float dyingTime_;
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

