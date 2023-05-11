#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_game_navigator_config.h>
#include <botlib_game_navigator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameNavigator::init(float x,
                         float y,
                         SteerFunc steerFunc)
{
    const GameNavigatorConfig &cfg = Context::gameNavigatorConfig();
    Widget::init(x, y, true, true);
    directionValid_ = false;
    steerFunc_ = steerFunc;
    radiusSquare_ = cfg.radius() * cfg.radius();
}

void GameNavigator::disableDirection()
{
    directionValid_ = false;
}

void GameNavigator::setDirection(const commonlib::Vector2 &direction)
{
    directionValid_ = true;
    curDirection_ = direction;
    resetArrowPos();
}

void GameNavigator::present() const
{
    if (!visible_)
    {
        return;
    }

    const GameNavigatorConfig &cfg = Context::gameNavigatorConfig();
    SimpleShaderProgram &program = Context::graphics().simpleShader();

    program.setAlpha(cfg.alpha());

    cfg.baseRect().draw(program, &pos_, nullptr, nullptr, nullptr,
                        cfg.baseTexture().id(), nullptr);

    if (directionValid_)
    {
        cfg.arrowRect().draw(program, &arrowPos_, &curDirection_,
                             nullptr, nullptr,
                             cfg.arrowTexture().id(), nullptr);
    }
}

bool GameNavigator::containPos(float x, float y) const
{
    float dx = x - pos_[0];
    float dy = y - pos_[1];
    return dx*dx + dy*dy <= radiusSquare_;
}

void GameNavigator::onPointerOver(float x, float y)
{
    onPointer(x, y);
}

void GameNavigator::onPointerDown(float x, float y)
{
    onPointer(x, y);
}

void GameNavigator::onPointerUp(float x, float y)
{
    disableDirection();
}

void GameNavigator::onPointer(float x, float y)
{
    float dx = x - pos_[0];
    float dy = y - pos_[1];

    directionValid_ = true;
    curDirection_[0] = dx;
    curDirection_[1] = dy;
    curDirection_.normalize();

    resetArrowPos();
    steerFunc_(curDirection_);
}

void GameNavigator::resetArrowPos()
{
    const GameNavigatorConfig &cfg = Context::gameNavigatorConfig();
    arrowPos_ = pos_ + curDirection_ * cfg.arrowRadius();
}

} // end of namespace botlib
} // end of namespace mcdane
