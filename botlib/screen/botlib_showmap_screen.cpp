#include <commonlib_exception.h>
#include <botlib_game_map_loader.h>
#include <botlib_showmap_screen.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ShowMapScreen::ShowMapScreen(const commonlib::Vector2& viewportSize,
                             const AppActions actions,
                             const std::string& mapFile)
{
    init(viewportSize, actions, mapFile);
}

void ShowMapScreen::init(const commonlib::Vector2& viewportSize,
                         const AppActions actions,
                         const std::string& mapFile)
{
    Screen::init(actions);
    loadMap(viewportSize, mapFile);
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

bool ShowMapScreen::processInput(const commonlib::InputEvent& e)
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

void ShowMapScreen::loadMap(const commonlib::Vector2& viewportSize,
                            const std::string& mapFile)
{
    GameMapLoader loader(viewportSize[0], viewportSize[1]);

    loader.load(map_, mapFile);
}

bool ShowMapScreen::processKey(const commonlib::KeyEvent& e)
{
    if (e.action_ != GLFW_PRESS && e.action_ != GLFW_REPEAT)
    {
        return true;
    }

    switch(e.key_)
    {
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

bool ShowMapScreen::processUpKey()
{
    Vector2 p = map_.viewportOrigin();
    p[1] += k_deltaPerStroke;
    map_.setViewportOrigin(p);
    return true;
}

bool ShowMapScreen::processDownKey()
{
    Vector2 p = map_.viewportOrigin();
    p[1] -= k_deltaPerStroke;
    map_.setViewportOrigin(p);
    return true;
}

bool ShowMapScreen::processRightKey()
{
    Vector2 p = map_.viewportOrigin();
    p[0] += k_deltaPerStroke;
    map_.setViewportOrigin(p);
    return true;
}

bool ShowMapScreen::processLeftKey()
{
    Vector2 p = map_.viewportOrigin();
    p[0] -= k_deltaPerStroke;
    map_.setViewportOrigin(p);
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
