#include <iostream>
#include <cstdlib>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_argument_parser.h>
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
    try
    {
        initArguments(argc, argv);
        initLog();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception happened while initializing log: " << e.what()
                  << std::endl;
        exit(1);
    }


    try
    {
        initApp();
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << "Exception happended when initializing app: " << e.what()
                   << LOG_END;
        exit(1);
    }
}

void AppLauncher::run()
{
    try
    {
        app_->run();
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << "Exception happened when running app: " << e.what()
                  << LOG_END;
        exit(1);
    }
}

void AppLauncher::initArguments(int argc, char *argv[])
{
    ArgumentParser parser;
    parser.init({
        Argument::create(args_.appName_,
                         "appName",
                         "n",
                         "appName",
                         "App name",
                         false,
                         k_nonEmptyStrV),
        Argument::create(args_.appConfigFile_,
                         "appConfig",
                         "c",
                         "appConfig",
                         "Config file for app",
                         false,
                         k_nonEmptyStrV),
        Argument::create(args_.logFile_,
                         "logFile",
                         "l",
                         "logFile",
                         "Log file",
                         false,
                         k_nonEmptyStrV),
        Argument::create(args_.logLevelStr_,
                         "logLevel",
                         "v",
                         "logLevel",
                         "Log level",
                         true,
                         k_nonEmptyStrV),
        Argument::create(args_.mapFile_,
                         "mapFile",
                         "m",
                         "mapFile",
                         "File to store generated map",
                         true,
                         k_nonEmptyStrV),
        Argument::create(args_.appDir_,
                         "appDir",
                         "a",
                         "appDir",
                         "App directory",
                         false,
                         k_nonEmptyStrV),
        Argument::create(args_.algorithm_,
                         "algorithm",
                         "g",
                         "algorithm",
                         "Algorithm to generate map",
                         true,
                         k_nonEmptyStrV),
        Argument::create(args_.algorithmConfigFile_,
                         "algorithmConfigFile",
                         "G",
                         "algorithmConfig",
                         "Config file for generating map",
                         true,
                         k_nonEmptyStrV),
        Argument::create(args_.exerciseMode_,
                         "exerciseMode",
                         "e",
                         "exerciseMode",
                         "Whether to run app in exersise mode",
                         true),
    });

    parser.parse(argc, argv);
}

void AppLauncher::initLog()
{
    logStream_.open(args_.logFile_);

    if (!logStream_.good())
    {
        THROW_EXCEPT(FileException, "Failed to open file " + args_.logFile_);
    }

    Logger::LogLevel level = Logger::LEVEL_DEBUG;

    if (!args_.logLevelStr_.empty())
    {
        level = Logger::strToLevel(args_.logLevelStr_);
    }

    Logger::initInstance(logStream_, level);
}

void AppLauncher::initTestShapeApp()
{
    TestShapeApp *a = new TestShapeApp();
    a->init(args_.appConfigFile_, args_.appDir_);
    app_ = a;
}

void AppLauncher::initTestMapApp()
{
    if (args_.mapFile_.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "mapFile cannot be empty");
    }

    TestMapApp *a = new TestMapApp();
    a->init(args_.appConfigFile_, args_.appDir_, args_.mapFile_);
    app_ = a;
}

void AppLauncher::initTestWidgetApp()
{
    TestWidgetApp *a = new TestWidgetApp();
    a->init(args_.appConfigFile_, args_.appDir_);
    app_ = a;
}

void AppLauncher::initTestParticleApp()
{
    TestParticleApp *a = new TestParticleApp();
    a->init(args_.appConfigFile_, args_.appDir_);
    app_ = a;
}

void AppLauncher::initTestGameButtonsApp()
{
    TestGameButtonsApp *a = new TestGameButtonsApp();
    a->init(args_.appConfigFile_, args_.appDir_);
    app_ = a;
}

void AppLauncher::initTestDirectionPieApp()
{
    TestDirectionPieApp *a = new TestDirectionPieApp();
    a->init(args_.appConfigFile_, args_.appDir_);
    app_ = a;
}

void AppLauncher::initTestGameNavigatorApp()
{
    TestGameNavigatorApp *a = new TestGameNavigatorApp();
    a->init(args_.appConfigFile_, args_.appDir_);
    app_ = a;
}

void AppLauncher::initShowMapApp()
{
    ShowMapApp *a = new ShowMapApp();
    a->init(args_.appConfigFile_, args_.appDir_, args_.mapFile_);
    app_ = a;
}

void AppLauncher::initGenMapApp()
{
    GenMapApp *a = new GenMapApp();
    a->init(args_.appConfigFile_, args_.appDir_, args_.algorithm_,
            args_.algorithmConfigFile_, args_.mapFile_);
    app_ = a;
}

void AppLauncher::initRunGameApp()
{
    RunGameApp *a = new RunGameApp();
    a->init(args_.appConfigFile_, args_.appDir_, args_.mapFile_,
            args_.exerciseMode_);
    app_ = a;
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

void AppLauncher::initParams(const std::string &startFile)
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

void AppLauncher::initApp()
{
    auto it = k_initMap.find(args_.appName_);
    if (it == k_initMap.end())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Unrecognized appName " + args_.appName_);
    }

    (this->*(it->second))();
}

} // end of namespace botlib
} // end of namespace mcdane
