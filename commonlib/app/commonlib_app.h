#ifndef INCLUDED_COMMONLIB_APP_H
#define INCLUDED_COMMONLIB_APP_H

#include <string>
#include <commonlib_vector.h>
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

    virtual void process();

    void postProcess();

#ifdef DESKTOP_APP
    void setupWindow(unsigned int width,
                     unsigned int height,
                     const std::string& title);

    GLFWwindow* window() const
    {
        return window_;
    }

    virtual void run();
#endif

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
    commonlib::Point2 viewportSize_;
    bool running_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

