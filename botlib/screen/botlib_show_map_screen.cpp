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
    if (e.type() == EventType::KEY)
    {
        processKey(e.keyEvent());
    }

    return true;
}

void ShowMapScreen::processKey(const commonlib::KeyEvent &e)
{
    if (e.action_ != GLFW_PRESS && e.action_ != GLFW_REPEAT)
    {
        return;
    }

    switch(e.key_)
    {
        case GLFW_KEY_ESCAPE:
        {
            backout();
            break;
        }
        case GLFW_KEY_UP:
        {
            move(0, 1);
            break;
        }
        case GLFW_KEY_DOWN:
        {
            move(0, -1);
            break;
        }
        case GLFW_KEY_RIGHT:
        {
            move(1, 0);
            break;
        }
        case GLFW_KEY_LEFT:
        {
            move(-1, 0);
            break;
        }
        default:
            break;
    }
}

#elif __ANDROID__
bool ShowMapScreen::processInput(const commonlib::InputEvent &e)
{
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

void ShowMapScreen::move(int horizontalDirection, int verticalDirection)
{
    const ShowMapScreenConfig &cfg = Context::showMapScreenConfig();
    Vector2 p = map_.viewportOrigin();

    if (horizontalDirection != 0)
    {
        p[0] += horizontalDirection * cfg.deltaPerStroke();
    }

    if (verticalDirection != 0)
    {
        p[1] += verticalDirection * cfg.deltaPerStroke();
    }

    map_.setViewportOrigin(p);
}

void ShowMapScreen::backout()
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
}

} // end of namespace botlib
} // end of namespace mcdane
