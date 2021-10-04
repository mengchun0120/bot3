#ifndef INCLUDED_BOTLIB_TILE_TEMPLATE_H
#define INCLUDED_BOTLIB_TILE_TEMPLATE_H

#include <commonlib_texture.h>
#include <botlib_rectangle.h>
#include <botlib_game_object_template.h>

namespace mcdane {
namespace botlib {

class TileTemplate: public GameObjectTemplate {
public:
    TileTemplate(float width,
                 float height,
                 float collideBreath,
                 float hp,
                 const commonlib::Texture* tex,
                 const Rectangle* r,
                 bool invincible=false);

    ~TileTemplate() override = default;

    inline float hp() const;

    inline const commonlib::Texture* texture() const;

    inline const Rectangle* rect() const;

private:
    void init(float hp,
              const commonlib::Texture* tex,
              const Rectangle* r);

protected:
    float hp_;
    const commonlib::Texture* texture_;
    const Rectangle* rect_;
};

float TileTemplate::hp() const
{
    return hp_;
}

const commonlib::Texture* TileTemplate::texture() const
{
    return texture_;
}

const Rectangle* TileTemplate::rect() const
{
    return rect_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

