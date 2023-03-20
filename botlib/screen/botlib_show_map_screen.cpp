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

    viewportSize_ = viewportSize;
#ifdef __ANDROID__
    initNavigator();
    overlayViewportOrigin_ = viewportSize / 2.0f;
#endif
}

void ShowMapScreen::update(float timeDelta)
{
}

void ShowMapScreen::present()
{
    glClear(GL_COLOR_BUFFER_BIT);
    map_.present();
#ifdef __ANDROID__
    presentOverlay();
#endif
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
    switch(e.type_)
    {
        case InputEvent::POINTER_DOWN:
            handlePointerDown(e.x_, e.y_);
            break;
        case InputEvent::POINTER_MOVE:
            handlePointerMove(e.x_, e.y_);
            break;
        default:
            break;
    }
    return true;
}

void ShowMapScreen::initNavigator()
{
    const ShowMapScreenConfig &cfg = Context::showMapScreenConfig();
    std::vector<MapNavigator::Action> actions{
        [&](){ move(1, 0); },
        [&](){ move(0, 1); },
        [&](){ move(-1, 0); },
        [&](){ move(0, -1); },
    };

    navigator_.init(cfg.navigatorPos()[0], cfg.navigatorPos()[1], actions);
}

void ShowMapScreen::handlePointerDown(float x, float y)
{
    if (navigator_.containPos(x, y))
    {
        navigator_.onPointerDown(x, y);
    }
    else
    {
        navigator_.onPointerOut();
    }
}

void ShowMapScreen::handlePointerMove(float x, float y)
{
    if (!navigator_.containPos(x, y))
    {
        navigator_.onPointerOver(x, y);
    }
    else
    {
        navigator_.onPointerOut();
    }

}

void ShowMapScreen::presentOverlay()
{
    SimpleShaderProgram &program = Context::graphics().simpleShader();

    program.use();
    program.setViewportOrigin(overlayViewportOrigin_);
    program.setViewportSize(viewportSize_);
    navigator_.present();
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
    viewportSize_[0] = width;
    viewportSize_[1] = height;
    map_.resetViewport(width, height);
#ifdef __ANDROID__
    overlayViewportOrigin_ = viewportSize_ / 2.0f;
#endif
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
