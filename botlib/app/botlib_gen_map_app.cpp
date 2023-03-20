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
#include <genmap_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace genmap {

GenMapApp::GenMapApp()
    : App()
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
    init(cfg.width(), cfg.height(), cfg.title());
    Context::init(cfg);
    setupOpenGL();
    setupGame();
    generateMap(algorithm, algorithmConfigFile, mapFile, appDir);
}
#elif __ANDROID__
void GenMapApp::init(android_app *app,
                     const std::string &appConfigFile,
                     const std::string &algorithm,
                     const std::string &algorithmConfigFile,
                     const std::string &mapFile)
{
    AppConfig::init(appConfigFile);
    const AppConfig &cfg = AppConfig::instance();
    init(app);
    Context::init(cfg);
    setupOpenGL();
    setupGame();
    generateMap(algorithm, algorithmConfigFile, mapFile, appDir);
}
#endif

void GenMapApp::process()
{
    InputManager::getInstance().processInput(inputProcessor_);

    if (running())
    {
        screen_.update(deltaSmoother_.curTimeDelta());
        screen_.present();
    }
}

void GenMapApp::generateMap(const std::string &algorithm,
                            const std::string &algorithmConfigFile,
                            const std::string &mapFile,
                            const std::string &appDir)
{
    std::string cfgFile = constructPath({appDir, algorithmConfigFile});

    LOG_INFO << "Generating map using algorithm=" << algorithm
             << " algorithmConfigFile=" << cfgFile << LOG_END;

    std::unique_ptr<GameMapGenerator> generator(
                    GameMapGeneratorFactory::create(algorithm,
                                                    Context::gameLib(),
                                                    cfgFile));

    generator->generate(screen_.map(), viewportWidth(), viewportHeight());
    writeMap(mapFile);
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

void GenMapApp::setupInput()
{
    using namespace std::placeholders;

    const AppConfig &cfg = AppConfig::instance();

    InputManager::initInstance(window(),
                               viewportHeight(),
                               cfg.inputQueueCapacity());

    inputProcessor_ = std::bind(&ShowMapScreen::processInput,
                                &screen_,
                                _1);

    InputManager::getInstance().enable();
}

void GenMapApp::exitApp()
{
    setRunning(false);
}

} // end of namespace genmap
} // end of namespace mcdane
