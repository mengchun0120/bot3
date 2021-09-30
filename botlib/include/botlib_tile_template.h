#ifndef INCLUDED_BOTLIB_TILE_TEMPLATE_H
#define INCLUDED_BOTLIB_TILE_TEMPLATE_H

#include <string>
#include <commonlib_texture.h>
#include <botlib_game_object_template.h>
#include <botlib_rectangle.h>

namespace mcdane {
namespace botlib {

class TileTemplate: public GameObjectTemplate {
public:
    TileTemplate() = default;

    TileTemplate(const rapidjson::Value& v,
                 const std::string& picDir);

    ~TileTemplate() override = default;

    void init(const rapidjson::Value& v,
              const std::string& picDir);

    inline const Rectangle& rect() const;

    inline const commonlib::Texture& texture() const;

    inline float hp() const;

protected:
    Rectangle rect_;
    commonlib::Texture texture_;
    float hp_;
};

const Rectangle& TileTemplate::rect() const
{
    return rect_;
}

const commonlib::Texture& TileTemplate::texture() const
{
    return texture_;
}

float TileTemplate::hp() const
{
    return hp_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

