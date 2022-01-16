#ifndef INCLUDED_BOTLIB_TILE_TEMPLATE_H
#define INCLUDED_BOTLIB_TILE_TEMPLATE_H

#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class TileTemplate: public CompositeObjectTemplate {
public:
    TileTemplate() = default;

    TileTemplate(float collideBreath,
                 float hp,
                 bool invincible,
                 std::vector<Component>&& components);

    ~TileTemplate() override = default;

    void init(float collideBreath,
              float hp,
              bool invincible,
              std::vector<Component>&& components);

    inline float hp() const;

    std::string toString() const override;

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

