#include <cmath>
#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_map_navigator.h>

namespace mcdane {
namespace botlib {

MapNavigator::MapNavigator()
    : actions_(4)
    , curControlIdx_(-1)
{
}

void MapNavigator::init(float x,
                        float y,
                        const std::vector<Action> &actions)
{
    Widget::init(x, y, true, true, true);
    actions_ = actions;
}

void MapNavigator::present() const
{
    const MapNavigatorConfig &cfg = Context::mapNavigatorConfig();
    SimpleShaderProgram &program = Context::graphics().simpleShader();

    for (int i = 0; i < 4; ++i)
    {
        cfg.control(i).draw(program, &pos_, nullptr, nullptr, nullptr,
                            cfg.texture().id(),
                            i == curControlIdx_ ? &cfg.activateColor() : nullptr,
                            GL_TRIANGLES, 0, 3);
    }
}

bool MapNavigator::containPos(float x, float y) const
{
    const MapNavigatorConfig &cfg = Context::mapNavigatorConfig();
    float distX = x - pos_[0];
    float distY = y - pos_[1];
    return distX * distX + distY * distY <= cfg.radius();
}

void MapNavigator::onLostFocus()
{
    curControlIdx_ = -1;
}

void MapNavigator::onPointerOut()
{
    curControlIdx_ = -1;
}

void MapNavigator::onPointerOver(float x, float y)
{
}

void MapNavigator::onPointerDown(float x, float y)
{
    curControlIdx_ = controlIdx(x, y);
    actions_[curControlIdx_]();
}

int MapNavigator::controlIdx(float x, float y)
{
    if (fabs(x) >= fabs(y))
    {
        return x >= 0.0 ? 0 : 2;
    }

    return y >= 0.0 ? 1 : 3;
}

} // end of namespace botlib
} // end of namespace mcdane
