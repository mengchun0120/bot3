#include <commonlib_exception.h>
#include <commonlib_app.h>

namespace mcdane {
namespace commonlib {

#ifdef DESKTOP_APP

void initGLFW()
{
    if (!glfwInit())
    {
        THROW_EXCEPT(OpenGLException, "glfwInit failed");
    }
}

void setWindowHints()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow *createWindow(unsigned int width,
                         unsigned int height,
                         const std::string& title)
{
    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(),
                                          nullptr, nullptr);
    if (!window)
    {
        THROW_EXCEPT(OpenGLException, "glfwCreateWindow failed");
    }

    return window;
}

void makeContextCurrent(GLFWwindow *window)
{
    glfwMakeContextCurrent(window);
}

void setupInputMode(GLFWwindow *window)
{
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void initGLEW()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        THROW_EXCEPT(OpenGLException, "glewInit failed");
    }
}

inline bool running(GLFWwindow *window)
{
    return 0 == glfwWindowShouldClose(window);
}

#endif

App::App()
    : window_(nullptr)
    , viewportWidth_(0.0f)
    , viewportHeight_(0.0f)
{
}

#ifdef DESKTOP_APP
App::App(unsigned int width,
         unsigned int height,
         const std::string& title)
    : App()
{
    setupWindow(width, height, title);
}
#endif

App::~App()
{
#ifdef DESKTOP_APP
    if (!window_)
    {
        glfwTerminate();
    }
#endif
}

#ifdef DESKTOP_APP
void App::setupWindow(unsigned int width,
                      unsigned int height,
                      const std::string& title)
{
    initGLFW();
    setWindowHints();
    window_ = createWindow(width, height, title);
    makeContextCurrent(window_);
    setupInputMode(window_);

    int w, h;
    glfwGetFramebufferSize(window_, &w, &h);
    viewportWidth_ = static_cast<float>(w);
    viewportHeight_ = static_cast<float>(h);
}

void App::run()
{
    while (running(window_))
    {
        if (!preProcess())
        {
            break;
        }

        if (!process())
        {
            break;
        }

        if (!postProcess())
        {
            break;
        }
    }
}
#endif

bool App::preProcess()
{
    return true;
}

bool App::process()
{
    return true;
}

bool App::postProcess()
{
#ifdef DESKTOP_APP
    glfwSwapBuffers(window_);
    glfwPollEvents();
#endif

    return true;
}

} // end of namespace commonlib
} // end of namespace mcdane

