#include <commonlib_exception.h>
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
    prevScreen_ = nullptr;
    curScreen_ = Screen::create(startScreenType, viewportSize, actions);
    curScreenType_ = startScreenType;
    viewportSize_ = viewportSize;
    actions_ = actions;
}

void ScreenManager::update()
{
    if (curScreen_)
    {
        curScreen_->update();
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
    curScreen_ = Screen::create(type, viewportSize_, actions_);
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

} // end of namespace botlib
} // end of namespace mcdane

