#ifndef INCLUDED_BOTLIB_RUN_GAME_APP_H
#define INCLUDED_BOTLIB_RUN_GAME_APP_H

#include <commonlib_app.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_game_screen.h>

namespace mcdane {
namespace botlib {

class RunGameApp: public commonlib::App {
public:
    RunGameApp() = default;

    ~RunGameApp() = default;

#ifdef DESKTOP_APP
    void init(const std::string &configFile,
              const std::string &appDir,
              const std::string &mapFile,
              bool exerciseMode=false);
#elif __ANDROID__
    void init(android_app *app,
              const std::string &configFile,
              const std::string &mapFile,
              bool exerciseMode=false);
#endif

    void process() override;

    bool operator()(const commonlib::InputEvent &e);

private:
    void setupGame(const std::string& mapFile,
                   bool exerciseMode);

    void setupDeltaSmoother();

    void setupScreen(const std::string& mapFile,
                     bool exerciseMode);

    void setupInput();

    void onViewportChange(float width, float height) override;

    void exitApp();

private:
    botlib::TimeDeltaSmoother deltaSmoother_;
    botlib::GameScreen screen_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

