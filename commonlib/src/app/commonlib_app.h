#ifndef INCLUDED_COMMONLIB_APP_H
#define INCLUDED_COMMONLIB_APP_H

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

    virtual bool preProcess();

    virtual bool process();

    virtual bool postProcess();

#ifdef DESKTOP_APP
    void setupWindow(unsigned int width,
                     unsigned int height,
                     const std::string& title);

    GLFWwindow* window()
    {
        return window_;
    }

    void run();
#endif

private:
#ifdef DESKTOP_APP
    GLFWwindow *window_;
#endif
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

