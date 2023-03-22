#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_game_navigator_config.h>
#include <botlib_game_navigator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameNavigator::init(float x,
                         float y,
                         MoveAction &moveAction,
                         StopAction &stopAction)
{
    const GameNavigatorConfig &cfg = Context::gameNavigatorConfig();
    Widget::init(x, y, true, true, true);
    directionValid_ = false;
    moveAction_ = moveAction;
    stopAction_ = stopAction;
    baseRadiusSquare_ = cfg.baseRadius() * cfg.baseRadius();
    stopRadiusSquare_ = cfg.stopRadius() * cfg.stopRadius();
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
    return x*x + y*y <= baseRadiusSquare_;
}

void GameNavigator::onLostFocus()
{
}

void GameNavigator::onPointerOut()
{
}

void GameNavigator::onPointerOver(float x, float y)
{
}

void GameNavigator::onPointerDown(float x, float y)
{
    if (x*x + y*y > stopRadiusSquare_)
    {
        pressBase(x, y);
    }
    else
    {
        pressStop();
    }
}

void GameNavigator::pressBase(float x, float y)
{
    const GameNavigatorConfig &cfg = Context::gameNavigatorConfig();

    directionValid_ = true;
    curDirection_[0] = x;
    curDirection_[1] = y;
    curDirection_.normalize();

    arrowPos_ = pos_ + curDirection_ * cfg.arrowRadius();

    moveAction_(curDirection_);
}

void GameNavigator::pressStop()
{
    directionValid_ = false;
    stopAction_();
}

} // end of namespace botlib
} // end of namespace mcdane
