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
{
}

#ifdef DESKTOP_APP
App::App(unsigned int width,
         unsigned int height,
         const std::string& title)
    : App()
{
    running_ = false;
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
    initGLEW();

    int w, h;
    glfwGetFramebufferSize(window_, &w, &h);
    viewportSize_[0] = static_cast<float>(w);
    viewportSize_[1] = static_cast<float>(h);
}

void App::run()
{
    running_ = true;
    while (0 == glfwWindowShouldClose(window_) && running_)
    {
        preProcess();

        if (running_)
        {
            process();
        }

        if (running_)
        {
            postProcess();
        }
    }
    running_ = false;
}
#endif

void App::postProcess()
{
#ifdef DESKTOP_APP
    glfwSwapBuffers(window_);
    glfwPollEvents();
#endif
}

} // end of namespace commonlib
} // end of namespace mcdane

