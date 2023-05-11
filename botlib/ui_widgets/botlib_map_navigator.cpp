#include <cmath>
#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_map_navigator.h>

namespace mcdane {
namespace botlib {

MapNavigator::MapNavigator()
    : actions_(4)
    , radiusSquare_(0.0f)
    , curControlIdx_(-1)
    , timeSinceLastPress_(0.0f)
{
}

void MapNavigator::init(float x,
                        float y,
                        const std::vector<Action> &actions)
{
    const MapNavigatorConfig &cfg = Context::mapNavigatorConfig();
    Widget::init(x, y, true, true);
    actions_ = actions;
    radiusSquare_ = cfg.radius() * cfg.radius();
    curControlIdx_ = -1;
    timeSinceLastPress_ = 0.0f;
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
                            cfg.texture().id(),
                            i == curControlIdx_ ? &cfg.activateColor() : nullptr,
                            GL_TRIANGLES, 0, 3);
    }
}

void MapNavigator::update(float timeDelta)
{
    if (curControlIdx_ == -1)
    {
        return;
    }

    const MapNavigatorConfig &cfg = Context::mapNavigatorConfig();
    timeSinceLastPress_ += timeDelta;
    if (timeSinceLastPress_ >= cfg.activateDuration())
    {
        curControlIdx_ = -1;
    }
}

bool MapNavigator::containPos(float x, float y) const
{
    float distX = x - pos_[0];
    float distY = y - pos_[1];
    return distX * distX + distY * distY <= radiusSquare_;
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
    timeSinceLastPress_ = 0.0f;

    actions_[curControlIdx_]();
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
