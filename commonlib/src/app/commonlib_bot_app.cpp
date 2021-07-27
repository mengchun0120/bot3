#include <commonlib_app_config.h>
#include <commonlib_bot_app.h>

namespace mcdane {
namespace commonlib {

BotApp::BotApp()
    : App()
{
    initApp();
}

BotApp::~BotApp()
{
}

void BotApp::initApp()
{
#ifdef DESKTOP_APP
    initWindow();
#endif
    setupOpenGL();
}

#ifdef DESKTOP_APP
void BotApp::initWindow()
{
    const AppConfig& cfg = AppConfig::getInstance();
    setupWindow(cfg.width(), cfg.height(), cfg.title());
}
#endif

void BotApp::setupOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

bool BotApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return true;
}

bool BotApp::process()
{
    return true;
}

bool BotApp::postProcess()
{
    return App::postProcess();
}

} // end of namespace commonlib
} // end of namespace mcdane

