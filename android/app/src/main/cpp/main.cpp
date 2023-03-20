#include <jni.h>
#include <vector>
#include <sstream>
#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_system.h>
#include <commonlib_file_utils.h>
#include <botlib_test_shape_app.h>
#include <botlib_test_map_app.h>
#include <botlib_test_widget_app.h>
#include <botlib_show_map_app.h>
#include <androidlib_android_out.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;
using namespace mcdane::androidlib;

extern "C" {

#include <game-activity/native_app_glue/android_native_app_glue.c>

void getStartApp(std::vector<std::string> &params)
{
    std::istringstream is1(readText("config/startapp.txt"));
    std::string line;
    while (std::getline(is1, line))
    {
        if (!line.empty() && line[0] != '#')
        {
            std::istringstream is2(line);
            readList(params, is2);
        }
    }
}

void handleInitWindow(android_app *app)
{
    std::vector<std::string> params;
    getStartApp(params);

    if (params.empty())
    {
        LOG_ERROR << "No app specified" << LOG_END;
        return;
    }

    LOG_INFO << "Starting: " << params[0] << LOG_END;

    if (params[0] == "testshape")
    {
        TestShapeApp *a = new TestShapeApp();
        a->init(app);
        app->userData = a;
    }
    else if (params[0] == "testmap")
    {
        TestMapApp *a = new TestMapApp();
        a->init(app);
        app->userData = a;
    }
    else if (params[0] == "testwidget")
    {
        TestWidgetApp *a = new TestWidgetApp();
        a->init(app);
        app->userData = a;
    }
    else if (params[0] == "showmap")
    {
        if (params.size() < 2)
        {
            LOG_ERROR << "Invalid params" << LOG_END;
            return;
        }

        ShowMapApp *a = new ShowMapApp();
        a->init(app, params[1]);
        app->userData = a;
    }
    else
    {
        THROW_EXCEPT(ParseException, "Unknown app " + params[0]);
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
