#include <fstream>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_game_map.h>
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
    : App()
    , mapFile_(mapFile)
    , generator_(nullptr)
{
    AppConfig::init(appConfigFile, appDir);

    const AppConfig& cfg = AppConfig::instance();
#ifdef DESKTOP_APP
    setupWindow(cfg.width(), cfg.height(), cfg.title());
#endif

    Context::init(cfg);

    LOG_INFO << "Generating map using algorithm=" << algorithm
             << " algorithmConfigFile=" << algorithmConfigFile << LOG_END;

    generator_ = GameMapGeneratorFactory::create(algorithm, Context::gameLib(),
                                                 algorithmConfigFile);

}

GenMapApp::~GenMapApp()
{
    delete generator_;
}

void GenMapApp::run()
{
    GameMap map;

    generator_->generate(map, viewportWidth(), viewportHeight());

    LOG_INFO << "Map generated successfully" << LOG_END;

    writeMap(mapFile_, map);
}

void GenMapApp::writeMap(const std::string& mapFile,
                         GameMap& map)
{
    using namespace rapidjson;

    LOG_INFO << "Writing map to " << mapFile << LOG_END;

    Document doc;
    std::ofstream os(mapFile);
    OStreamWrapper osw(os);
    PrettyWriter<OStreamWrapper> writer(osw);

    map.toJson(doc);
    doc.Accept(writer);

    LOG_INFO << "Map written succcessfully" << LOG_END;
}

} // end of namespace genmap
} // end of namespace mcdane
