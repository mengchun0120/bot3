#ifndef INCLUDED_BOTLIB_TILE_H
#define INCLUDED_BOTLIB_TILE_H

#include <botlib_game_object.h>

namespace mcdane {
namespace botlib {

class Tile: public GameObject {
public:
    Tile();

    ~Tile() override = default;

    void update() override;

    void present() override;

private:

};

} // end of namespace botlib
} // end of namespace mcdane

#endif

