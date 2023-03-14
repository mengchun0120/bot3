#ifndef INCLUDED_COMMONLIB_APP_H
#define INCLUDED_COMMONLIB_APP_H

#include <string>

#ifdef __ANDROID__
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif

#include <commonlib_vector.h>
#include <commonlib_opengl.h>

namespace mcdane {
namespace commonlib {

class App {
public:
    static void initInstance(App *app);

    static void clearInstance();

    inline static App * instance();

    App(const std::string &name1="");

    virtual ~App();

#ifdef DESKTOP_APP
    void init(unsigned int width1,
              unsigned int height1,
              const std::string &title);

    inline GLFWwindow * window();

    void run();

#elif __ANDROID__

    void init(android_app *app);

    void handleCommand(int32_t cmd);

    inline android_app * app();

#endif

    inline const std::string & name() const;

    virtual void process();

    inline int width() const;

    inline int height() const;

    inline float viewportWidth() const;

    inline float viewportHeight() const;

    inline const commonlib::Point2 & viewportSize() const;

    inline bool running() const;

    inline void setRunning(bool running);

    inline bool shouldRun() const;

protected:
#ifdef __ANDROID__
    void initDisplay();

    void initSurface();

    void initContext();

    void chooseConfig();

    virtual void handleGainedFocus();

    virtual void handleLostFocus();

    virtual void handlePause();

    virtual void handleWindowResized();

    virtual void handleConfigChanged();

    virtual void handleLowMemory();
#endif

    void getViewportSize(float &width1, float &height1);

    virtual void onViewportChange(float width1, float height1);

    void setupOpenGL();

    void postProcess();

protected:
    static App *k_instance;

#ifdef DESKTOP_APP
    GLFWwindow *window_;

#elif __ANDROID__
    android_app *app_;
    bool hasFocus_;
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLConfig config_;
#endif

    std::string name_;
    commonlib::Point2 viewportSize_;
    bool running_;
};

App * App::instance()
{
    return k_instance;
}

const std::string & App::name() const
{
    return name_;
}

int App::width() const
{
    return width_;
}

int App::height() const
{
    return height_;
}

float App::viewportWidth() const
{
    return viewportSize_[0];
}

float App::viewportHeight() const
{
    return viewportSize_[1];
}

const commonlib::Point2 & App::viewportSize() const
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

GLFWwindow * App::window()
{
    return window_;
}

bool App::shouldRun() const
{
    return 0 == glfwWindowShouldClose(window_) && running_;
}

#elif __ANDROID__

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
