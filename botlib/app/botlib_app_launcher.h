#ifndef INCLUDED_BOTLIB_APP_LAUNCHER_H
#define INCLUDED_BOTLIB_APP_LAUNCHER_H

#include <unordered_map>

#ifdef __ANDROID__
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif

#include <commonlib_app.h>

namespace mcdane {
namespace botlib {

class AppLauncher {
    typedef void (AppLauncher::*InitFunc)();

public:
    AppLauncher();

    ~AppLauncher();

#ifdef DESKTOP_APP
    void init(int argc, char *argv[]);

    void run();

#elif __ANDROID__
    void init(android_app *env,
              const std::string& startFile);

    void handleCmd(int cmd);

    void process();

#endif

private:
    void initTestShapeApp();

    void initTestMapApp();

    void initTestWidgetApp();

    void initTestParticleApp();

    void initTestGameButtonsApp();

    void initTestDirectionPieApp();

    void initTestGameNavigatorApp();

    void initShowMapApp();

    void initGenMapApp();

    void initRunGameApp();

private:
    static std::unordered_map<std::string, InitFunc> k_initMap;

#ifdef __ANDROID__
    android_app *env_;
#endif

    commonlib::App *app_;
    std::string appName_;
    std::vector<std::string> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
