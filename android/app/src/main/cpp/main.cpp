#include <jni.h>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>
#include <commonlib_log.h>
#include <androidlib_android_out.h>
#include <botlib_app_launcher.h>

using namespace mcdane::botlib;
using namespace mcdane::commonlib;
using namespace mcdane::androidlib;

extern "C" {

#include <game-activity/native_app_glue/android_native_app_glue.c>

void handleInitWindow(android_app *app)
{
    AppLauncher *launcher = new AppLauncher();
    launcher->init(app, "config/startapp.txt");
    app->userData = launcher;
}

void handleTermWindow(android_app *app)
{
    AppLauncher *a = reinterpret_cast<AppLauncher*>(app->userData);

    LOG_INFO << "Terminating " << LOG_END;

    app->userData = nullptr;
    delete a;
}

void handleDefaultCmd(android_app *app, int32_t cmd)
{
    if (app->userData)
    {
        AppLauncher *launcher = reinterpret_cast<AppLauncher*>(app->userData);
        launcher->handleCmd(cmd);
    }
}

void handle_cmd(android_app *app, int32_t cmd)
{
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
        {
            handleInitWindow(app);
            break;
        }
        case APP_CMD_TERM_WINDOW:
        {
            handleTermWindow(app);
            break;
        }
        default:
        {
            handleDefaultCmd(app, cmd);
            break;
        }
    }
}

void android_main(struct android_app *app)
{
    app->onAppCmd = handle_cmd;

    aout << "Starting Robot" << std::endl;

    int events;
    android_poll_source *pSource;
    while(true) {
        if (ALooper_pollAll(0, nullptr, &events, (void **) &pSource) >= 0) {
            if (pSource) {
                pSource->process(app, pSource);
            }
        }

        if (app->destroyRequested)
        {
            return;
        }

        if (app->userData) {
            AppLauncher *launcher = reinterpret_cast<AppLauncher*>(app->userData);
            launcher->process();
        }
    }
}

}
