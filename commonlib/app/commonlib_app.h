#ifndef INCLUDED_COMMONLIB_APP_H
#define INCLUDED_COMMONLIB_APP_H

#include <string>
#include <commonlib_vector.h>
#include <commonlib_opengl.h>

struct android_app;

namespace mcdane {
namespace commonlib {

class App {
public:
    App();

    virtual ~App();

#ifdef DESKTOP_APP
    bool init(unsigned int width,
              unsigned int height,
              const std::string& title);
#endif

#ifdef __ANDROID__
    bool init(android_app *app);
#endif

    virtual void process();

    void postProcess();

    virtual void run();

    float viewportWidth() const
    {
        return viewportSize_[0];
    }

    float viewportHeight() const
    {
        return viewportSize_[1];
    }

    const commonlib::Point2& viewportSize() const
    {
        return viewportSize_;
    }

    inline bool running() const
    {
        return running_;
    }

    void setRunning(bool running)
    {
        running_ = running;
    }

    inline bool shouldRun() const;

private:
#ifdef __ANDROID__
    bool initDisplay();

    bool initSurface();

    bool initContext();

    void killDisplay();

    void killSurface();

    void killContext();

    void handleEglError(EGLint error);
#endif

private:
#ifdef DESKTOP_APP
    GLFWwindow *window_;
#endif

#ifdef __ANDROID__
    android_app *app_;
    bool hasFocus_, visible_, hasWindow_;
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLConfig config_;
#endif

    commonlib::Point2 viewportSize_;
    bool running_;
};

#ifdef DESKTOP_APP
bool App::shouldRun() const
{
    return 0 == glfwWindowShouldClose(window_) && running_;
}
#endif

#ifdef __ANDROID__
bool App::shouldRun() const
{
    return hasFocus_ && visible_ && hasWindow_;
}
#endif

} // end of namespace commonlib
} // end of namespace mcdane

#endif