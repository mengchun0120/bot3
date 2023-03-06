#ifndef INCLUDED_GENMAP_APP_H
#define INCLUDED_GENMAP_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_showmap_screen.h>

namespace mcdane {

namespace botlib {

class GameMap;
class GameMapGenerator;

} // end of namespace botlib

namespace genmap {

class GenMapApp: public commonlib::App {
public:
    GenMapApp(const std::string& appConfigFile,
              const std::string& appDir,
              const std::string& algorithm,
              const std::string& algorithmConfigFile,
              const std::string& mapFile);

    ~GenMapApp() override = default;

    void process() override;

private:
    void generateMap(const std::string& algorithm,
                     const std::string& algorithmConfigFile,
                     const std::string& mapFile,
                     const std::string& appDir);

    void writeMap(const std::string& mapFile);

    void setupGame();

    void setupDeltaSmoother();

    void setupScreen();

    void setupInput();

    void exitApp();

private:
    botlib::TimeDeltaSmoother deltaSmoother_;
    commonlib::InputProcessor inputProcessor_;
    botlib::ShowMapScreen screen_;
};

} // end of namespace genmap
} // end of namespace mcdane

#endif
