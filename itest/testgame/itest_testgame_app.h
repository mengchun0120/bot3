#ifndef INCLUDED_ITEST_TESTMAP_APP_H
#define INCLUDED_ITEST_TESTMAP_APP_H

#include <commonlib_app.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_game_map.h>
#include <botlib_game_object_updater.h>
#include <botlib_game_object_flag_resetter.h>

namespace mcdane {
namespace itest {

class TestGameApp: public commonlib::App {
public:
    TestGameApp(const std::string& configFile,
                const std::string& appDir,
                const std::string& mapFile);

    ~TestGameApp() override = default;

    void preProcess() override;

    void process() override;

    void postProcess() override;

private:
    void setupOpenGL();

    void setupDeltaSmoother();

    void setupMap(const std::string& mapFile);

    void setupGameObjUpdater();

    void setupFlagAccessor();

    void update();

private:
    botlib::GameMap map_;
    botlib::TimeDeltaSmoother deltaSmoother_;
    botlib::GameObjectUpdater gameObjUpdater_;
    botlib::GameMap::Accessor updater_;
    botlib::GameObjectFlagResetter flagResetter_;
    botlib::GameMap::Accessor flagAccessor_;
};

} // end of namespace itest
} // end of namespace mcdane

#endif

