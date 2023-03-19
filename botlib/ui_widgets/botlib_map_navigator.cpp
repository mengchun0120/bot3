#include <cmath>
#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_map_navigator.h>

namespace mcdane {
namespace botlib {

MapNavigator::MapNavigator()
    : actions_(4)
{
}

void MapNavigator::init(float x,
                        float y,
                        const std::vector<Action> &actions)
{
    const MapNavigatorConfig &cfg = Context::mapNavigatorConfig();
    Widget::init(x, y, true, true, true);
    actions_ = actions;
    radiusSquare_ = cfg.radius() * cfg.radius();
}

void MapNavigator::present() const
{
    const MapNavigatorConfig &cfg = Context::mapNavigatorConfig();
    SimpleShaderProgram &program = Context::graphics().simpleShader();

    program.setAlpha(cfg.alpha());
    for (int i = 0; i < 4; ++i)
    {
        cfg.control(i).draw(program, &pos_,
                            nullptr, nullptr, nullptr,
                            cfg.texture().id(), nullptr,
                            GL_TRIANGLES, 0, 3);
    }
}

bool MapNavigator::containPos(float x, float y) const
{
    const MapNavigatorConfig &cfg = Context::mapNavigatorConfig();
    float distX = x - pos_[0];
    float distY = y - pos_[1];
    return distX * distX + distY * distY <= radiusSquare_;
}

void MapNavigator::onLostFocus()
{
}

void MapNavigator::onPointerOut()
{
}

void MapNavigator::onPointerOver(float x, float y)
{
}

void MapNavigator::onPointerDown(float x, float y)
{
    actions_[controlIdx(x, y)]();
}

int MapNavigator::controlIdx(float x, float y)
{
    float dx = x - pos_[0];
    float dy = y - pos_[1];

    if (fabs(dx) >= fabs(dy))
    {
        return dx >= 0.0 ? 0 : 2;
    }

    return dy >= 0.0 ? 1 : 3;
}

} // end of namespace botlib
} // end of namespace mcdane
