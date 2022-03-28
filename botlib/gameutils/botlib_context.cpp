#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_context.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::shared_ptr<Context> Context::k_context;

void Context::init(const AppConfig& cfg)
{
    if (k_context)
    {
        THROW_EXCEPT(MyException, "k_context already initialized");
    }

    Context* cxt = new Context(cfg);
    k_context.reset(cxt);
}

Context::Context(const AppConfig& cfg)
    : graphics_(cfg)
    , gameLib_(cfg)
    , hpIndicatorConfig_(graphics_, cfg.hpIndicatorConfigFile())
    , buttonConfig_(cfg.buttonConfigFile(), cfg.picDir())
    , labelConfig_(cfg.labelConfigFile())
    , msgBoxConfig_(cfg.messageBoxConfigFile())
    , startScreenConfig_(cfg.startScreenConfigFile())
{
    LOG_INFO << "Context initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

