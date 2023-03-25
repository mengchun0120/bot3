#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_game_navigator_config.h>
#include <botlib_game_navigator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameNavigator::init(float x,
                         float y,
                         SteerFunc steerFunc,
                         ToggleFunc toggleFunc)
{
    const GameNavigatorConfig &cfg = Context::gameNavigatorConfig();
    Widget::init(x, y, true, true, true);
    directionValid_ = false;
    steerFunc_ = steerFunc;
    toggleFunc_ = toggleFunc;
    baseRadiusSquare_ = cfg.baseRadius() * cfg.baseRadius();
    toggleRadiusSquare_ = cfg.toggleRadius() * cfg.toggleRadius();
}

void GameNavigator::present() const
{
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
    return dx*dx + dy*dy <= baseRadiusSquare_;
}

void GameNavigator::onLostFocus()
{
}

void GameNavigator::onPointerOut()
{
}

void GameNavigator::onPointerOver(float x, float y)
{
    float dx = x - pos_[0];
    float dy = y - pos_[1];

    if (dx*dx + dy*dy > toggleRadiusSquare_)
    {
        pressBase(dx, dy);
    }
}

void GameNavigator::onPointerDown(float x, float y)
{
    float dx = x - pos_[0];
    float dy = y - pos_[1];

    if (dx*dx + dy*dy > toggleRadiusSquare_)
    {
        pressBase(dx, dy);
    }
    else
    {
        pressToggle();
    }
}

void GameNavigator::pressBase(float dx, float dy)
{
    const GameNavigatorConfig &cfg = Context::gameNavigatorConfig();

    directionValid_ = true;
    curDirection_[0] = dx;
    curDirection_[1] = dy;
    curDirection_.normalize();

    arrowPos_ = pos_ + curDirection_ * cfg.arrowRadius();

    steerFunc_(curDirection_);
}

void GameNavigator::pressToggle()
{
    toggleFunc_();
}

} // end of namespace botlib
} // end of namespace mcdane
