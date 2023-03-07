//
// Created by mengc on 3/6/2023.
//

#include <commonlib_log.h>
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

    return true;
}

void RobotApp::process()
{
    LOG_INFO << "process" << LOG_END;
}

} // end of namespace androidlib
} // end of namespace mcdane