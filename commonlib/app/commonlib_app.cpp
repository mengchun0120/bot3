#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_opengl_utils.h>
#include <commonlib_app.h>

namespace mcdane {
namespace commonlib {

App::App()
{
#ifdef DESKTOP_APP
    window_ = nullptr;
#endif
}

App::~App()
{
#ifdef DESKTOP_APP
    if (!window_)
    {
        glfwTerminate();
    }
#endif
}

#ifdef __ANDROID__
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