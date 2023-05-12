#include <iostream>
#include <cstdlib>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_system.h>
#include <commonlib_file_utils.h>
#include <commonlib_out_utils.h>
#include <botlib_test_shape_app.h>
#include <botlib_test_widget_app.h>
#include <botlib_test_particle_app.h>
#include <botlib_test_game_buttons_app.h>
#include <botlib_show_map_app.h>
#include <botlib_gen_map_app.h>
#include <botlib_run_game_app.h>
#ifdef __ANDROID__
#include <androidlib_android_out.h>
#endif
#include <botlib_app_launcher.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::unordered_map<std::string, AppLauncher::InitFunc> AppLauncher::k_initMap{
    {"test_shape", &AppLauncher::initTestShapeApp},
    {"test_widget", &AppLauncher::initTestWidgetApp},
    {"test_particle", &AppLauncher::initTestParticleApp},
    {"test_game_buttons", &AppLauncher::initTestGameButtonsApp},
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
    initArgumentParser(parser);
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
    LOG_INFO << "Initializing AppLauncher" << LOG_END;

    setAssetManager(env->activity->assetManager);

    initLog();
    initArguments(startFile);

    env_ = env;
    initApp();

    LOG_INFO << "App initialized" << LOG_END;
}

void AppLauncher::handleCmd(int cmd)
{
    app_->handleCommand(cmd);
}

void AppLauncher::process()
{
    app_->process();
}

void AppLauncher::initLog()
{
    Logger::initInstance(mcdane::androidlib::aout);
}

void AppLauncher::initArguments(const std::string &startFile)
{
    std::vector<std::string> args;
    readArguments(args, startFile);

    ArgumentParser parser;
    initArgumentParser(parser);
    parser.parse(args);
}

void AppLauncher::readArguments(std::vector<std::string> &args,
                                const std::string &startFile)
{
    std::istringstream is1(readText(startFile));

    std::string line;
    while (std::getline(is1, line))
    {
        if (!line.empty() && line[0] != '#')
        {
            std::istringstream is2(line);
            readList(args, is2);
            return;
        }
    }
}

void AppLauncher::initTestShapeApp()
{
    TestShapeApp *a = new TestShapeApp();
    a->init(env_, args_.appConfigFile_);
    app_ = a;
}

void AppLauncher::initTestWidgetApp()
{
    TestWidgetApp *a = new TestWidgetApp();
    a->init(env_, args_.appConfigFile_);
    app_ = a;
}

void AppLauncher::initTestParticleApp()
{
    TestParticleApp *a = new TestParticleApp();
    a->init(env_, args_.appConfigFile_);
    app_ = a;
}

void AppLauncher::initTestGameButtonsApp()
{
    TestGameButtonsApp *a = new TestGameButtonsApp();
    a->init(env_, args_.appConfigFile_);
    app_ = a;
}

void AppLauncher::initTestDirectionPieApp()
{
    TestDirectionPieApp *a = new TestDirectionPieApp();
    a->init(env_, args_.appConfigFile_);
    app_ = a;
}

void AppLauncher::initShowMapApp()
{
    ShowMapApp *a = new ShowMapApp();
    a->init(env_, args_.appConfigFile_, args_.mapFile_);
    app_ = a;
}

void AppLauncher::initGenMapApp()
{
    GenMapApp *a = new GenMapApp();
    a->init(env_, args_.appConfigFile_, args_.algorithm_, args_.algorithmConfigFile_);
    app_ = a;
}

void AppLauncher::initRunGameApp()
{
    RunGameApp *a = new RunGameApp();
    a->init(env_, args_.appConfigFile_, args_.mapFile_, args_.exerciseMode_);
    app_ = a;
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

void AppLauncher::initArgumentParser(ArgumentParser &parser)
{
    parser.init({
        Argument::create(args_.appName_,
                         "appName",
                         "",
                         "",
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
#ifdef DESKTOP_APP
        Argument::create(args_.logFile_,
                         "logFile",
                         "l",
                         "logFile",
                         "Log file",
                         false,
                         k_nonEmptyStrV),
        Argument::create(args_.appDir_,
                         "appDir",
                         "a",
                         "appDir",
                         "App directory",
                         false,
                         k_nonEmptyStrV),
#endif
    });

}

} // end of namespace botlib
} // end of namespace mcdane
