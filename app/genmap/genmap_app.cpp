#include <commonlib_log.h>
#include <botlib_app_config.h>
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
{
    AppConfig::init(appConfigFile, appDir);

    const AppConfig& cfg = AppConfig::instance();
#ifdef DESKTOP_APP
    setupWindow(cfg.width(), cfg.height(), cfg.title());
#endif
    lib_.load(cfg);
}

GenMapApp::~GenMapApp()
{
}

void GenMapApp::run()
{
    LOG_INFO << "Running" << LOG_END;
}

} // end of namespace genmap
} // end of namespace mcdane
