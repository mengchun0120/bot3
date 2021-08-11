#ifndef INCLUDED_COMMONLIB_APP_H
#define INCLUDED_COMMONLIB_APP_H

#include <string>
#include <commonlib_opengl.h>

namespace mcdane {
namespace commonlib {

class App {
public:
    App();

#ifdef DESKTOP_APP
    App(unsigned int width,
        unsigned int height,
        const std::string& title);
#endif

    virtual ~App();

    virtual void preProcess() = 0;

    virtual void process() = 0;

    virtual void postProcess();

#ifdef DESKTOP_APP
    void setupWindow(unsigned int width,
                     unsigned int height,
                     const std::string& title);

    GLFWwindow* window() const
    {
        return window_;
    }

    void run();
#endif

    float viewportWidth() const
    {
        return viewportWidth_;
    }

    float viewportHeight() const
    {
        return viewportHeight_;
    }

    bool running() const
    {
        return running_;
    }

    void setRunning(bool running)
    {
        running_ = running;
    }

private:
#ifdef DESKTOP_APP
    GLFWwindow *window_;
#endif
    float viewportWidth_;
    float viewportHeight_;
    bool running_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

