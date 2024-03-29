#ifndef INCLUDED_GEN_MAP_APP_H
#define INCLUDED_GEN_MAP_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_show_map_screen.h>

namespace mcdane {
namespace botlib {

class GenMapApp: public commonlib::App {
public:
    GenMapApp();

    ~GenMapApp() override = default;

#ifdef DESKTOP_APP
    void init(const std::string &appConfigFile,
              const std::string &appDir,
              const std::string &algorithm,
              const std::string &algorithmConfigFile,
              const std::string &mapFile);
#elif __ANDROID__
    void init(android_app *app,
              const std::string &appConfigFile,
              const std::string &algorithm,
              const std::string &algorithmConfigFile);
#endif

    void process() override;

    bool operator()(const commonlib::InputEvent &e);

private:
    void generateMap(const std::string &algorithm,
                     const std::string &algorithmConfigFile,
                     const std::string &appDir="",
                     const std::string &mapFile="");

    void writeMap(const std::string &mapFile);

    void setupGame();

    void setupDeltaSmoother();

    void setupScreen();

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
