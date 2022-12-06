#include <commonlib_exception.h>
#include <botlib_start_screen.h>
#include <botlib_game_screen.h>
#include <botlib_screen_manager.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ScreenManager::ScreenManager()
    : prevScreen_(nullptr)
    , curScreen_(nullptr)
    , curScreenType_(ScreenType::NONE)
{
}

ScreenManager::~ScreenManager()
{
    delete prevScreen_;
    delete curScreen_;
}

void ScreenManager::init(ScreenType startScreenType,
                         const commonlib::Vector2& viewportSize,
                         const AppActions& actions)
{
    curScreenType_ = startScreenType;
    viewportSize_ = viewportSize;
    actions_ = actions;
    prevScreen_ = nullptr;
    curScreen_ = createScreen(startScreenType);
}

void ScreenManager::update(float delta)
{
    if (curScreen_)
    {
        curScreen_->update(delta);
    }
}

void ScreenManager::present()
{
    if (curScreen_)
    {
        curScreen_->present();
    }
}

bool ScreenManager::processInput(const commonlib::InputEvent &e)
{
    if (!curScreen_)
    {
        return true;
    }

    return curScreen_->processInput(e);
}

void ScreenManager::switchScreen(ScreenType type)
{
    if (type == ScreenType::NONE)
    {
        THROW_EXCEPT(InvalidArgumentException, "ScreenType is none");
    }

    if (curScreenType_ == type)
    {
        return;
    }

    prevScreen_ = curScreen_;
    curScreen_ = createScreen(type);
    curScreenType_ = type;
}

void ScreenManager::postProcess()
{
    if (prevScreen_)
    {
        delete prevScreen_;
        prevScreen_ = nullptr;
    }
}

Screen* ScreenManager::createScreen(ScreenType screenType)
{
    Screen* screen = nullptr;
    switch(screenType)
    {
        case ScreenType::START:
            screen = new StartScreen(viewportSize_, actions_);
            break;
        case ScreenType::GAME:
            screen = new GameScreen(viewportSize_, actions_);
            break;
        case ScreenType::SHOW_MAP:
            break;
        default:
            THROW_EXCEPT(commonlib::MyException, "Invalid screen type");
            break;
    }

    return screen;

}

} // end of namespace botlib
} // end of namespace mcdane

