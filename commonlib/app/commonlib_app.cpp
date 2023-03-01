#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_app.h>

namespace mcdane {
namespace commonlib {


#ifdef DESKTOP_APP
 App::App()
{
    window_ = nullptr;
}

App::~App()
{
    if (!window_)
    {
        glfwTerminate();
    }
}
#endif

#ifdef __ANDROID__

static void handleCmdProxy(struct android_app *app, int32_t cmd) {
    App *a = reinterpret_cast<App*>(app->userData);
    a->handleCommand(cmd);
}

static int handleInputProxy(struct android_app *app, AInputEvent *event) {
    App *a = reinterpret_cast<App*>(app->userData);
    return a->handleInput(event) ? 1 : 0;
}

App::App()
    : app_(nullptr)
    , hasFocus_(false)
    , visible_(false)
    , hasWindow_(false)
    , display_(EGL_NO_DISPLAY)
    , surface_(EGL_NO_SURFACE)
    , context_(EGL_NO_CONTEXT)
    , config_(0)
{
}

App::~App()
{

}

bool App::init(android_app *app)
{
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
        handleEglError(eglGetError());
        return false;
    }

    return true;
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
    EGLint numConfigs;
    const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE,
            EGL_OPENGL_ES3_BIT,  // request OpenGL ES 3.0
            EGL_SURFACE_TYPE,
            EGL_WINDOW_BIT,
            EGL_BLUE_SIZE,
            8,
            EGL_GREEN_SIZE,
            8,
            EGL_RED_SIZE,
            8,
            EGL_DEPTH_SIZE,
            16,
            EGL_NONE
    };

    eglChooseConfig(display_, attribs, &config_, 1, &numConfigs);

    surface_ = eglCreateWindowSurface(display_, config_, app_->window, nullptr);
    if (surface_ == EGL_NO_SURFACE) {
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
    };  // OpenGL 3.0

    context_ = eglCreateContext(display_, config_, nullptr,attribs);
    if (context_ == EGL_NO_CONTEXT) {
        LOG_ERROR << "Failed to create EGL context, EGL error " << eglGetError() << LOG_END;
        return false;
    }

    LOG_INFO << "Initialized context successfully" << LOG_END;

    return true;
}

void App::killDisplay()
{
    killContext();
    killSurface();

    if (display_ != EGL_NO_DISPLAY) {
        LOG_INFO << "Terminating display" << LOG_END;

        eglTerminate(display_);
        display_ = EGL_NO_DISPLAY;
    }

    LOG_INFO << "Display killed successfully." << LOG_END;
}

void App::killSurface()
{
    eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (surface_ != EGL_NO_SURFACE) {
        LOG_INFO << "Killing surface ..." << LOG_END;

        eglDestroySurface(display_, surface_);
        surface_ = EGL_NO_SURFACE;
    }

    LOG_INFO << "Surface killed successfully." << LOG_END;
}

void App::killContext()
{
    eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    if (context_ != EGL_NO_CONTEXT) {
        LOG_INFO << "Killing context ..." << LOG_END;

        eglDestroyContext(display_, context_);
        context_ = EGL_NO_CONTEXT;
    }

    LOG_INFO << "NativeEngine: Context killed successfully." << LOG_END;
}

void App::handleEglError(EGLint error)
{
    switch (error)
    {
        case EGL_CONTEXT_LOST:
            LOG_ERROR << "egl error: EGL_CONTEXT_LOST. Recreating context." << LOG_END;
            killContext();
            return;
        case EGL_BAD_CONTEXT:
            LOG_ERROR << "egl error: EGL_BAD_CONTEXT. Recreating context." << LOG_END;
            killContext();
            return;
        case EGL_BAD_DISPLAY:
            LOG_ERROR << "egl error: EGL_BAD_DISPLAY. Recreating display." << LOG_END;
            killDisplay();
            return;
        case EGL_BAD_SURFACE:
            LOG_ERROR << "egl error: EGL_BAD_SURFACE. Recreating display." << LOG_END;
            killSurface();
            return;
        default:
            LOG_ERROR << "unknown egl error: " << error << LOG_END;
            return;
    }
}
#endif

void App::process()
{
}

void App::run()
{
    running_ = true;
    while (shouldRun())
    {
        process();
    }
}

void App::postProcess()
{
#ifdef DESKTOP_APP
    glfwSwapBuffers(window_);
    glfwPollEvents();
#endif
}

} // end of namespace commonlib
} // end of namespace mcdane