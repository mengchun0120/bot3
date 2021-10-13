#ifndef INCLUDED_ITEST_TESTMAP_APP_H
#define INCLUDED_ITEST_TESTMAP_APP_H

#include <commonlib_app.h>
#include <botlib_game_map.h>

namespace mcdane {
namespace itest {

class TestMapApp: public commonlib::App {
public:
    TestMapApp(const std::string& configFile,
                  const std::string& appDir);

    ~TestMapApp() override = default;

    void preProcess() override;

    void process() override;

    void postProcess() override;

private:
    void setupOpenGL();

    void setupMap();

private:
    botlib::GameMap map_;
};

} // end of namespace itest
} // end of namespace mcdane

#endif

