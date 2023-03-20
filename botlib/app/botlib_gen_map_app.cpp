#include <fstream>
#include <memory>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <commonlib_log.h>
#include <commonlib_file_utils.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_game_map_generator.h>
#include <botlib_game_map_generator_factory.h>
#include <botlib_gen_map_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GenMapApp::GenMapApp()
    : App("genmap")
{
}

#ifdef DESKTOP_APP
void GenMapApp::init(const std::string &appConfigFile,
                     const std::string &appDir,
                     const std::string &algorithm,
                     const std::string &algorithmConfigFile,
                     const std::string &mapFile)
{
    AppConfig::init(appConfigFile, appDir);
    const AppConfig &cfg = AppConfig::instance();
    App::init(cfg.width(), cfg.height(), cfg.title());
    Context::init(cfg);
    setupGame();
    generateMap(algorithm, algorithmConfigFile, appDir, mapFile);
}
#elif __ANDROID__
void GenMapApp::init(android_app *app,
                     const std::string &appConfigFile,
                     const std::string &algorithm,
                     const std::string &algorithmConfigFile)
{
    AppConfig::init(appConfigFile);
    const AppConfig &cfg = AppConfig::instance();
    App::init(app);
    Context::init(cfg);
    setupGame();
    generateMap(algorithm, algorithmConfigFile);
}
#endif

void GenMapApp::process()
{
    App::process();

    InputManager::instance().processInput(*this);
    deltaSmoother_.update();

    if (running())
    {
        screen_.update(deltaSmoother_.curTimeDelta());
        screen_.present();
    }

    postProcess();
}

bool GenMapApp::operator()(const commonlib::InputEvent &e)
{
    if (!running())
    {
        return false;
    }

    screen_.processInput(e);
    return running();
}

void GenMapApp::generateMap(const std::string &algorithm,
                            const std::string &algorithmConfigFile,
                            const std::string &appDir,
                            const std::string &mapFile)
{
    std::string cfgFile = constructPath({appDir, algorithmConfigFile});

    LOG_INFO << "Generating map using algorithm=" << algorithm
             << " algorithmConfigFile=" << cfgFile << LOG_END;

    std::unique_ptr<GameMapGenerator> generator(
                    GameMapGeneratorFactory::create(algorithm,
                                                    Context::gameLib(),
                                                    cfgFile));

    generator->generate(screen_.map(), viewportWidth(), viewportHeight());
    if (!mapFile.empty())
    {
        writeMap(mapFile);
    }
}

void GenMapApp::writeMap(const std::string &mapFile)
{
    using namespace rapidjson;

    const AppConfig &cfg = AppConfig::instance();
    std::string filePath = constructPath({cfg.mapDir(), mapFile});

    LOG_INFO << "Writing map to " << filePath << LOG_END;

    Document doc;
    std::ofstream os(filePath);
    OStreamWrapper osw(os);
    PrettyWriter<OStreamWrapper> writer(osw);

    screen_.map().toJson(doc);
    doc.Accept(writer);

    LOG_INFO << "Map written succcessfully" << LOG_END;
}

void GenMapApp::setupGame()
{
    setupDeltaSmoother();
    setupScreen();
    setupInput();
}

void GenMapApp::setupDeltaSmoother()
{
    const AppConfig &cfg = AppConfig::instance();
    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void GenMapApp::setupScreen()
{
    AppActions actions;
    actions.exitAction_ = std::bind(&GenMapApp::exitApp, this);
    screen_.init(viewportSize(), actions, ScreenType::NONE, false);
}

#ifdef DESKTOP_APP
void GenMapApp::setupInput()
{
    const AppConfig &cfg = AppConfig::instance();

    InputManager::initInstance(window(),
                               viewportSize(),
                               cfg.inputQueueCapacity());
    InputManager::instance().enable();
}
#elif __ANDROID__
void GenMapApp::setupInput()
{
    InputManager::initInstance(app_, viewportSize());
}
#endif

void GenMapApp::onViewportChange(float width, float height)
{
    App::onViewportChange(width, height);
    InputManager::instance().setViewportSize(viewportSize());
    screen_.onViewportChange(width, height);
}

void GenMapApp::exitApp()
{
    setRunning(false);
}

} // end of namespace botlib
} // end of namespace mcdane
