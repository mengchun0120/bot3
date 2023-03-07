#include <jni.h>

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>
#include <commonlib_log.h>
#include <androidlib_android_out.h>
#include <androidlib_robot_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::androidlib;

extern "C" {

#include <game-activity/native_app_glue/android_native_app_glue.c>

void handle_cmd(android_app *pApp, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
        {
            RobotApp* app = new RobotApp();
            pApp->userData = app;
            app->init(pApp);
            break;
        }
        case APP_CMD_TERM_WINDOW:
        {
            RobotApp* app = reinterpret_cast<RobotApp*>(pApp->userData);
            pApp->userData = nullptr;
            delete app;
            break;
        }
        default:
        {
            RobotApp* app = reinterpret_cast<RobotApp*>(pApp->userData);
            app->handleCommand(cmd);
            break;
        }
    }
}

void android_main(struct android_app *pApp)
{
    Logger::initInstance(mcdane::androidlib::aout);

    LOG_DEBUG << "Welcome to Robot" << LOG_END;

    pApp->onAppCmd = handle_cmd;

    int events;
    android_poll_source *pSource;
    while(true) {
        if (ALooper_pollAll(0, nullptr, &events, (void **) &pSource) >= 0) {
            if (pSource) {
                pSource->process(pApp, pSource);
            }
        }

        if (pApp->destroyRequested)
        {
            return;
        }

        if (pApp->userData) {
            RobotApp *app = reinterpret_cast<RobotApp*>(pApp->userData);
            if (app->shouldRun()) {
                app->process();
            }
        }
    }
}

}