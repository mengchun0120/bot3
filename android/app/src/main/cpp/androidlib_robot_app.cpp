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

    updateViewport();

    AppConfig::init("config/bot_config.json", assetManager());

    return true;
}

void RobotApp::process()
{
    updateViewport();
}

void RobotApp::updateViewport()
{
    EGLint width;
    eglQuerySurface(display_, surface_, EGL_WIDTH, &width);

    EGLint height;
    eglQuerySurface(display_, surface_, EGL_HEIGHT, &height);

    float width1 = static_cast<float>(width);
    float height1 = static_cast<float>(height);

    if (viewportWidth() != width1 || viewportHeight() != height1)
    {
        viewportSize_.init({width1, height1});
        glViewport(0, 0, width, height);

        LOG_INFO << "Viewport updated " << viewportSize_ << LOG_END;
    }
}

} // end of namespace androidlib
} // end of namespace mcdane