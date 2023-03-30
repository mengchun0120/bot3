#ifndef INCLUDED_BOTLIB_SHOW_MAP_APP_H
#define INCLUDED_BOTLIB_SHOW_MAP_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_show_map_screen.h>

namespace mcdane {
namespace botlib {

class ShowMapApp: public commonlib::App {
public:
    ShowMapApp();

    ~ShowMapApp() override;

#ifdef DESKTOP_APP
    void init(const std::string &configFile,
              const std::string &appDir,
              const std::string &mapFile);
#elif __ANDROID__
    void init(android_app *app,
              const std::string &configFile,
              const std::string &mapFile);
#endif

    void process() override;

    bool operator()(const commonlib::InputEvent &e);

private:
    void setupGame(const std::string &mapFile);

    void setupDeltaSmoother();

    void setupScreen(const std::string &mapFile);

    void setupInput();

    void onViewportChange(float width, float height) override;

    void exitApp();

private:
    TimeDeltaSmoother deltaSmoother_;
    ShowMapScreen screen_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
