#include <jni.h>

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>
#include <commonlib_log.h>
#include <commonlib_system.h>
#include <androidlib_android_out.h>
#include <androidlib_robot_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::androidlib;

extern "C" {

#include <game-activity/native_app_glue/android_native_app_glue.c>

void handle_cmd(android_app *app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
        {
            LOG_INFO << "Init-window" << LOG_END;
            RobotApp *robotApp = new RobotApp();
            app->userData = robotApp;
            robotApp->init(app);
            break;
        }
        case APP_CMD_TERM_WINDOW:
        {
            RobotApp *robotApp = reinterpret_cast<RobotApp*>(app->userData);
            app->userData = nullptr;
            delete robotApp;
            break;
        }
        default:
        {
            if (app->userData)
            {
                RobotApp *robotApp = reinterpret_cast<RobotApp*>(app->userData);
                robotApp->handleCommand(cmd);
            }
            break;
        }
    }
}

void android_main(struct android_app *app)
{
    setAssetManager(app->activity->assetManager);
    Logger::initInstance(mcdane::androidlib::aout);

    LOG_DEBUG << "Welcome to Robot" << LOG_END;

    app->onAppCmd = handle_cmd;

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
            RobotApp *robotApp = reinterpret_cast<RobotApp*>(app->userData);
            if (robotApp->shouldRun()) {
                robotApp->process();
            }
        }
    }
}

}