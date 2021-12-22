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
              const commonlib::Vector2& pos,
              const commonlib::Vector2& direction);

    inline float hp() const;

    inline const TileTemplate* getTemplate() const;

    void addHP(float delta);

private:
    float hp_;
};

float Tile::hp() const
{
    return hp_;
}

const TileTemplate* Tile::getTemplate() const
{
    return static_cast<const TileTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

