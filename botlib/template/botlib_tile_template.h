#ifndef INCLUDED_BOTLIB_TILE_TEMPLATE_H
#define INCLUDED_BOTLIB_TILE_TEMPLATE_H

#include <commonlib_texture.h>
#include <botlib_rectangle.h>
#include <botlib_composite_object.h>

namespace mcdane {
namespace botlib {

class TileTemplate: public CompositeObjectTemplate {
public:
    TileTemplate(float collideBreath,
                 float hp,
                 bool invincible,
                 std::vector<Component>&& components);

    ~TileTemplate() override = default;

    inline float hp() const;

protected:
    float hp_;
};

float TileTemplate::hp() const
{
    return hp_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

