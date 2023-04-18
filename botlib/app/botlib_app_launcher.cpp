#include <commonlib_log.h>
#include <botlib_test_shape_app.h>
#include <botlib_test_map_app.h>
#include <botlib_test_widget_app.h>
#include <botlib_test_particle_app.h>
#include <botlib_test_game_buttons_app.h>
#include <botlib_test_direction_pie_app.h>
#include <botlib_test_game_navigator_app.h>
#include <botlib_show_map_app.h>
#include <botlib_gen_map_app.h>
#include <botlib_run_game_app.h>
#include <botlib_app_launcher.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::unordered_map<std::string, AppLauncher::InitFunc> AppLauncher::k_initMap{
    {"test_shape", &AppLauncher::initTestShapeApp},
    {"test_map", &AppLauncher::initTestMapApp},
    {"test_widget", &AppLauncher::initTestWidgetApp},
    {"test_particle", &AppLauncher::initTestParticleApp},
    {"test_game_buttons", &AppLauncher::initTestGameButtonsApp},
    {"test_direction_pie", &AppLauncher::initTestDirectionPieApp},
    {"test_game_navigator", &AppLauncher::initTestGameNavigatorApp},
    {"show_map", &AppLauncher::initShowMapApp},
    {"gen_map", &AppLauncher::initGenMapApp},
    {"run_game", &AppLauncher::initRunGameApp},
};

AppLauncher::AppLauncher()
    : app_(nullptr)
{
}

AppLauncher::~AppLauncher()
{
    if (app_)
    {
        delete app_;
    }
}

#ifdef DESKTOP_APP
void AppLauncher::init(int argc, char *argv[])
{
}

void AppLauncher::run()
{
}

void AppLauncher::initTestShapeApp()
{
}

void AppLauncher::initTestMapApp()
{
}

void AppLauncher::initTestWidgetApp()
{
}

void AppLauncher::initTestParticleApp()
{
}

void AppLauncher::initTestGameButtonsApp()
{
}

void AppLauncher::initTestDirectionPieApp()
{
}

void AppLauncher::initTestGameNavigatorApp()
{
}

void AppLauncher::initShowMapApp()
{
}

void AppLauncher::initGenMapApp()
{
}

void AppLauncher::initRunGameApp()
{
}

#elif __ANDROID__
void AppLauncher::init(android_app *env,
                       const std::string& startFile)
{
}

void AppLauncher::handleCmd(int cmd)
{
}

void AppLauncher::process()
{
}

void AppLauncher::initTestShapeApp()
{
}

void AppLauncher::initTestMapApp()
{
}

void AppLauncher::initTestWidgetApp()
{
}

void AppLauncher::initTestParticleApp()
{
}

void AppLauncher::initTestGameButtonsApp()
{
}

void AppLauncher::initTestDirectionPieApp()
{
}

void AppLauncher::initTestGameNavigatorApp()
{
}

void AppLauncher::initShowMapApp()
{
}

void AppLauncher::initGenMapApp()
{
}

void AppLauncher::initRunGameApp()
{
}

#endif

} // end of namespace botlib
} // end of namespace mcdane
