#include <botlib_screen_manager.h>

namespace mcdane {
namespace botlib {

ScreenManager::ScreenManager()
    : prevScreen_(nullptr)
    , curScreen_(nullptr)
    , curScreenType_(Screen::SCREEN_NONE)
{
}

ScreenManager::~ScreenManager()
{
    delete prevScreen_;
    delete curScreen_;
}

void ScreenManager::init(Screen::Type startScreenType)
{
    prevScreen_ = nullptr;
    curScreen_ = Screen::create(startScreenType);
    curScreenType_ = startScreenType;
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

void ScreenManager::switchScreen(Screen::Type type)
{
    if (curScreenType_ == type)
    {
        return;
    }

    prevScreen_ = curScreen_;
    curScreen_ = Screen::create(type);
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

