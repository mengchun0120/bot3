#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_graphics.h>

namespace mcdane {
namespace botlib {

void Graphics::init(const AppConfig& cfg)
{
    simpleShader_.init(cfg.simpleVertexShaderFiles(),
                       cfg.simpleFragShaderFiles());
    particleShader_.init(cfg.particleVertexShaderFiles(),
                         cfg.particleFragShaderFiles());
    textSys_.load(cfg.fontDir());

    LOG_INFO << "Graphics created successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

