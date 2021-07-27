#ifndef INCLUDED_COMMONLIB_APP_H
#define INCLUDED_COMMONLIB_APP_H

#include <commonlib_opengl.h>

namespace mcdane {
namespace commonlib {

class App {
public:
    App() = default;

    virtual ~App() = default;

#ifdef DESKTOP_APP
    GLFWwindow* window()
    {
        return window_;
    }

    void run();
#endif

    void process();

private:
#ifdef DESKTOP_APP

#endif

private:
#ifdef DESKTOP_APP
    GLFWwindow *window_;
#endif
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

