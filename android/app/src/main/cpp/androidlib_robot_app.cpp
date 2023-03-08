//
// Created by mengc on 3/6/2023.
//
#ifdef __ANDROID__
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif
#include <commonlib_log.h>
#include <commonlib_file_utils.h>
#include <commonlib_json_utils.h>
#include <botlib_app_config.h>
#include <androidlib_robot_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace androidlib {

RobotApp::RobotApp()
    : App()
{
}

RobotApp::~RobotApp()
{
}

bool RobotApp::init(android_app* app)
{
    if (!App::init(app))
    {
        LOG_ERROR << "Failed to initialize RobotApp" << LOG_END;
        return false;
    }

    AppConfig::init("config/bot_config.json", assetManager());

    const AppConfig &cfg = AppConfig::instance();

    LOG_INFO << cfg.aiRobotTemplateLibFile() << LOG_END;

    return true;
}

void RobotApp::process()
{
}

} // end of namespace androidlib
} // end of namespace mcdane