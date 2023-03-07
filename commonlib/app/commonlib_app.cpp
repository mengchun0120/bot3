#ifdef __ANDROID__
#include <memory>
#include <algorithm>
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif
#include <commonlib_log.h>
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

App::App()
    : window_(nullptr)
    , running_(false)
{
}

App::~App()
{
    if (!window_)
    {
        glfwTerminate();
    }
}


void App::init(unsigned int width,
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

    setupOpenGL();
}

void App::run()
{
    running_ = true;
    while (shouldRun())
    {
        process();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void App::setupOpenGL()
{
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

#endif

#ifdef __ANDROID__

static AppSavedState k_appSavedState{false};

static void handleCmdProxy(struct android_app *app, int32_t cmd)
{
    App *a = reinterpret_cast<App*>(app->userData);
    a->handleCommand(cmd);
}

App::App()
    : app_(nullptr)
    , hasFocus_(false)
    , visible_(false)
    , display_(EGL_NO_DISPLAY)
    , surface_(EGL_NO_SURFACE)
    , context_(EGL_NO_CONTEXT)
    , viewportSize_{0.0f, 0.0f}
    , running_(false)
{
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
}

bool App::init(android_app *app)
{
    app_ = app;
    handleInitWindow();

    if (!initDisplay())
    {
        return false;
    }

    if (!initSurface()) {
        return false;
    }

    if (!initContext())
    {
        return false;
    }

    if (EGL_FALSE == eglMakeCurrent(display_, surface_, surface_, context_)) {
        LOG_ERROR << "eglMakeCurrent failed, EGL error " << eglGetError() << LOG_END;
        return false;
    }

    setupOpenGL();

    running_ = true;

    return true;
}

void App::handleCommand(int32_t cmd)
{
    LOG_DEBUG << "Handling command " << cmd << LOG_END;

    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            handleSaveState();
            break;
        case APP_CMD_GAINED_FOCUS:
            handleGainedFocus();
            break;
        case APP_CMD_LOST_FOCUS:
            handleLostFocus();
            break;
        case APP_CMD_PAUSE:
            handlePause();
            break;
        case APP_CMD_RESUME:
            handleResume();
            break;
        case APP_CMD_STOP:
            handleStop();
            break;
        case APP_CMD_START:
            handleStart();
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

    LOG_DEBUG << "Status: hasFocus=" << hasFocus_ << " visible=" << visible_
              << " display=" << display_ << " surface=" << surface_ << " context=" << context_
              << " config=" << config_ << LOG_END;
}

bool App::initDisplay()
{
    display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (EGL_FALSE == eglInitialize(display_, nullptr, nullptr)) {
        LOG_ERROR << "Failed to init display, error " << eglGetError() << LOG_END;
        return false;
    }

    LOG_INFO << "Display initialized successfully" << LOG_END;

    return true;
}

bool App::initSurface()
{
    if (!chooseConfig())
    {
        return false;
    }

    surface_ = eglCreateWindowSurface(display_, config_, app_->window, nullptr);
    if (surface_ == EGL_NO_SURFACE)
    {
        LOG_ERROR << "Failed to create EGL surface, EGL error " << eglGetError() << LOG_END;
        return false;
    }

    LOG_INFO << "Successfully initialized surface." << LOG_END;

    return true;
}

bool App::initContext()
{
    EGLint attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION,
        3,
        EGL_NONE
    };

    context_ = eglCreateContext(display_, config_, nullptr,attribs);
    if (context_ == EGL_NO_CONTEXT) {
        LOG_ERROR << "Failed to create EGL context, EGL error " << eglGetError() << LOG_END;
        return false;
    }

    LOG_INFO << "Initialized context successfully" << LOG_END;

    return true;
}

bool App::chooseConfig()
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
        LOG_ERROR << "Failed to find config" << LOG_END;
        return false;
    }

    config_ = *cfg;

    return true;
}

void App::setupOpenGL()
{
    glEnable(GL_BLEND);
    //glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void App::handleInitWindow()
{
    LOG_DEBUG << "Handling APP_CMD_INIT_WINDOW" << LOG_END;

    if (app_->window) {
        if (app_->savedStateSize == sizeof(savedState_) && app_->savedState) {
            savedState_ = *reinterpret_cast<AppSavedState*>(app_->savedState);
            hasFocus_ = savedState_.hasFocus_;
        } else {
            hasFocus_ = k_appSavedState.hasFocus_;
        }
    }
}

void App::handleSaveState()
{
    LOG_DEBUG << "Handling APP_CMD_SAVE_STATE" << LOG_END;

    savedState_.hasFocus_ = hasFocus_;
    app_->savedState = malloc(sizeof(savedState_));
    *reinterpret_cast<AppSavedState*>(app_->savedState) = savedState_;
    app_->savedStateSize = sizeof(savedState_);
}

void App::handleGainedFocus()
{
    LOG_DEBUG << "Handling APP_CMD_GAINED_FOCUS" << LOG_END;

    hasFocus_ = true;
    savedState_.hasFocus_ = true;
    k_appSavedState.hasFocus_ = true;
}

void App::handleLostFocus()
{
    LOG_DEBUG << "Handling APP_CMD_LOST_FOCUS" << LOG_END;

    hasFocus_ = false;
    savedState_.hasFocus_ = false;
    k_appSavedState.hasFocus_ = false;
}

void App::handlePause()
{
    LOG_DEBUG << "Handling APP_CMD_PAUSE" << LOG_END;
}

void App::handleResume()
{
    LOG_DEBUG << "Handling APP_CMD_RESUME" << LOG_END;
}

void App::handleStart()
{
    LOG_DEBUG << "Handling APP_CMD_START" << LOG_END;

    visible_ = false;
}

void App::handleStop()
{
    LOG_DEBUG << "Handling APP_CMD_STOP" << LOG_END;

    visible_ = true;
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

#endif

void App::process()
{
}

} // end of namespace commonlib
} // end of namespace mcdane
