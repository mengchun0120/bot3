#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_context.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Graphics Context::k_graphics;
GameLib Context::k_gameLib;
HPIndicatorConfig Context::k_hpIndicatorConfig;
ButtonConfig Context::k_buttonConfig;
LabelConfig Context::k_labelConfig;
MessageBoxConfig Context::k_msgBoxConfig;
StartScreenConfig Context::k_startScreenConfig;
GameScreenConfig Context::k_gameScreenConfig;
ShowMapScreenConfig Context::k_showMapScreenConfig;
GoodieGenerator Context::k_goodieGenerator;

void Context::init(const AppConfig& cfg)
{
    k_graphics.init(cfg);
    k_gameLib.load(cfg);
    k_hpIndicatorConfig.init(cfg.hpIndicatorConfigFile());
    k_buttonConfig.init(cfg.buttonConfigFile(), cfg.picDir());
    k_labelConfig.init(cfg.labelConfigFile());
    k_msgBoxConfig.init(cfg.messageBoxConfigFile());
    k_startScreenConfig.init(cfg.startScreenConfigFile());
    k_gameScreenConfig.init(cfg.gameScreenConfigFile());
    k_showMapScreenConfig.init(cfg.showMapScreenConfigFile());
    k_goodieGenerator.init(k_gameLib.goodieTemplateLib());

    LOG_INFO << "Context initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

