#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_graphics.h>

namespace mcdane {
namespace botlib {

Graphics::Graphics(const AppConfig& cfg)
{
    simpleShader_.init(cfg.simpleVertexShaderFiles(),
                       cfg.simpleFragShaderFiles());
    particleShader_.init(cfg.particleVertexShaderFiles(),
                         cfg.particleFragShaderFiles());
    textSys_.load(cfg.fontDir());
}

} // end of namespace botlib
} // end of namespace mcdane

