#include <jni.h>

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_system.h>
#include <commonlib_file_utils.h>
#include <botlib_testshape_app.h>
#include <botlib_testmap_app.h>
#include <botlib_testwidget_app.h>
#include <androidlib_android_out.h>
#include <androidlib_robot_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;
using namespace mcdane::androidlib;

extern "C" {

#include <game-activity/native_app_glue/android_native_app_glue.c>

std::string getStartApp()
{
    std::vector<std::string> appList;

    readList(appList, "config/startapp.txt");
    for (auto it = appList.begin(); it != appList.end(); ++it)
    {
        if (!it->empty() && (*it)[0] != '#')
        {
            return *it;
        }
    }

    return "";
}

void handleInitWindow(android_app *app)
{
    std::string appName = getStartApp();

    LOG_INFO << "Starting: " << appName << LOG_END;

    if (appName == "testshape")
    {
        TestShapeApp *a = new TestShapeApp();
        a->init(app);
        app->userData = a;
    }
    else if (appName == "testmap")
    {
        TestMapApp *a = new TestMapApp();
        a->init(app);
        app->userData = a;
    }
    else if (appName == "testwidget")
    {
        TestWidgetApp *a = new TestWidgetApp();
        a->init(app);
        app->userData = a;
    }
    else
    {
        THROW_EXCEPT(ParseException, "Unknown app " + appName);
    }
}

void handleTermWindow(android_app *app)
{
    App *a = reinterpret_cast<App*>(app->userData);

    LOG_INFO << "Terminating " << a->name() << LOG_END;

    app->userData = nullptr;
    delete a;
}

void handleDefaultCmd(android_app *app, int32_t cmd)
{
    if (app->userData)
    {
        App *a = reinterpret_cast<App*>(app->userData);
        a->handleCommand(cmd);
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
            App *a = reinterpret_cast<App*>(app->userData);
            if (a->shouldRun()) {
                a->process();
            }
        }
    }
}

}
