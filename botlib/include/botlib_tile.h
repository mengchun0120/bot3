#ifndef INCLUDED_BOTLIB_TILE_H
#define INCLUDED_BOTLIB_TILE_H

#include <botlib_game_object.h>
#include <botlib_tile_template.h>

namespace mcdane {
namespace botlib {

class Tile: public GameObject {
public:
    Tile() = default;

    Tile(const TileTemplate* t,
         float x,
         float y);

    ~Tile() override = default;

    void init(const TileTemplate* t,
              float x,
              float y);

    inline float hp() const;

    inline const TileTemplate* getTemplate() const;

    void present() const override;

    void setPos(float x,
                float y) override;

    void addHP(float delta);

private:
    void updateRefPos();

private:
    float hp_;
    commonlib::Vector2 refPos_;
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

