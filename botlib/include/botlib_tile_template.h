#ifndef INCLUDED_BOTLIB_TILE_TEMPLATE_H
#define INCLUDED_BOTLIB_TILE_TEMPLATE_H

#include <commonlib_color.h>
#include <botlib_game_object_template.h>
#include <botlib_rectangle.h>

namespace mcdane {
namespace botlib {

class TileTemplate: public GameObjectTemplate {
public:
    TileTemplate(const rapdidjson::Value& v);

    ~TileTemplate() override = default;

    inline const Rectangle& rect() const;

    inline const commonlib::Color& color() const;

    inline float hp() const;

private:
    void init(const rapdidjson::Value& v);

protected:
    Rectangle rect_;
    commonlib::Color color_;
    float hp_;
};

const Rectangle& TileTemplate::rect() const
{
    return rect_;
}

const commonlib::Color& TileTemplate::color() const
{
    return color_;
}

float TileTemplate::hp() const
{
    return hp_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

