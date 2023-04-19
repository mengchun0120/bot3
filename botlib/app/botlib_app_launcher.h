#ifndef INCLUDED_BOTLIB_APP_LAUNCHER_H
#define INCLUDED_BOTLIB_APP_LAUNCHER_H

#include <fstream>
#include <unordered_map>

#ifdef __ANDROID__
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif

#include <commonlib_app.h>

namespace mcdane {
namespace botlib {

class AppLauncher {
    typedef void (AppLauncher::*InitFunc)();

#ifdef DESKTOP_APP
struct Arguments {
    std::string appName_;
    std::string appConfigFile_;
    std::string logLevelStr_;
    std::string logFile_;
    std::string mapFile_;
    std::string appDir_;
    std::string algorithm_;
    std::string algorithmConfigFile_;
    bool exerciseMode_;
};

#elif __ANDROID__
struct Arguments {
    std::string appName_;
    std::string appConfigFile_;
    std::string logLevelStr_;
    std::string mapFile_;
    bool exerciseMode_;
};

#endif

public:
    AppLauncher();

    ~AppLauncher();

#ifdef DESKTOP_APP
    void init(int argc, char *argv[]);

    void run();

#elif __ANDROID__
    void init(android_app *env,
              const std::string &startFile);

    void handleCmd(int cmd);

    void process();

#endif

private:
#ifdef DESKTOP_APP
    void initArguments(int argc, char *argv[]);
#elif __ANDROID__
    void initArguments(const std::string &startFile);
#endif

    void initLog();

    void initApp();

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

#ifdef DESKTOP_APP
    std::std::ofstream logStream_;
#elif __ANDROID__
    android_app *env_;
#endif

    commonlib::App *app_;
    Arguments args_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
