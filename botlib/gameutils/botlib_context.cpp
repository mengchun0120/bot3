#include <commonlib_log.h>
#include <botlib_context.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Context::Context(const std::string& appCfgFileName,
                 const std::string& appDir)
    : appCfg_(appCfgFileName, appDir)
    , graphics_(appCfg_)
    , gameLib_(appCfg_)
{
    LOG_INFO << "Context initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

