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

GenMapApp::GenMapApp(const std::string& appConfigFile,
                     const std::string& appDir,
                     const std::string& algorithm,
                     const std::string& algorithmConfigFile,
                     const std::string& mapFile)
{
    init(appConfigFile, appDir, algorithm, algorithmConfigFile, mapFile);
}

void GenMapApp::process()
{
    InputManager::getInstance().processInput(inputProcessor_);

    if (running())
    {
        screen_.update(deltaSmoother_.curTimeDelta());
        screen_.present();
    }

    postProcess();
}

void GenMapApp::init(const std::string& appConfigFile,
                     const std::string& appDir,
                     const std::string& algorithm,
                     const std::string& algorithmConfigFile,
                     const std::string& mapFile)
{
    AppConfig::init(appConfigFile, appDir);
    const AppConfig& cfg = AppConfig::instance();
#ifdef DESKTOP_APP
    setupWindow(cfg.width(), cfg.height(), cfg.title());
#endif
    Context::init(cfg);
    setupOpenGL();
    setupGame();
    generateMap(algorithm, algorithmConfigFile, mapFile);
}

void GenMapApp::generateMap(const std::string& algorithm,
                            const std::string& algorithmConfigFile,
                            const std::string& mapFile)
{
    LOG_INFO << "Generating map using algorithm=" << algorithm
             << " algorithmConfigFile=" << algorithmConfigFile << LOG_END;

    std::unique_ptr<GameMapGenerator> generator(
                    GameMapGeneratorFactory::create(algorithm,
                                                    Context::gameLib(),
                                                    algorithmConfigFile));

    generator->generate(screen_.map(), viewportWidth(), viewportHeight());
    writeMap(mapFile);
}

void GenMapApp::writeMap(const std::string& mapFile)
{
    using namespace rapidjson;

    const AppConfig& cfg = AppConfig::instance();
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

void GenMapApp::setupOpenGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void GenMapApp::setupGame()
{
    setupDeltaSmoother();
    setupScreen();
    setupInput();
}

void GenMapApp::setupDeltaSmoother()
{
    const AppConfig& cfg = AppConfig::instance();
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

    const AppConfig& cfg = AppConfig::instance();

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
