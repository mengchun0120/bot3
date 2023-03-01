#include <jni.h>

#include "AndroidOut.h"
#include "Renderer.h"

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>
#include <androidlib_android_out.h>
#include <commonlib_log.h>

extern "C" {

#include <game-activity/native_app_glue/android_native_app_glue.c>

void handle_cmd(android_app *pApp, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            break;
        case APP_CMD_TERM_WINDOW:
            break;
        default:
            break;
    }
}

void initLog()
{
    mcdane::commonlib::Logger::initInstance(mcdane::androidlib::aout);
}

/*!
 * This the main entry point for a native activity
 */
void android_main(struct android_app *pApp)
{
    initLog();

    LOG_DEBUG << "Welcome to Robot" << LOG_END;

    // register an event handler for Android events
    pApp->onAppCmd = handle_cmd;

    // This sets up a typical game/event loop. It will run until the app is destroyed.
    int events;
    android_poll_source *pSource;
    do {
        // Process all pending events before running game logic.
        if (ALooper_pollAll(0, nullptr, &events, (void **) &pSource) >= 0) {
            if (pSource) {
                pSource->process(pApp, pSource);
            }
        }

        // Check if any user data is associated. This is assigned in handle_cmd
        if (pApp->userData) {

            // We know that our user data is a Renderer, so reinterpret cast it. If you change your
            // user data remember to change it here
            /*auto *pRenderer = reinterpret_cast<Renderer *>(pApp->userData);

            // Process game input
            pRenderer->handleInput();

            // Render a frame
            pRenderer->render();*/
        }
    } while (!pApp->destroyRequested);
}
}