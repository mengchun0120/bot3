#ifndef INCLUDED_SHOWMAP_APP_H
#define INCLUDED_SHOWMAP_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_showmap_screen.h>

namespace mcdane {
namespace showmap {

class ShowMapApp: public commonlib::App {
public:
    ShowMapApp(const std::string& configFile,
               const std::string& appDir,
               const std::string& mapFile);

    ~ShowMapApp() override;

    void process() override;

private:
    void setupGame(const std::string& mapFile);

    void setupDeltaSmoother();

    void setupScreen(const std::string& mapFile);

    void setupInput();

    void exitApp();

private:
    botlib::TimeDeltaSmoother deltaSmoother_;
    commonlib::InputProcessor inputProcessor_;
    botlib::ShowMapScreen screen_;
};

} // end of namespace showmap
} // end of namespace mcdane

#endif