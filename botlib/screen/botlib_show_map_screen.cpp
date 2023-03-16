#include <commonlib_exception.h>
#include <botlib_context.h>
#include <botlib_game_map_loader.h>
#include <botlib_show_map_screen.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ShowMapScreen::ShowMapScreen(const commonlib::Vector2 &viewportSize,
                             AppActions actions,
                             ScreenType nextScreenType,
                             bool initMap)
{
    init(viewportSize, actions, nextScreenType);
}

void ShowMapScreen::init(const commonlib::Vector2 &viewportSize,
                         AppActions actions,
                         ScreenType nextScreenType,
                         bool initMap)
{
    constexpr int MISSILE_POOL_SIZE = 1000;

    Screen::init(actions);
    factory_.init(MISSILE_POOL_SIZE);
    nextScreenType_ = nextScreenType;
    if (initMap)
    {
        loadMap(viewportSize);
    }
}

void ShowMapScreen::update(float timeDelta)
{
}

void ShowMapScreen::present()
{
    glClear(GL_COLOR_BUFFER_BIT);
    map_.present();
    glFlush();
}

#ifdef DESKTOP_APP
bool ShowMapScreen::processInput(const commonlib::InputEvent &e)
{
    switch (e.type())
    {
        case EventType::KEY:
            return processKey(e.keyEvent());
        default:
            break;
    }

    return true;
}

bool ShowMapScreen::processKey(const commonlib::KeyEvent &e)
{
    if (e.action_ != GLFW_PRESS && e.action_ != GLFW_REPEAT)
    {
        return true;
    }

    switch(e.key_)
    {
        case GLFW_KEY_ESCAPE:
        {
            return processEscKey();
        }
        case GLFW_KEY_UP:
        {
            return processUpKey();
        }
        case GLFW_KEY_DOWN:
        {
            return processDownKey();
        }
        case GLFW_KEY_RIGHT:
        {
            return processRightKey();
        }
        case GLFW_KEY_LEFT:
        {
            return processLeftKey();
        }
        default:
            break;
    }

    return true;
}

bool ShowMapScreen::processEscKey()
{
    if (nextScreenType_ == ScreenType::NONE)
    {
        if (actions_.exitAction_)
        {
            actions_.exitAction_();
        }
    }
    else
    {
        if (actions_.switchAction_)
        {
            actions_.switchAction_(nextScreenType_);
        }
    }

    return true;
}

bool ShowMapScreen::processUpKey()
{
    const ShowMapScreenConfig &cfg = Context::showMapScreenConfig();
    Vector2 p = map_.viewportOrigin();

    p[1] += cfg.deltaPerStroke();
    map_.setViewportOrigin(p);

    return true;
}

bool ShowMapScreen::processDownKey()
{
    const ShowMapScreenConfig &cfg = Context::showMapScreenConfig();
    Vector2 p = map_.viewportOrigin();

    p[1] -= cfg.deltaPerStroke();
    map_.setViewportOrigin(p);

    return true;
}

bool ShowMapScreen::processRightKey()
{
    const ShowMapScreenConfig &cfg = Context::showMapScreenConfig();
    Vector2 p = map_.viewportOrigin();

    p[0] += cfg.deltaPerStroke();
    map_.setViewportOrigin(p);

    return true;
}

bool ShowMapScreen::processLeftKey()
{
    const ShowMapScreenConfig &cfg = Context::showMapScreenConfig();
    Vector2 p = map_.viewportOrigin();

    p[0] -= cfg.deltaPerStroke();
    map_.setViewportOrigin(p);

    return true;
}
#endif

void ShowMapScreen::loadMap(const commonlib::Vector2 &viewportSize)
{
    const ShowMapScreenConfig &cfg = Context::showMapScreenConfig();

    GameMapLoader loader(viewportSize[0], viewportSize[1], factory_);

    loader.load(map_, cfg.mapFile());
}

void ShowMapScreen::onViewportChange(float width, float height)
{
    map_.resetViewport(width, height);
}

} // end of namespace botlib
} // end of namespace mcdane
