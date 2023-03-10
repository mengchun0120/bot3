#ifndef INCLUDED_COMMONLIB_APP_H
#define INCLUDED_COMMONLIB_APP_H

#include <string>
#include <commonlib_vector.h>
#include <commonlib_opengl.h>
#ifdef __ANDROID__
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif

namespace mcdane {
namespace commonlib {

class App {
public:
    inline static App *instance();

    App();

    virtual ~App();

#ifdef DESKTOP_APP
    void init(unsigned int width,
              unsigned int height,
              const std::string& title);

    inline GLFWwindow* window();

    void run();
#endif

#ifdef __ANDROID__
    bool init(android_app *app);

    void handleCommand(int32_t cmd);

    inline android_app * app();

    void updateViewport();
#endif

    virtual void process();

    inline float viewportWidth() const;

    inline float viewportHeight() const;

    inline const commonlib::Point2& viewportSize() const;

    inline bool running() const;

    inline void setRunning(bool running);

    inline bool shouldRun() const;

protected:
#ifdef __ANDROID__
    bool initDisplay();

    bool initSurface();

    bool initContext();

    bool chooseConfig();

    virtual void handleGainedFocus();

    virtual void handleLostFocus();

    virtual void handlePause();

    virtual void handleWindowResized();

    virtual void handleConfigChanged();

    virtual void handleLowMemory();
#endif

    void setupOpenGL();

protected:
    static App *k_instance;

#ifdef DESKTOP_APP
    GLFWwindow *window_;
#endif

#ifdef __ANDROID__
    android_app *app_;
    bool hasFocus_;
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLConfig config_;
#endif

    commonlib::Point2 viewportSize_;
    bool running_;
};

App * App::instance()
{
    return k_instance;
}

float App::viewportWidth() const
{
    return viewportSize_[0];
}

float App::viewportHeight() const
{
    return viewportSize_[1];
}

const commonlib::Point2& App::viewportSize() const
{
    return viewportSize_;
}

bool App::running() const
{
    return running_;
}

void App::setRunning(bool running)
{
    running_ = running;
}

#ifdef DESKTOP_APP
GLFWwindow* App::window()
{
    return window_;
}

bool App::shouldRun() const
{
    return 0 == glfwWindowShouldClose(window_) && running_;
}
#endif

#ifdef __ANDROID__
android_app * App::app()
{
    return app_;
}

bool App::shouldRun() const
{
    return hasFocus_ && running_;
}
#endif

} // end of namespace commonlib
} // end of namespace mcdane

#endif
