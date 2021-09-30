#include <commonlib_exception.h>
#include <commonlib_math_utils.h>
#include <botlib_graphics.h>
#include <botlib_tile.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Tile::Tile(const TileTemplate* t,
           float x,
           float y)
{
    init(t, x, y);
}

void Tile::init(const TileTemplate* t,
                float x,
                float y)
{
    GameObject::init(t, x, y);
}

void Tile::present()
{
    const TileTemplate* t = getTemplate();
    Graphics& g = Graphics::getInstance();

    t->rect().draw(g.simpleShader(), &pos_, nullptr, nullptr, nullptr,
                    t->texture().id(), nullptr);
}

void Tile::addHP(float delta)
{
    const TileTemplate* t = getTemplate();

    if (t->invincible())
    {
        return;
    }

    hp_ = clamp(hp_+delta, 0.0f, t->hp());
    if (hp_ <= 0.0f)
    {
        alive_ = false;
    }
}

} // end of namespace botlib
} // end of namespace mcdane

