//
// Created by mengc on 3/6/2023.
//
#ifdef __ANDROID__
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif
#include <commonlib_log.h>
#include <commonlib_file_utils.h>
#include <androidlib_robot_app.h>

using namespace mcdane::commonlib;

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

    std::string str = readTextFromAssets(app_->activity->assetManager, "res/libs/texture_lib.json");
    LOG_INFO << "str_len=" << str.size() << LOG_END;
    LOG_INFO << "str=" << str << LOG_END;

    return true;
}

void RobotApp::process()
{
}

} // end of namespace androidlib
} // end of namespace mcdane