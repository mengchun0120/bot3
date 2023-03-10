#include <commonlib_log.h>
#include <commonlib_file_utils.h>
#include <commonlib_json_utils.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
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

    AppConfig::init("config/bot_config_android.json");

    const AppConfig& cfg = AppConfig::instance();

    Context::init(cfg);

    return true;
}

void RobotApp::process()
{
    updateViewport();
}

} // end of namespace androidlib
} // end of namespace mcdane
