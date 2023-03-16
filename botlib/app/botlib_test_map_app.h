#ifndef INCLUDED_BOTLIB_TEST_MAP_APP_H
#define INCLUDED_BOTLIB_TEST_MAP_APP_H

#include <commonlib_app.h>
#include <botlib_game_object_factory.h>
#include <botlib_game_map.h>

namespace mcdane {
namespace botlib {

class TestMapApp: public commonlib::App {
public:
    TestMapApp();

    ~TestMapApp() override = default;

#ifdef DESKTOP_APP
    void init(const std::string &configFile,
              const std::string &appDir,
              const std::string &mapFile);
#elif __ANDROID__
    void init(android_app *app);
#endif

    void process() override;

private:
    void setupMap(const std::string &mapFile);

    void onViewportChange(float width, float height) override;

private:
    botlib::GameMap map_;
    botlib::GameObjectFactory factory_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

