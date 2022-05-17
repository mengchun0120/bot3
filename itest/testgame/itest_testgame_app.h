#ifndef INCLUDED_ITEST_TESTMAP_APP_H
#define INCLUDED_ITEST_TESTMAP_APP_H

#include <commonlib_app.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>

namespace mcdane {
namespace itest {

class TestGameApp: public commonlib::App {
public:
    TestGameApp(const std::string& configFile,
                const std::string& appDir,
                const std::string& mapFile);

    ~TestGameApp() override = default;

    void process() override;

private:
    void setupOpenGL();

    void setupDeltaSmoother();

    void setupMap(const std::string& mapFile);

    void setupObjDumper();

    void presentObjs();

    void presentEffects();

    void update();

    void clearObjUpdated();

    void updateObjs();

private:
    botlib::GameMap map_;
    botlib::TimeDeltaSmoother deltaSmoother_;
    botlib::GameObjectDumper objDumper_;
};

} // end of namespace itest
} // end of namespace mcdane

#endif

