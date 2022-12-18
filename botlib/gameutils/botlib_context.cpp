#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_context.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::shared_ptr<Context> Context::k_instance;

void Context::init(const AppConfig& cfg)
{
    k_instance.reset(new Context(cfg));
}

Context::Context(const AppConfig& cfg)
{
    graphics_.init(cfg);
    gameLib_.load(cfg);
    hpIndicatorConfig_.init(graphics_.textSys(), cfg.hpIndicatorConfigFile());
    buttonConfig_.init(cfg.buttonConfigFile(), cfg.picDir());
    labelConfig_.init(cfg.labelConfigFile());
    msgBoxConfig_.init(cfg.messageBoxConfigFile());
    startScreenConfig_.init(cfg.startScreenConfigFile());
    gameScreenConfig_.init(gameLib_, cfg.gameScreenConfigFile());
    showMapScreenConfig_.init(cfg.showMapScreenConfigFile());
    goodieGenerator_.init(gameLib_.goodieTemplateLib());

    LOG_INFO << "Context initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

