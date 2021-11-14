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
    updateRefPos();
}

void Tile::present() const
{
    const TileTemplate* t = getTemplate();
    SimpleShaderProgram& program = Graphics::simpleShader();

    t->rect()->draw(program, &refPos_, nullptr, nullptr, nullptr,
                    t->texture()->id(), nullptr);
}

void Tile::setPos(float x,
                  float y)
{
    GameObject::setPos(x, y);
    updateRefPos();
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

void Tile::updateRefPos()
{
    const TileTemplate* t = getTemplate();
    refPos_[0] = pos_[0] + t->rect()->width() / 2.0f;
    refPos_[1] = pos_[1] + t->rect()->height() / 2.0f;
}

} // end of namespace botlib
} // end of namespace mcdane

