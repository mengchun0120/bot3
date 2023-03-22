#include <memory>
#include <algorithm>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_system.h>
#include <commonlib_app.h>

namespace mcdane {
namespace commonlib {

App * App::k_instance = nullptr;

void App::initInstance(App *app)
{
    if (k_instance)
    {
        THROW_EXCEPT(MyException, "Only one instance of App is allowed");
    }

    k_instance = app;
}

void App::clearInstance()
{
    k_instance = nullptr;
}

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
                         const std::string &title)
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

App::App(const std::string &name1)
    : window_(nullptr)
    , name_(name1)
    , viewportSize_{0.0f, 0.0f}
    , running_(false)
{
    initInstance(this);
}

App::~App()
{
    if (!window_)
    {
        glfwTerminate();
    }

    clearInstance();
}


void App::init(unsigned int width1,
               unsigned int height1,
               const std::string &title)
{
    initGLFW();
    setWindowHints();
    window_ = createWindow(width1, height1, title);
    makeContextCurrent(window_);
    setupInputMode(window_);
    initGLEW();

    setupOpenGL();
    initViewportSize();
    running_ = true;
}

void App::run()
{
    while (shouldRun())
    {
        process();
    }
}

void App::getViewportSize(float &width1, float &height1)
{
    int w, h;
    glfwGetFramebufferSize(window_, &w, &h);
    width1 = static_cast<float>(w);
    height1 = static_cast<float>(h);
}

void App::setupOpenGL()
{
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void App::postProcess()
{
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

#elif __ANDROID__

App::App(const std::string &name1)
    : app_(nullptr)
    , hasFocus_(false)
    , display_(EGL_NO_DISPLAY)
    , surface_(EGL_NO_SURFACE)
    , context_(EGL_NO_CONTEXT)
    , name_(name1)
    , viewportSize_{0.0f, 0.0f}
    , running_(false)
{
    initInstance(this);
}

App::~App()
{
    if (display_ != EGL_NO_DISPLAY) {
        eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context_ != EGL_NO_CONTEXT) {
            eglDestroyContext(display_, context_);
            context_ = EGL_NO_CONTEXT;
        }
        if (surface_ != EGL_NO_SURFACE) {
            eglDestroySurface(display_, surface_);
            surface_ = EGL_NO_SURFACE;
        }
        eglTerminate(display_);
        display_ = EGL_NO_DISPLAY;
    }

    clearInstance();
}

void App::init(android_app *app)
{
    app_ = app;

    initDisplay();
    initSurface();
    initContext();

    if (EGL_FALSE == eglMakeCurrent(display_, surface_, surface_, context_)) {
        THROW_EXCEPT(OpenGLException, "eglMakeCurrent failed, err "\
                     + std::to_string(eglGetError()));
    }

    setupOpenGL();
    initViewportSize();
    running_ = true;
}

void App::handleCommand(int32_t cmd)
{
    switch (cmd) {
        case APP_CMD_GAINED_FOCUS:
            handleGainedFocus();
            break;
        case APP_CMD_LOST_FOCUS:
            handleLostFocus();
            break;
        case APP_CMD_PAUSE:
            handlePause();
            break;
        case APP_CMD_WINDOW_RESIZED:
            handleWindowResized();
            break;
        case APP_CMD_CONFIG_CHANGED:
            handleConfigChanged();
            break;
        case APP_CMD_LOW_MEMORY:
            handleLowMemory();
            break;
        default:
            LOG_WARN << "Unknown command " << cmd << LOG_END;
            break;
    }

    LOG_DEBUG << "Status: hasFocus=" << hasFocus_ << " display=" << display_
              << " surface=" << surface_ << " context=" << context_
              << " config=" << config_ << LOG_END;
}

void App::initDisplay()
{
    display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (EGL_FALSE == eglInitialize(display_, nullptr, nullptr)) {
        THROW_EXCEPT(OpenGLException, "Failed to init display, err "\
                     + std::to_string(eglGetError()));
    }

    LOG_INFO << "Display initialized successfully" << LOG_END;
}

void App::initSurface()
{
    chooseConfig();

    surface_ = eglCreateWindowSurface(display_, config_, app_->window, nullptr);
    if (surface_ == EGL_NO_SURFACE)
    {
        THROW_EXCEPT(OpenGLException, "Failed to create EGL surface, err "\
                     + std::to_string(eglGetError()));
    }

    LOG_INFO << "Successfully initialized surface." << LOG_END;
}

void App::initContext()
{
    EGLint attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION,
        3,
        EGL_NONE
    };

    context_ = eglCreateContext(display_, config_, nullptr, attribs);
    if (context_ == EGL_NO_CONTEXT) {
        THROW_EXCEPT(OpenGLException, "Failed to create EGL context, err "\
                     + std::to_string(eglGetError()));
    }

    LOG_INFO << "Initialized context successfully" << LOG_END;
}

void App::chooseConfig()
{
    constexpr EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_NONE
    };

    EGLint numConfigs;
    eglChooseConfig(display_, attribs, nullptr, 0, &numConfigs);

    // get the list of configurations
    std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    eglChooseConfig(display_, attribs, supportedConfigs.get(), numConfigs, &numConfigs);

    EGLConfig *cfg, *last = supportedConfigs.get() + numConfigs;
    for (cfg = supportedConfigs.get(); cfg != last; ++cfg)
    {
        EGLint red, green, blue, depth;
        if (eglGetConfigAttrib(display_, *cfg, EGL_RED_SIZE, &red)
            && eglGetConfigAttrib(display_, *cfg, EGL_GREEN_SIZE, &green)
            && eglGetConfigAttrib(display_, *cfg, EGL_BLUE_SIZE, &blue)
            && eglGetConfigAttrib(display_, *cfg, EGL_DEPTH_SIZE, &depth))
        {
            if (red == 8 && green == 8 && blue == 8 && depth == 24)
            {
                break;
            }
        }
    }

    if (cfg == last)
    {
        THROW_EXCEPT(OpenGLException, "Failed to find config");
    }

    config_ = *cfg;
}

void App::handleGainedFocus()
{
    LOG_DEBUG << "Handling APP_CMD_GAINED_FOCUS" << LOG_END;

    hasFocus_ = true;
}

void App::handleLostFocus()
{
    LOG_DEBUG << "Handling APP_CMD_LOST_FOCUS" << LOG_END;

    hasFocus_ = false;
}

void App::handlePause()
{
    LOG_DEBUG << "Handling APP_CMD_PAUSE" << LOG_END;
}

void App::handleWindowResized()
{
    LOG_DEBUG << "Handling APP_CMD_WINDOW_RESIZED" << LOG_END;
}

void App::handleConfigChanged()
{
    LOG_DEBUG << "Handling APP_CMD_CONFIG_CHANGED" << LOG_END;
}

void App::handleLowMemory()
{
    LOG_DEBUG << "Handling APP_CMD_LOST_FOCUS" << LOG_END;
}

void App::getViewportSize(float &width1, float &height1)
{
    EGLint w, h;

    eglQuerySurface(display_, surface_, EGL_WIDTH, &w);
    eglQuerySurface(display_, surface_, EGL_HEIGHT, &h);
    width1 = static_cast<float>(w);
    height1 = static_cast<float>(h);
}

void App::setupOpenGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void App::postProcess()
{
    EGLBoolean ret = eglSwapBuffers(display_, surface_);
    if (ret != EGL_TRUE)
    {
        THROW_EXCEPT(OpenGLException, "Failed to swap buffer");
    }
}

#endif

void App::process()
{
    float width, height;

    getViewportSize(width, height);
    if (width != viewportWidth() || height != viewportHeight())
    {
        onViewportChange(width, height);
    }
}

void App::initViewportSize()
{
    float width, height;

    getViewportSize(width, height);
    setViewportSize(width, height);
}

void App::setViewportSize(float width, float height)
{
    viewportSize_[0] = width;
    viewportSize_[1] = height;
    glViewport(0, 0, width, height);
}

void App::onViewportChange(float width, float height)
{
    setViewportSize(width, height);
}

} // end of namespace commonlib
} // end of namespace mcdane
